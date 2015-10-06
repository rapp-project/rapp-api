#include "../includes/service/service_controller/service_controller.hpp"
#include "../includes/cloud/speechToText/speechToText.hpp"
#include "../includes/objects/audio/audio.hpp"

int main ( )
{
    rapp::services::service_controller ctrl;

    // Maybe we can move the LANG parameter in the Audio Class ?
    auto audio = std::make_shared<rapp::object::OGGfile>( "recording_sentence2.ogg" );
                                                             //"nao_wav_d05_a1.wav_mono16k.wav"
                                                             //"yes-no.wav"
                                                             //"nao_wav_d05_a1.wav" 
                                                             //"nao_ogg_d05_a1.ogg" 
                                                             //"email-robot.wav"
                                                             //"recording_yes.ogg"
                                                             //"recording_no.ogg"
                                                             //"recording_tuesday.ogg"

    assert ( audio );
    
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

    // Maybe we should move the parameter "user" to a Global Var, or to the Job Scheduler?
    //
    auto sphinx_handle = std::make_shared<rapp::cloud::speechToText>( audio,           // audio file
                                                                      "en",            // Language
                                                                      "rapp",          // user
                                                                      grammar,         // grammar ? (empty)
                                                                      words,           // words to be considered
                                                                      sentences,       // sentences to be considered
                                                                      callback );
    ctrl.runJob ( sphinx_handle );

    return 0;
}
