#include "../includes/service/service_controller/service_controller.hpp"
#include "../includes/cloud/speechToText/speechToText.hpp"
#include "../includes/objects/audio/audio.hpp"

int main ( int argc, char** argv )
{
    if ( argc == 2)
    {
        std::cout << "speech2text using: " << argv[1] << std::endl;
        std::string file = argv[1];
        rapp::services::service_controller ctrl;

        // Load file
        auto audio = std::make_shared<rapp::object::MicrophoneWAV>( file );
        //auto audio = std::make_shared<rapp::object::NAOSingleChannelWAV>( file );
        assert ( audio );

        std::cout << "audio source: " << audio->audio_source() << std::endl;

        // Keywords to search for
        std::vector<std::string> words { };

        // JSGF Grammar
        std::vector<std::string> grammar = 
{
"#JSGF V1.0\
public <basicCmd> = <query> <verb> <object>;\
<query> = (where | what | which | who | when);\
<verb> = (is | are);\
<object> = [the | a | my ] (keys | lunch | time | this | that | it | name | shoes | nurse | pills | lunch | remote | son | daugther );"
};

        // Complete setences
        std::vector<std::string> sentences {  };

        /*
        std::cout << "keywords: " << std::endl;
        for ( auto k : words )
           std::cout << "\t" << k << std::endl;

        std::cout << "sentences: " << std::endl;
        for ( auto s : sentences )
           std::cout << "\t" << s << std::endl;
        */

        std::cout << "grammar: " << std::endl;
        for ( auto g : grammar )
          std::cout << g << std::endl;

        // ...
        auto callback = [&]( std::vector<std::string> words  )
                           {
                               for ( const auto & str : words )
                                   std::cout << str << " ";
                               std::cout << std::endl;
                           };

        // Maybe we should move the parameter "user" to a Global Var, or to the Job Scheduler
        auto sphinx_handle = std::make_shared<rapp::cloud::speechToText>( audio,           // audio file
                                                                          "en",            // Language
                                                                          "rapp",          // user
                                                                          grammar,         // grammar ? (empty)
                                                                          words,           // words to be considered
                                                                          sentences,       // sentences to be considered
                                                                          callback );
        ctrl.runJob ( sphinx_handle );
    }
    else
       std::cerr << "no audio file argument" << std::endl;

    return 0;
}
