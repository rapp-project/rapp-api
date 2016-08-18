#include "available_services.hpp"

namespace rapp {
namespace cloud {

available_services::available_services(std::function<void(std::vector<service>)> callback)
: http_request("GET /hop/available_services HTTP/1.1\r\n"),
  delegate_(callback)
{
    assert(callback);
}

void available_services::deserialise(std::string json) const
{
    using namespace rapidjson;
    Document doc;
    doc.Parse(json);

    // parse JSON array 
    const Value& services = doc["services"];
    const Value& error    = doc["error"];

    assert(services.IsArray());
    assert(error.IsString());
    std::string error_str = doc["error"].GetString();
    if (!error_str.empty()) {
        std::cerr << error_str << std::endl;
        return;
    }
    if (!services.IsArray()) {
        std::cerr << "services JSON not an array" << std::endl;
        return;
    }
    /*
    for (Value::ConstIterator itr = services.Begin(); itr != services.End(); ++itr) {
        const Value& value = (*itr)["service"];
    }
    */

    // ...
    //delegate_(std::move(services));
}

void available_services::fill_buffer(
                                       boost::asio::streambuf & request,
                                       rapp::cloud::platform info
                                    )
{
    http_request::fill_buffer(request, info);
}

}
}
