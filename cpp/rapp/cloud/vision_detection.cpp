#include "vision_detection.hpp"
namespace rapp {
namespace cloud {

///Class face_detection
face_detection::face_detection(
                                const rapp::object::picture & image,
                                bool fast,
                                std::function<void(std::vector<rapp::object::face>)> callback
                              )
: http_request("POST /hop/face_detection HTTP/1.1\r\n"),
  delegate_(callback)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    json json_doc = {{"fast", fast}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

void face_detection::deserialise(std::string json) const
{   
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    std::vector<rapp::object::face> faces;
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
        auto it_faces = json_f.find("faces");
        for (auto it = it_faces->begin(); it != it_faces->end(); it++ ) {
            faces.push_back(rapp::object::face(it));
        }
        delegate_(faces);
    }
}

/// Class door_angle_detection
door_angle_detection::door_angle_detection(
                                            const rapp::object::picture & image,
                                            std::function<void(double door_angle)> callback
                                          )
: http_request("POST /hop/hazard_detection_door_check HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

void door_angle_detection::deserialise(std::string json) const
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
        std::cerr << "error JSON: " << error <<std::endl;
    }
    else {
        delegate_(json_f["door_angle"]);
    }
}

/// Class light_detection
light_detection::light_detection(
                                  const rapp::object::picture & image,
                                  std::function<void(int light_level)> callback
                                )
: http_request("POST /hop/hazard_detection_light_check HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

void light_detection::deserialise(std::string json) const
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
        std::cerr << "error JSON: " << error <<std::endl;
    }
    else {
        delegate_(json_f["light_level"]);
    }
}

/// Class human_detection
human_detection::human_detection(
                                  const rapp::object::picture & image,
                                  std::function<void(std::vector<rapp::object::human>)> callback
                                )
: http_request("POST /hop/human_detection HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

void human_detection::deserialise(std::string json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    std::vector<rapp::object::human> humans;
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
        auto it_human = json_f.find("humans");
        for (auto it = it_human->begin(); it != it_human->end(); it++ ) {
            humans.push_back(rapp::object::human(it));
        }
        delegate_(humans);
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
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    json json_doc = {{"user", user},
                     {"limit", limit}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::add_content("file", fname, image.bytearray());
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
        auto it_center = json_f.find("found_centers");
        for (auto it = it_center->begin(); it != it_center->end(); it++) {
            points.push_back(rapp::object::point(it));
        }
        delegate_(json_f["found_names"],
                  points, 
                  json_f["found_scores"],
                  json_f["result"]);
    }
}

}
}
