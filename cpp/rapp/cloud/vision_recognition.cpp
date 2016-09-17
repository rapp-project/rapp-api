#include "vision_recognition.hpp"
namespace rapp {
namespace cloud {

object_recognition::object_recognition(
                                        const rapp::object::picture & image,
                                        std::function<void(std::string)> callback
                                      )
: http_request("POST /hop/object_recognition_caffe HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();

}
/**
 * \brief handle the rapp-platform JSON reply
 */
void object_recognition::deserialise(std::string json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    try {
        json_f = json::parse(json);
    }
    catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
    auto error = misc::get_json_value<std::string>("error", json_f);
    if (!error.empty()) {
        std::cerr << "Error JSON: " << error <<std::endl;
    }
    else {
        delegate_(json_f["object_class"]);
    }    
}

}
}
