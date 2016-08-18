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
    /*
    if (!services.IsArray()) {
        throw std::runtime_error("services JSON not an array");
    }
    for (Value::ConstIterator itr = audios.Begin(); itr != audios.End(); ++itr) {
        const Value& value = (*itr)["metadata"];
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
