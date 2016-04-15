#ifndef RAPP_CLOUD_ONTOLOGY_SUBCLASSES_OF
#define RAPP_CLOUD_ONTOLOGY_SUBCLASSES_OF
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class ontology_subclasses_of
 * \brief Asynchronous Service which will request the Ontology Subclass of/for an Input
 * \version 4
 * \date January 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class ontology_subclasses_of : public rapp::cloud::asio_service_http
{
public:
    /**
     * \brief Constructor for this handler
     * \param query is the entity for which we will try to acquire its Super-Ordinates
     * \param callback is the functor that will receive the classes discovered
     */
    ontology_subclasses_of(
                            std::string query,
                            std::function<void(std::vector<std::string>)> callback,
							std::string token
                          )
    : asio_service_http(token), delegate__(callback)
    {
        post_ = "query="+escape_string(query);
        header_ = "POST /hop/ontology_subclasses_of HTTP/1.1\r\n";
        header_ += "Host: " + std::string(rapp::cloud::address) + "\r\n";
        header_ += "Content-Type: application/x-www-form-urlencoded\r\n";
        header_ += "Content-Length: " + boost::lexical_cast<std::string>(post_.length()) + "\r\n";
        header_ += "Connection: close\r\n\r\n";
        callback_ = std::bind(&ontology_subclasses_of::handle_reply, this, std::placeholders::_1);
     }
      
private:
	
    void handle_reply(std::string json)
    {
        std::vector<std::string> classes;
        std::stringstream ss(json);
        try
        {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);
            // JSON reply is: { results: [], trace: [], error: '' }
            for (auto child : tree.get_child("results"))
                classes.push_back( child.second.get_value<std::string>() );
            // Check for Errors returned by the api.rapp.cloud
            for (auto child : tree.get_child("error"))
            {
                const std::string value = child.second.get_value<std::string>();
                if ( !value.empty() )
                    std::cerr << "ontology_subclasses_of JSON error: " << value << std::endl;
            }
        }
        catch(boost::property_tree::json_parser::json_parser_error & je)
        {
            std::cerr << "ontology_subclasses_of::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate__(classes);
    }
      
    /// The callback called upon completion of receiving the detected faces
    std::function<void(std::vector<std::string> classes)> delegate__;
};
}
}
#endif
