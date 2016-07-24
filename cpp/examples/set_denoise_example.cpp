#include "cloud/service_controller/service_controller.hpp"
#include "cloud/speech/set_denoise_profile/set_denoise_profile.hpp"
#include "objects/audio/audio.hpp"
#include <boost/filesystem.hpp>
///
/// set a denoise profile for a specific user
/// argv[1] : audio file
/// argv[2] : audio type (@see audio.hpp) e.g.: `microphone_wav`, 
///                                             `nao_single_channel_wav`
///                                             `nao_quad_channel_wav`
///                                             `ogg`
/// argv[3] : user (by default: `rapp`)
///
int main(int argc, char ** argv)
{
    if (argc == 4) {
        std::cout << "denoise file: " << argv[1] << std::endl;
        std::string file = argv[1];
        std::cout << "audio source: " << argv[2] << std::endl;
        std::string type = argv[2];
        std::cout << "denoise user: " << argv[3] << std::endl;
        std::string user = argv[3];
		std::string token = "my_token";

		if (!boost::filesystem::exists(file)) {
			std::cerr << "file doesn't exist\r\n";
			return 1;
		}

        // Service Controller 
        rapp::cloud::platform_info info = {"localhost", "9001", "mytoken"}; 
        rapp::cloud::service_controller ctrl(info);

        std::shared_ptr<rapp::object::audio> audio;

        if (type == "microphone_wav")
            audio = std::make_shared<rapp::object::microphone_wav>(file);

        else if (type == "nao_single_channel_wav")
            audio = std::make_shared<rapp::object::nao_single_channel_wav>(file);

        else if (type == "nao_quad_channel_wav")
            audio = std::make_shared<rapp::object::nao_quad_channel_wav>(file);

        else if (type == "ogg")
            audio = std::make_shared<rapp::object::ogg>(file);

        else
            throw std::runtime_error("uknown audio source");

        if (audio) {
            ctrl.make_call<rapp::cloud::set_denoise_profile>(audio, user);
        }
    }
    else {
        std::cerr << "incorrect params" << std::endl;
	}
    return 0;
}
