#ifndef RAPP_CLOUD_ONTOLOGY_SUPERCLASSES_OF
#define RAPP_CLOUD_ONTOLOGY_SUPERCLASSES_OF
#include "Includes.ihh"
namespace rapp {
namespace cloud {
/**
 * @class ontologySuperclassesOf
 * @brief 
 * @version 
 * @date 
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class ontologySuperclassesOf : public rapp::services::asio_service_http
{
public:
    
    /**
     * @brief Constructor for this handler
     * @param query is the entity for which we will try to acquire its Super-Ordinates
     * @param callback is the functor that will receive the classes discovered
     */
    ontologySuperclassesOf (
                              const std::string query,
                              std::function< void( std::vector<std::string> ) > callback
                           )
    : rapp::services::asio_service_http(), delegate__ ( callback )
    {
        post_ = "query="+query+"\r\n\r\n";
        header_ = "POST /hop/ontology_superclasses_of HTTP/1.1\r\n";
        header_ += "Host: " + std::string( rapp::cloud::address ) + "\r\n";
        header_ += "Content-Type: application/x-www-form-urlencoded\r\n";
        header_ += "Content-Length: " + boost::lexical_cast<std::string>( post_.length() ) + "\r\n";
        header_ += "Connection: close\r\n\r\n";
        callback_ = std::bind ( &ontologySuperclassesOf::handle_reply, this, std::placeholders::_1 );
     }
      
private:
      
    void handle_reply ( std::string json )
    {
        std::vector<std::string> classes;
        std::stringstream ss ( json );
        try
        {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json( ss, tree );
            // JSON reply is: { results: [], trace: [], error: '' }
            for ( auto child : tree.get_child( "results" ) )
                for ( auto iter = child.second.begin(); iter!= child.second.end(); ++iter )
                    classes.push_back ( iter->second.get_value<std::string>() );
            // Check for Errors returned by the api.rapp.cloud
            for ( auto child : tree.get_child( "error" ) )
            {
                const std::string value = child.second.get_value<std::string>();
                if ( !value.empty() )
                    std::cerr << "ontologySuperclassesOf JSON error: " << value << std::endl;
            }
        }
        catch( boost::property_tree::json_parser::json_parser_error & je )
        {
            std::cerr << "ontologySuperclassesOf::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate__( classes );
    }
      
    /// The callback called upon completion of receiving the detected faces
    std::function< void( std::vector<std::string> classes ) > delegate__;
};
  
}
}
#endif
