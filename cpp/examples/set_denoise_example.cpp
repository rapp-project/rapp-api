#include "../includes/service/service_controller/service_controller.hpp"
#include "../includes/cloud/set_denoise_profile/set_denoise_profile.hpp"
#include "../includes/objects/audio/audio.hpp"
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
    if (argc == 4)
    {
        std::cout << "denoise file: " << argv[1] << std::endl;
        std::string file = argv[1];
        std::cout << "audio source: " << argv[2] << std::endl;
        std::string type = argv[2];
        std::cout << "denoise user: " << argv[3] << std::endl;
        std::string user = argv[3];
        rapp::services::service_controller ctrl;
        if (auto audio = std::make_shared<rapp::object::audio>(file))
        {
            auto set_denoise = std::make_shared<rapp::cloud::set_denoise_profile>(audio, user, type);
            ctrl.run_job(set_denoise);
        }
    }
    else
        std::cerr << "incorrect params" << std::endl;

    return 0;
}
