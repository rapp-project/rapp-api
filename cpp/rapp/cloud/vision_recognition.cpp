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

object_detection_learn_object::object_detection_learn_object(
                                                              const rapp::object::picture & image,
                                                              const std::string name,
                                                              const std::string user,
                                                              std::function<void(int)> callback
                                                            )
: http_request("POST /hop/object_detection_learn_object HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    json json_doc = {{"name", name},
                     {"user", user}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}
    
void object_detection_learn_object::deserialise(std::string json) const {

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
        std::cerr << "error JSON: " << error <<std::endl;
    }
    else {
        delegate_(json_f["result"]);
    }

}

object_detection_clear_models::object_detection_clear_models(
                                                              const std::string user,
                                                              std::function<void(int)> callback
                                                            )
: http_request("POST /hop/object_detection_clear_models HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    json json_doc = {{"user", user}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}
    
void object_detection_clear_models::deserialise(std::string json) const {

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
        std::cerr << "error JSON: " << error <<std::endl;
    }
    else {
        delegate_(json_f["result"]);
    }

}

object_detection_load_models::object_detection_load_models(
                                                            const std::string user,
                                                            const std::vector<std::string> names,
                                                            std::function<void(int)> callback
                                                          )
: http_request("POST /hop/object_detection_load_models HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    json json_doc = {{"user", user},
                     {"names", names}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}
void object_detection_load_models::deserialise(std::string json) const {

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
        std::cerr << "error JSON: " << error <<std::endl;
    }
    else {
        delegate_(json_f["result"]);
    }

}

object_detection_find_objects::object_detection_find_objects(
                                                              const rapp::object::picture & image,
                                                              const std::string user,
                                                              const int limit,
                                                              std::function<void(std::vector<std::string>,
                                                                                 std::vector<rapp::object::point>, 
                                                                                 std::vector<double>,
                                                                                 int)> callback
                                                             )
: http_request("POST /hop/object_detection_find_objects HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    json json_doc = {{"user", user},
                     {"limit", limit}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

void object_detection_find_objects::deserialise(std::string json) const {

   if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    std::vector<rapp::object::point> points;
    nlohmann::json json_f;
    try {
        json_f = json::parse(json);
    }
    catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
    auto error = misc::get_json_value<std::string>("error", json_f);
    if (!error.empty()) {
        std::cerr << "error JSON: " << error <<std::endl;
    }
    else {
        // @BUG
        auto it_center = json_f.find("found_centers");
        for (auto it = it_center->begin(); it != it_center->end(); it++) {
            auto it_points = it->find("position");
            points.push_back(rapp::object::point(it_points));
        }
        delegate_(json_f["found_names"],
                  points, 
                  json_f["found_scores"],
                  json_f["result"]);
    }
}

qr_recognition::qr_recognition(
                               const rapp::object::picture & image,
                               std::function<void(std::vector<rapp::object::qr_code>)> callback
                             )
: http_request("POST /hop/qr_detection HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

void qr_recognition::deserialise(std::string json) const
{
    std::vector<rapp::object::qr_code> qr_codes;
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
        std::cerr << "error JSON: " << error <<std::endl;
    }
    else {
        unsigned int i = 0;
        for (auto & obj : json_f["qr_centers"]) {
            qr_codes.push_back(rapp::object::qr_code(obj["x"], obj["y"], json_f["qr_messages"].at(i)));
            i++;
        }
        delegate_(qr_codes);
    }
}


}
}
