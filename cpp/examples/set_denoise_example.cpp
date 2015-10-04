#include "../includes/service/service_controller/service_controller.hpp"
#include "../includes/cloud/setDenoiseProfile/setDenoiseProfile.hpp"
#include "../includes/objects/audio/audio.hpp"

int main ( int argc, char ** argv )
{
    rapp::services::service_controller ctrl;

    if ( auto audio = std::make_shared<rapp::object::audio>(
						 	     "denoise_source.wav"
                                                            //"silence_sample.wav"
                                                            // "silence_wav_d05_a1.wav"
                                                            //"silence_ogg_d05_a1.ogg" 
                                                           ) )
    {
        std::cout << "set denoise using: " << argv[1] << std::endl;
        std::string file = argv[1];
        rapp::services::service_controller ctrl;

        auto audio = std::make_shared<rapp::object::audio>( file
                                                                //"denoise_source.wav"
                                                                //"silence_sample.wav"
                                                                // "silence_wav_d05_a1.wav"
                                                                //"silence_ogg_d05_a1.ogg" 
                                                               );
        assert( audio );        
        auto set_denoise = std::make_shared<rapp::cloud::setDenoiseProfile>( audio, 
                                                                             "rapp",
                                                                             //"nao_wav_1_ch"
                                                                             //"nao_wav_4_ch" 
                                                                             "nao_ogg" 
                                                                           ); 
        ctrl.runJob ( set_denoise );
    }
    else
        std::cerr << "you didn't specify a denoising audi file" << std::endl;
    return 0;
}
