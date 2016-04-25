#ifndef RAPP_CLOUD_ONTOLOGY_IS_SUBSUPERCLASS_OF
#define RAPP_CLOUD_ONTOLOGY_IS_SUBSUPERCLASS_OF
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class ontology_is_subsuperclass_of
 * \brief query if sub class is a super class of param 
 * \version 2
 * \date January 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class ontology_is_subsuperclass_of : public rapp::services::asio_service_http
{
public:
    /**
     * \brief Constructor for this handler
     * \param query is the entity for which we will try to acquire its ?
     * \param callback is the functor that will receive the classes discovered
     */
    ontology_is_subsuperclass_of(
                                   const std::string parent,
                                   const std::string child,
                                   bool recursive,
                                   std::function<void(bool result)> callback
                                )
    : rapp::services::asio_service_http(), delegate__(callback)
    {
        boost::property_tree::ptree tree;
        tree.put("parent", parent);
        tree.put("child", child);
        tree.put("recursive", boost::lexical_cast<std::string>(recursive));
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        post_ = ss.str();
        header_ = "POST /hop/ontology_is_subsuperclass_of HTTP/1.1\r\n";
        callback_ = std::bind(&ontology_is_subsuperclass_of::handle_reply, this, std::placeholders::_1);
     }
      
private:
      
    void handle_reply(std::string json)
    {
        std::vector<std::string> classes;
        std::stringstream ss(json);
        bool result;
        try
        {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);
            // JSON reply is: { results: [], trace: [], error: '' }
            for (auto child : tree.get_child( "result"))
                result = child.second.get_value<bool>();
            // Check for Errors returned by the api.rapp.cloud
            for (auto child : tree.get_child("error"))
            {
                const std::string value = child.second.get_value<std::string>();
                if ( !value.empty() )
                    std::cerr << "ontology_is_subsuperclass_of JSON error: " << value << std::endl;
            }
        }
        catch( boost::property_tree::json_parser::json_parser_error & je )
        {
            std::cerr << "ontology_is_subsuperclass_of::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate__(result);
    }
      
    /// The callback called upon completion of receiving the detected faces
    std::function<void(bool result)> delegate__;
};
}
}
#endif
