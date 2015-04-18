#ifndef RAPP_SERVICE_CLOUD_ONTOLOGY_SUBCLASS_OF
#define RAPP_SERVICE_CLOUD_ONTOLOGY_SUBCLASS_OF
#include "Includes.ihh"

namespace rapp {
namespace cloud {

#define hostname "localhost"
    
/**
 * @class ontologySubclassOf
 * @brief Asynchronous Service which will request the Ontology Subclass of/for an Input
 * @version 2
 * @date 18-April-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */

class ontologySubclassOf : public rapp::services::asio_service_http
{
  public:

    
    /**
     * @brief Constructor for this handler
     * @param query is the entity for which we will try to acquire its Super-Ordinates
     * @param callback is the functor that will receive the classes discovered
     */
    ontologySubclassOf (
                          const std::string query,
                          std::function< void( std::vector<std::string> ) > callback
                       )
    : rapp::services::asio_service_http(),
      delegate__ ( callback )
    {
        // Craft the POSt field
        post_ = "query="+query+"\r\n\r\n";
        
        // Craft the actual header
        header_ = "POST /hop/ontology_subclass_of/ HTTP/1.1\r\n";
        header_ += "Host: " + std::string( hostname ) + "\r\n";
        header_ += "Content-Type: application/x-www-form-urlencoded\r\n";
        header_ += "Content-Length: " + boost::lexical_cast<std::string>( post_.length() ) + "\r\n";
        header_ += "Connection: close\r\n\r\n";   
     }
      
  private:
      
    /// Parse @param buffer received from the socket, into a vector of faces
    void handle ( boost::asio::streambuf & buffer )
    {
        // Convert the buffer into a string
        std::string json ( ( std::istreambuf_iterator<char>( &buffer ) ), std::istreambuf_iterator<char>() );
        std::vector<std::string> classes;
        std::stringstream ss ( json );
        
        // Parse JSON
        boost::property_tree::ptree tree;
        boost::property_tree::read_json( ss, tree );
        
        // TODO: WARNING Decide upon the actual JSON Format.
        for ( auto child : tree.get_child( "subclasses" ) )
        {
            // std::string member( iter->first );
            // classes.push_back ( iter->second.get_value<std::string>();
        }
        
        delegate__( classes );
    }
      
      
    /// The callback called upon completion of receiving the detected faces
    std::function< void( std::vector<std::string> classes ) > delegate__;
};
  
    
}
}

#endif