#ifndef RAPP_CLOUD_ONTOLOGY
#define RAPP_CLOUD_ONTOLOGY
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class ontology_subclasses_of
 * \brief get ontology subclass of a query
 * \version 0.6.1
 * \date May 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class ontology_subclasses_of : public asio_http
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
    : asio_http(), delegate__(callback)
    {
        boost::property_tree::ptree tree;
        tree.put("ontology_class", ontology_class);
        tree.put("recursive", recursive);

        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

		std::string boundary = rapp::misc::random_boundary();
        post_  = "--" + boundary + "\r\n"
               + "Content-Disposition: form-data; name=\"json\"\r\n\r\n";

		// JSON PDT value unquote
		post_ += rapp::misc::json_unquote_pdt_value<bool>()(ss.str(), recursive);
		
		// close the multipart - no need for \r\n here, the json already has one
        post_ += "--" + boundary + "--";

		// set the HTTP header URI pramble and the Content-Type
        head_preamble_.uri = "POST /hop/ontology_subclasses_of HTTP/1.1\r\n";
        head_preamble_.content_type = "Content-Type: multipart/form-data; boundary=" + boundary;

        callback_ = std::bind(&ontology_subclasses_of::handle_reply, this, std::placeholders::_1);
     }
private:
    /**
     * \brief handle and parse JSON reply
     */
    void handle_reply(std::string json)
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
    /// The callback called upon completion of receiving the detected faces
    std::function<void(std::vector<std::string> classes)> delegate__;
};
/**
 * \class ontology_superclasses_of
 * \brief get ontology super-classes of query
 * \version 0.6.1
 * \date May 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class ontology_superclasses_of : public asio_http
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
    : asio_http(), delegate__(callback)
    {
		std::string boundary = rapp::misc::random_boundary();
        boost::property_tree::ptree tree;
        tree.put("ontology_class", ontology_class);
        tree.put("recursive", recursive);

        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        post_  = "--" + boundary + "\r\n"
               + "Content-Disposition: form-data; name=\"json\"\r\n\r\n";

		// JSON PDT value unquote
		post_ += rapp::misc::json_unquote_pdt_value<bool>()(ss.str(), recursive);
		post_ += "--" + boundary + "--";

		// set the HTTP header URI pramble and the Content-Type
        head_preamble_.uri = "POST /hop/ontology_superclasses_of HTTP/1.1\r\n";
		head_preamble_.content_type = "Content-Type: multipart/form-data; boundary=" + boundary;

        callback_ = std::bind(&ontology_superclasses_of::handle_reply, this, std::placeholders::_1);
     }
private:
    /**
     * \brief handle and parse JSON reply
     */
    void handle_reply(std::string json)
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

    /// The callback called upon completion of receiving the detected faces
    std::function<void(std::vector<std::string> classes)> delegate__;
};
/**
 * \class ontology_is_subsuperclass_of
 * \brief query if sub class is a super class of param 
 * \version 0.6.0
 * \date April 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class ontology_is_subsuperclass_of : public asio_http
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
    : asio_http(), delegate__(callback)
    {
        boost::property_tree::ptree tree;
        tree.put("parent_class", parent_class);
        tree.put("child_class", child_class);
        tree.put("recursive", boost::lexical_cast<std::string>(recursive));

		std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

		std::string boundary = rapp::misc::random_boundary();
        post_  = "--" + boundary + "\r\n"
               + "Content-Disposition: form-data; name=\"json\"\r\n\r\n";

		// JSON PDT value unquote
		post_ += misc::json_unquote_pdt_value<bool>()(ss.str(), recursive);
		post_ += "--" + boundary + "--";

		// set the HTTP header URI pramble and the Content-Type
        head_preamble_.uri = "POST /hop/ontology_is_subsuperclass_of HTTP/1.1\r\n";
		head_preamble_.content_type = "Content-Type: multipart/form-data; boundary=" + boundary;

        callback_ = std::bind(&ontology_is_subsuperclass_of::handle_reply, this, std::placeholders::_1);
     }
private:
    /**
     * \brief handle and parse JSON reply
     */
    void handle_reply(std::string json)
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

    /// The callback called upon completion of receiving the detected faces
    std::function<void(bool result)> delegate__;
};
}
}
#endif
