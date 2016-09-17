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

qr_detection::qr_detection(
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

void qr_detection::deserialise(std::string json) const
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
