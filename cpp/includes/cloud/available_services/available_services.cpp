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
    /*
    std::vector<std::pair<std::string, std::string>> services;
    using namespace rapidjson;
    Document doc;
    doc.Parse(json);

    // parse JSON array 
    const Value& list  = doc["services"];
    const Value& error = doc["error"];

    assert(list.IsArray());
    assert(error.IsString());

    // get and check no errors
    std::string error_str = doc["error"].GetString();
    if (!error_str.empty()) {
        std::cerr << error_str << std::endl;
        return;
    }
    // check service list is an array
    if (!list.IsArray()) {
        std::cerr << "services JSON not an array" << std::endl;
        return;
    }
    // iterate service objects
    for (auto itr = list.Begin(); itr != list.End(); ++itr) {
        // each object has member `name` and member `url`
        std::pair<std::string, std::string> pair;
        auto name = itr->FindMember("name");
        if(name != itr->MemberEnd()) {
            pair.first = name->value.GetString();
        }
        else {
            std::cerr << "missing `name` member" << std::endl;
            return;
        }
        auto url = itr->FindMember("url");
        if (url != itr->MemberEnd()) {
            pair.second = url->value.GetString();
        }
        else {
            std::cerr << "missing `url` member" << std::endl;
            return;
        }
        services.push_back(pair);
    }

    delegate_(services);
    */
}


}
}
