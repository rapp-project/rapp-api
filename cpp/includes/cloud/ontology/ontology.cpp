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
    //http_request::make_multipart_form();
    http_request::add_content("json", json_doc.dump(-1), true); 
    http_request::close();
 }

void ontology_subclasses_of::deserialise(std::string json) const
{
    std::vector<std::string> classes;
    std::string current_class = "ontology_subclasses";

    auto json_f = json::parse(json);
    if (!json.empty()) {
        // Get "results" from json
        rapp::misc::get_value_from_json(current_class, "results", json_f, classes);
        //Get "error" from json
        std::string error;
        rapp::misc::get_value_from_json(current_class, "error", json_f, error);
        if (!error.empty()) {
            std::cerr << "ontology_subclasses_of JSON: " << error <<std::endl;
        }
    }
    else {
        throw std::runtime_error("json is empty");
    }

    delegate__(classes);
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
    std::vector<std::string> classes;
    std::string current_class = "ontology_superclasses";
    auto json_f = json::parse(json);
    if (!json.empty()) {
        // Get "results" from json
        rapp::misc::get_value_from_json(current_class, "results", json_f, classes);
        //Get "error" from json
        std::string error;
        rapp::misc::get_value_from_json(current_class, "error", json_f, error);
        if (!error.empty()) {
            std::cerr << "ontology_superclasses_of JSON: " << error <<std::endl;
        }
    }
    else {
        throw std::runtime_error("json is empty");
    }
    delegate__(classes);
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
    bool result;
    std::string current_class = "ontology_is_subsuperclass_of";
    auto json_f = json::parse(json);
    if (!json.empty()) {
        // Get "results" from json
        rapp::misc::get_value_from_json(current_class, "result", json_f, result);
        //Get "error" from json
        std::string error;
        rapp::misc::get_value_from_json(current_class, "error", json_f, error);
        if (!error.empty()) {
            std::cerr << "ontology_superclasses_of JSON: " << error <<std::endl;
        }
    }
    else {
        throw std::runtime_error("json is empty");
    }
    delegate__(result);
}

}
}
