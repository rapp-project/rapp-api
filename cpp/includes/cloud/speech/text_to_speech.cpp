#include "text_to_speech"
namespace rapp {
namespace cloud {

text_to_speech::text_to_speech(
                 const std::string text,
                 const std::string language,
                 std::function<void(audio_file)> callback
              )
: http_request("POST /hop/text_to_speech HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    json json_doc = {{"text", text},
                     {"language", language}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

void text_to_speech::deserialise(std::string json) const
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
        std::vector<rapp::types::byte> bytearray;
        std::string decoded = rapp::misc::decode64(json_f["payload"]);
        std::copy(decoded.begin(), decoded.end(), std::back_inserter(bytearray));
        delegate_(rapp::object::audio(bytearray));
    }
}

}
}
