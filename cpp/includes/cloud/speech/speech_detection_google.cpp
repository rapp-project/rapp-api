#include "speech_detection_google.hpp"
namespace rapp {
namespace cloud {

speech_detection_google::speech_detection_google(
                          const std::vector<rapp::types::byte> audio_bytearray,
                          const std::string audio_source,
                          const std::string language,
                          std::function<void(std::vector<std::string>, 
                                             std::vector<std::vector<std::string>>)> callback
                       )
: http_request("POST /hop/speech_detection_google HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    json json_doc = {{"audio_source", audio_source},
                     {"language", language}};
    http_request::add_content("json", json_doc.dump(-1), true);
    std::string audio_type;
    if (audio_source == "nao_ogg") {
        audio_type = "ogg";
    }
    else {
        audio_type = "wav";
    }
    std::string fname = rapp::misc::random_boundary() + "." + audio_type;
    http_request::add_content("file", fname, audio_bytearray);
    http_request::close();
}

void speech_detection_google::deserialise(std::string json) const
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
        std::cout << json << std::endl;
        delegate_(json_f["words"], json_f["alternatives"]);
    }
}

}
}
