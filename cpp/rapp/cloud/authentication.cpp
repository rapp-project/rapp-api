#include "authentication.hpp"
namespace rapp {
namespace cloud {

login_user::login_user(std::string username,
                       std::string password,
                       std::string device_token,
                       std::function<void(std::string)> callback)
: http_request("POST /hop/login_user HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    json json_doc = {{"username", username},
                     {"password", password},
                     {"device_token", device_token}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
 
}

void login_user::deserialise(std::string json)
{
    if (json.empty()) {
       throw std::runtime_error("Empty json");
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
        delegate_(json_f["token"]);
    }
}

register_user_from_platform::register_user_from_platform(
                                                           std::string creator_username,
                                                           std::string creator_password,
                                                           std::string new_user_username,
                                                           std::string new_user_password,
                                                           std::string language,
                                                           std::function<void(std::string)> callback
                                                        )
: http_request("POST /hop/register_user_from_platform HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    json json_doc = {{"creator_username", creator_username},
                     {"creator_password", creator_password},
                     {"new_user_username", new_user_username},
                     {"new_user_password", new_user_password},
                     {"language", language}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
 
}

void register_user_from_platform::deserialise(std::string json)
{
    if (json.empty()) {
       throw std::runtime_error("Empty json");
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
        delegate_(json_f["suggested_username"]);
    }
}

register_user_from_store::register_user_from_store(
                                                    std::string username,
                                                    std::string password,
                                                    std::string device_token,
                                                    std::string language,
                                                    std::function<void(std::string)> callback
                                                  )
: http_request("POST /hop/register_user_from_platform HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    json json_doc = {{"username", username},
                     {"password", password},
                     {"device_token", device_token},
                     {"language", language}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
 
}

void register_user_from_store::deserialise(std::string json)
{
    if (json.empty()) {
       throw std::runtime_error("Empty json");
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
        delegate_(json_f["suggested_username"]);
    }
}

}
}
