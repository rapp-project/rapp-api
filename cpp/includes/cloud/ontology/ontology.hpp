#ifndef RAPP_CLOUD_ONTOLOGY
#define RAPP_CLOUD_ONTOLOGY
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class ontology_subclasses_of
 * \brief get ontology subclass of a query
 * \version 0.7.0
 * \date 15 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class ontology_subclasses_of : public caller, public http_request
{
public:
    /**
     * \brief constructor for this handler
     * \param query is the entity for which we will try to acquire its Super-Ordinates
     * \param callback is the functor that will receive the classes discovered
     * \param token is the rapp authentication token
     */
    ontology_subclasses_of(
                            std::string ontology_class,
                            bool recursive,
                            std::function<void(std::vector<std::string>)> callback
                          )
    : http_request("POST /hop/ontology_subclasses_of HTTP/1.1\r\n"),
      delegate__(callback)
    {
        boost::property_tree::ptree tree;
        tree.put("ontology_class", ontology_class);
        tree.put("recursive", recursive);
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

        std::string json = rapp::misc::json_unquote_pdt_value<bool>()(ss.str(), recursive);
        http_request.add_content("json", json, false); 
        http_request.close();
     }

    /**
     * \brief handle and parse JSON reply
     */
    void deserialise(std::string json) const
    {
        std::vector<std::string> classes;
        std::stringstream ss(json);
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

            // JSON reply is: { results: [], error: '' }
            for (auto child : tree.get_child("results")) {
                classes.push_back(child.second.get_value<std::string>());
            }

            // Check for Errors returned by the platform
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "ontology_subclasses_of JSON error: " << value << std::endl;
                }
            }
        }
        catch (boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "ontology_subclasses_of::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate__(classes);
    }

    /**
    * \brief method to fill the buffer with http_post and http_header information
    * \param info is the data of the platform    
    */
    void fill_buffer(
                       boost::asio::streambuf & request,
                       rapp::cloud::platform info
                    )
    {
        http_request::fill_buffer(request, info);
    }

private:
    /// The callback called upon completion of receiving the detected faces
    std::function<void(std::vector<std::string> classes)> delegate__;
};

/**
 * \class ontology_superclasses_of
 * \brief get ontology super-classes of query
 * \version 0.7.0
 * \date 15 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class ontology_superclasses_of : public caller, public http_request
{
public:
    /**
     * \param ontology_class is the entity for which we will try to acquire its Super-Ordinates
     * \param callback is the functor that will receive the classes discovered
     * \param token is user authentication token
     */
    ontology_superclasses_of(
                              const std::string ontology_class,
                              bool recursive,
                              std::function<void(std::vector<std::string>)> callback
                            )
    : http_header("POST /hop/ontology_superclasses_of HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()), 
      delegate__(callback)
    {
        boost::property_tree::ptree tree;
        tree.put("ontology_class", ontology_class);
        tree.put("recursive", recursive);

        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
       	// JSON PDT value unquote
        std::string json = rapp::misc::json_unquote_pdt_value<bool>()(ss.str(), recursive);

        http_post::add_content("json", json, false); 
        http_post::end();
     }   

    /**
     * \brief handle and parse JSON reply
     */
    void deserialise(std::string json) const
    {
        std::vector<std::string> classes;
        std::stringstream ss(json);
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

            // JSON reply is: { results: [], error: '' }
            for (auto child : tree.get_child("results")) {
                classes.push_back(child.second.get_value<std::string>());
            }

            // Check for Errors returned by the platform
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "ontology_superclasses_of JSON error: " << value << std::endl;
                }
            }
        }
        catch (boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "ontology_superclasses_of::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate__(classes);
    }

    /**
    * \brief method to fill the buffer with http_post and http_header information
    * \param info is the data of the platform    
    */
    boost::asio::streambuf fill_buffer(rapp::cloud::platform info)
    {
           return std::move(http_request::fill_buffer(info));
    }

private:
    /// The callback called upon completion of receiving the detected faces
    std::function<void(std::vector<std::string> classes)> delegate__;
};

/**
 * \class ontology_is_subsuperclass_of
 * \brief query if sub class is a super class of param 
 * \version 0.7.0
 * \date 15 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class ontology_is_subsuperclass_of : public caller, public http_request
{
public:
    /**
     * \brief query if a class is the superclass of a subclass
     * \param parent class queried
     * \param child class queried
     * \param recursive defines a recursive procedure
     * \param callback is the functor that will receive the classes discovered
     * \param token is the rapp authentication token
     */
    ontology_is_subsuperclass_of(
                                   const std::string parent_class,
                                   const std::string child_class,
                                   bool recursive,
                                   std::function<void(bool result)> callback
                                )
    : http_header("POST /hop/ontology_is_subsuperclass_of HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()), 
      delegate__(callback)
    {
        boost::property_tree::ptree tree;
        tree.put("parent_class", parent_class);
        tree.put("child_class", child_class);
        tree.put("recursive", boost::lexical_cast<std::string>(recursive));

		std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

		// JSON PDT value unquote
        std::string json = misc::json_unquote_pdt_value<bool>()(ss.str(), recursive);
        http_post::add_content("json", json, false); 
        http_post::end();
     }

    /**
     * \brief handle and parse JSON reply
     */
    void deserialise(std::string json)const
    {
        std::vector<std::string> classes;
        std::stringstream ss(json);
        bool result;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

            // JSON reply is: { results: [], trace: [], error: '' }
            for (auto child : tree.get_child( "result")) {
                result = child.second.get_value<bool>();
            }

            // Check for Errors returned by the platform
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "ontology_is_subsuperclass_of JSON error: " << value << std::endl;
                }
            }
        }
        catch (boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "ontology_is_subsuperclass_of::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate__(result);
    }

    /**
    * \brief method to fill the buffer with http_post and http_header information
    * \param info is the data of the platform    
    */
    boost::asio::streambuf fill_buffer(rapp::cloud::platform info)
    {
           return std::move(http_request::fill_buffer(info));
    }

private:
    /// The callback called upon completion of receiving the detected faces
    std::function<void(bool result)> delegate__;
};
}
}
#endif
