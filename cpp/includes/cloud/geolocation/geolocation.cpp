#include "geolocation.hpp"
namespace rapp {
namespace cloud {

geolocation::geolocation(
             const std::string ipaddr,
             const std::string engine,
             std::function<void(std::string,
                                std::string,
                                std::string,
                                float,
                                float,
                                std::string,
                                std::string)> callback           )

: http_request("POST /hop/geolocation HTTP/1.1\r\n"), 
  delegate_(callback)
{

    std::string ss;
    json json_doc = {{"ipaddr", ipaddr},
                    {"engine", engine}};
    ss = json_doc.dump(4);
    http_request::add_content("json", ss, false); 
    http_request::close();
 
}

void geolocation::deserialise(std::string json) const
{
   
    std::string city;
    std::string country; 
    std::string country_code; 
    float latitude;
    float longtitude;
    std::string timezone; 
    std::string zip; 

    std::string  current_class = "geolocation";

    auto json_f = json::parse(json);

    if (!json.empty()) {

        // Get "city" from json
        rapp::misc::get_value_from_json( current_class, "city", json_f, city); 

        // Get "country" from json
        rapp::misc::get_value_from_json( current_class, "country", json_f, country);        

        // Get "country_code" from json
        rapp::misc::get_value_from_json( current_class, "country_code", json_f, country_code); 

        // Get "latitude" from json 
        rapp::misc::get_value_from_json( current_class, "latitude", json_f, latitude);
        
        // Get "longtitude" from json
        rapp::misc::get_value_from_json( current_class, "longtitude", json_f, longtitude);        

        // Get "timezone" from json
        rapp::misc::get_value_from_json( current_class, "timezone", json_f, timezone); 

        // Get "zip" from json
        rapp::misc::get_value_from_json( current_class, "zip", json_f, zip);
        
        // Get error from json
        std::string error;

        rapp::misc::get_value_from_json( current_class, "error", json_f, error);
        if (!error.empty()) {
            std::cerr << "cognitive_test_selector JSON error: " << error <<std::endl;
        }
    }
    else {
        throw std::runtime_error("json is empty");
    }

    delegate_(city,
              country,
              country_code,
              latitude,
              longtitude,
              timezone,
              zip);
}


}
}
