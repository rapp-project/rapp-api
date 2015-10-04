#include "../includes/service/service_controller/service_controller.hpp"
#include "../includes/cloud/speechToText/speechToText.hpp"
#include "../includes/objects/audio/audio.hpp"

int main ( )
{
    rapp::services::service_controller ctrl;

    if ( auto audio = std::make_shared<rapp::object::audio>( 
							     //"nao_wav_d05_a1.wav_mono16k.wav"
                                                             //"yes-no.wav"
                                                             //"nao_wav_d05_a1.wav" 
                                                             //"nao_ogg_d05_a1.ogg" 
							     "recording_sentence2.ogg"
							     //"email-robot.wav"
							     //"recording_yes.ogg"
							     //"recording_no.ogg"
							     //"recording_tuesday.ogg"
                                                           ) )
    {
        std::vector<std::string> grammar;
        std::vector<std::string> words     //{"tuesday","monday"};
					   //{"yes","no"};
					   //{"I", "want", "to", "go", "out"};
					   //{"email","robot"};
					   {"check","my","email","robot"};


        std::vector<std::string> sentences //{"tuesday","monday"};
					   //{"yes","no"};
					   //{"I", "want", " to",  "go", "out"};
					   //{"email", "robot"};
					   {"check","my","email","robot"};

        auto callback = [&]( std::vector<std::string> words  )
                           {
                               for ( const auto & str : words )
                                   std::cout << str << " ";
                               std::cout << std::endl;
                           };

        auto sphinx_handle = std::make_shared<rapp::cloud::speechToText>( audio,           // audio file
                                                                          "en",            // Language
                                                                          "rapp",          // user
                                                                          //"headset",
                                                                          //"nao_wav_1_ch",
                                                                          //"nao_wav_4_ch",
                                                                          "nao_ogg",       // Audio Source Type
                                                                          grammar,         // grammar ? (empty)
                                                                          words,           // words to be considered
                                                                          sentences,       // sentences to be considered
                                                                          callback );
        ctrl.runJob ( sphinx_handle );
    }
    else
        std::cerr << "Error loading audio" << std::endl;



    return 0;
}
