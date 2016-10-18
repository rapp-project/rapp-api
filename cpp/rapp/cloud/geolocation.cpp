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
                                            std::string,
                                            std::string)> callback           
                         )
: http_request("POST /hop/geolocation HTTP/1.1\r\n"), 
  delegate_(callback)
{

    http_request::make_multipart_form();
    json json_doc = {{"ipaddr", ipaddr},
                    {"engine", engine}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
 
}

void geolocation::deserialise(std::string json) const
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
        delegate_(json_f["city"],
                  json_f["country"], 
                  json_f["country_code"], 
                  json_f["latitude"], 
                  json_f["longtitude"], 
                  json_f["region"],
                  json_f["timezone"],
                  json_f["zip"]);
    }
}


}
}
