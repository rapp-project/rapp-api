#include "available_services.hpp"

namespace rapp {
namespace cloud {

available_services::available_services(std::function<void(std::vector<service>)> callback)
: http_request("GET /hop/available_services HTTP/1.1\r\n"),
  delegate_(callback)
{
    assert(callback);
}

void available_services::deserialise(std::string json) 
{
    std::cout << json;
    service services;
    std::vector<std::string> args;
    std::vector<service> vector_services;

    auto json_f = json::parse(json);

    if (!json.empty()) {
        
        // Get "response" from json
        const auto it = json_f.find("services");
        if (it == json_f.end()){
            throw std::runtime_error("no services in available_services");
        }
        else {

             //Fill the vector_services with names and urls
             for (auto it_s = it->begin(); it_s != it->end(); it_s++){

                 // Get 'name' from json
                auto name_it = it_s->find("name");
                if (name_it == it_s->end()) {
                    throw std::runtime_error("no name in services");
                }
                else {
                    services.first = name_it->get<std::string>();
                }

                // Get 'url' from json
                auto url_it = it_s->find("url");
                if (url_it == it_s->end()) {
                    throw std::runtime_error("no url in services");
                }
                else {
                    services.second = url_it->get<std::string>();
                }            

                vector_services.push_back(services);
             
             } 

           // Get "error" from json
             std::string error;
             rapp::misc::get_value_from_json("available_services", "error", json_f, error);

             if (!error.empty()) {
                 std::cerr << error << std::endl; 
             }
        }
    }
    
    delegate_(vector_services);
}


}
}
