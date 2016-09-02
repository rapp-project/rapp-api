#include "ontology.hpp"
namespace rapp {
namespace cloud {

ontology_subclasses_of::ontology_subclasses_of(
                                                std::string ontology_class,
                                                bool recursive,
                                                std::function<void(std::vector<std::string>)> callback
                                              )
: http_request("POST /hop/ontology_subclasses_of HTTP/1.1\r\n"), 
  delegate__(callback)
{
    http_request::make_multipart_form();
    json json_doc = {{"ontology_class", ontology_class},
                     {"recursive", recursive}};

    http_request::add_content("json", json_doc.dump(-1), true); 
    http_request::close();
 }

void ontology_subclasses_of::deserialise(std::string json) const
{
    if (json.empty()) {
        throw std::runtime_error("json is empty");
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
        std::cerr << "ontology_subclasses_of JSON: " << error <<std::endl;
    }
    else {
        delegate__(json_f["results"]);
    }
}

//Class Ontology_superclasses_of
ontology_superclasses_of::ontology_superclasses_of(
                                                    const std::string ontology_class,
                                                    bool recursive,
                                                    std::function<void(std::vector<std::string>)> callback
                                                  )
: http_request("POST /hop/ontology_superclasses_of HTTP/1.1\r\n"), 
  delegate__(callback)
{
    http_request::make_multipart_form();
    json json_doc = {{"ontology_class", ontology_class},
                     {"recursive", recursive}};
    http_request::add_content("json", json_doc.dump(-1), true); 
    http_request::close();
}   

void ontology_superclasses_of::deserialise(std::string json) const
{
    if (json.empty()) {
       throw std::runtime_error("json is empty");
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
        std::cerr << "ontology_superclasses_of JSON: " << error <<std::endl;
    }
    else {
        delegate__(json_f["results"]);
    }
}

//CLass Ontology_is_subsuperclass_of
ontology_is_subsuperclass_of::ontology_is_subsuperclass_of(
                                                             const std::string parent_class,
                                                             const std::string child_class,
                                                             bool recursive,
                                                             std::function<void(bool result)> callback
                                                          )
: http_request("POST /hop/ontology_is_subsuperclass_of HTTP/1.1\r\n"), 
  delegate__(callback)
{
    http_request::make_multipart_form();
    json json_doc = {{"parent_class", parent_class},
                     {"child_class", child_class},
                     {"recursive", recursive}};
    http_request::add_content("json", json_doc.dump(-1), true); 
    http_request::close();
}

void ontology_is_subsuperclass_of::deserialise(std::string json) const
{
    if (json.empty()) {
       throw std::runtime_error("json is empty");
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
        std::cerr << "ontology_subsuperclass_of JSON: " << error <<std::endl;
    }
    else {
        delegate__(json_f["result"]);
    }

}

}
}
