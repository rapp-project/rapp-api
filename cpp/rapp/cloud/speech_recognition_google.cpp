#include "speech_recognition_google.hpp"
namespace rapp {
namespace cloud {

speech_recognition_google::speech_recognition_google(
                                                      const std::vector<rapp::types::byte> audio_bytearray,
                                                      const rapp::types::audio_source audio_src,
                                                      const std::string language,
                                                      std::function<void(std::vector<std::string>, 
                                                                         std::vector<std::vector<std::string>>)> callback
                                                    )
: http_request("POST /hop/speech_detection_google HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    std::string audio_type;
    std::string audio_format;
    switch(audio_src) {
        case 0: 
            audio_type = "nao_ogg";
            audio_format = "ogg";
            break;
        case 1:
            audio_type = "nao_wav_1_ch";
            audio_format = "wav";
            break;
        case 2:
            audio_type = "nao_wav_4_ch";
            audio_format = "wav";
            break;
        case 3:
            audio_type = "headset";
            audio_format = "wav";
            break;
        default:
            std::cerr << "Error: not the correct audio source" <<std::endl;
    }

    json json_doc = {{"audio_source", audio_type},
                     {"language", language}};
    http_request::add_content("json", json_doc.dump(-1), true);
    std::string fname = rapp::misc::random_boundary() + "." + audio_format;
    http_request::add_content("file", fname, audio_bytearray);
    http_request::close();
}

void speech_recognition_google::deserialise(std::string json) const
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
        std::cerr << "error JSON: " << error << std::endl;
    }
    else {
        delegate_(json_f["words"], json_f["alternatives"]);
    }
}

}
}
