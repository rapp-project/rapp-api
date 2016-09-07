#include "path_planning.hpp"
namespace rapp {
namespace cloud {

// Class plan_path_2d
plan_path_2d::plan_path_2d(
                            const std::string map_name,
                            const std::string robot_type,
                            const std::string algorithm,
                            const rapp::object::pose_stamped start,
                            const rapp::object::pose_stamped goal,
                            std::function<void(rapp::object::planned_path)> callback
                          )
: http_request("POST /hop/path_planning_plan_path_2d HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    json json_str = {{"map_name", map_name},
                     {"robot_type", robot_type},
                     {"algorithm", algorithm},
                     {"start", start.to_json()},
                     {"goal", goal.to_json()}};
    http_request::add_content("json", json_str.dump(-1), true);
    http_request::close();
}

void plan_path_2d::deserialise(std::string json) const
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
        delegate_(rapp::object::planned_path(json_f));
    }
}

// Class path_upload_map
path_upload_map::path_upload_map(
                                  const rapp::object::picture & png_file,
                                  const rapp::object::yaml & yaml_file,
                                  const std::string map_name,
                                  std::function<void(std::string)> callback
                                )
: http_request("POST /hop/path_upload_map HTTP/1.1\r\n"), 
  delegate_(callback)
{

    http_request::make_multipart_form();
    json json_doc = {{"map_name", map_name}};
    http_request::add_content("json", json_doc.dump(-1), true);
    std::string png_fname = rapp::misc::random_boundary() + ".png";
    auto imagebytes = png_file.bytearray();
    http_request::add_content("png_file", png_fname, imagebytes);
    //ymal file
    std::string yaml_fname = rapp::misc::random_boundary() + ".yaml";
    std::string yaml_data = yaml_file.get_string();
    std::vector<rapp::types::byte> yaml_bytes(yaml_data.begin(), yaml_data.end());
    http_request::add_content("yaml_file", yaml_fname, yaml_bytes);
    http_request::close();
}

 void path_upload_map::deserialise(std::string json) const
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
        delegate_(error);
    }
 }
}
}
