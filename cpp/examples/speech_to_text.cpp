#include "../includes/service/service_controller/service_controller.hpp"
#include "../includes/cloud/speechToText/speechToText.hpp"
#include "../includes/objects/audio/audio.hpp"

int main ( )
{
    rapp::services::service_controller ctrl;

    if ( auto audio = std::make_shared<rapp::object::audio>( "terminator_1.wav" ) )
    {
        std::vector<std::string> grammar;
        std::vector<std::string> words;      //{"yes"};
        std::vector<std::string> sentences; //{"yes","no"};

        auto callback = [&]( std::vector<std::string> words  )
                           {
                               for ( const auto & str : words )
                                   std::cout << str << " ";
                               std::cout << std::endl;
                           };

        auto sphinx_handle = std::make_shared<rapp::cloud::speechToText>( audio,           // audio file
                                                                          "en",            // Language
                                                                          "testuser",      // user
                                                                          "headset",  // Audio Source Type
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
