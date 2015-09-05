#include "../includes/service/service_controller/service_controller.hpp"
//#include "../includes/cloud/setDenoiseProfile/setDenoiseProfile.hpp"
#include "../includes/objects/audio/audio.hpp"

int main ( )
{
    rapp::services::service_controller ctrl;
    
    if ( auto wav = std::make_shared<rapp::object::audio>( "terminator1.wav" ) )
    {
        //auto set_denoise = std::make_shared<rapp::cloud::setDenoiseProfile>( wav, "alex" );
        //ctrl.runJob ( set_denoise );
    }
    else
        std::cerr << "Error loading audio" << std::endl;

    return 0;
}
