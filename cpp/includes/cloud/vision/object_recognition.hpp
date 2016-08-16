#ifndef RAPP_CLOUD_OBJECT_RECOGNITION
#define RAPP_CLOUD_OBJECT_RECOGNITION
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class object_recognition
 * \brief recognize object from an image
 * \version 0.7.0
 * \date 15 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class object_recognition : public caller, public http_request
{
public:
    /**
    * \brief Constructor
    * \param image is a picture object pointer
    * \param callback is the function that will receive a string
    */
    object_recognition(
                      const rapp::object::picture & image,
                      std::function<void(std::string)> callback
                    )
    : http_header("POST /hop/ontology_subclasses_of HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()), 
      delegate__(callback)
    {
        std::string fname = rapp::misc::random_boundary() + "." + image.type();

        boost::property_tree::ptree tree;
        tree.put("file", fname);
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

        std::string json = ss.str();
        http_post::add_content("json", json, false);

        // Append binary data
        auto imagebytes = image.bytearray();
        http_post::add_content("file", fname, imagebytes);
        http_post::end();

    }
	/**
	 * \brief handle the rapp-platform JSON reply
	 */
    void deserialise(std::string json) const
    {
        std::stringstream ss(json);
        std::string object_class;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

            for (auto child : tree.get_child("object_class")) {
                object_class = child.second.get_value<std::string>();
            }
            // Check for Errors returned by the platform
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "object_recognition JSON error: " << value << std::endl;
                }
            }
        }
        catch(boost::property_tree::json_parser::json_parser_error & je) {
			std::cerr << "object_recognition::handle_reply Error parsing: " 
                      << je.filename() << " on line: " << je.line() << std::endl;
			std::cerr << je.message() << std::endl;
        }
        delegate__(object_class);
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
    std::function<void(std::string)> delegate__;
};
}
}
#endif
