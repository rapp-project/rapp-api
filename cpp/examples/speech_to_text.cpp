#include "../includes/service/service_controller/service_controller.hpp"
#include "../includes/cloud/speech_detection_sphinx4/speech_detection_sphinx4.hpp"
#include "../includes/objects/audio/audio.hpp"
#include <boost/program_options.hpp>
namespace po = boost::program_options;
///
/// Query the CMU Sphinx4 engine for keywords and sentences using a WAV file
/// argv[1]: audio file
/// argv[2]: language
/// argv[3]: user
/// argv[4]: grammar file (BNF/JSGF text file) - OPTIONAL
/// argv[5]: words to search for
/// argv[6]: sentences to search for
///
int main(int argc, char** argv)
{
    try
    {
        po::options_description desc("Allowed options - Please only use WAV files (PCM 16/WAV)");
        desc.add_options()
        ("audio", "the WAV audio input file")
        ("lang", "set the language, `en`, `gr`, etc...")
        ("user", "set the user, e.g. `rapp`")
        ("lang", "set the language, `en`, `gr`, etc...")
        ("words", "keywords to search for, e.g: \"key\", \"book\", \"beer\" - optional")
        ("sentences", "keywords to search for, e.g: \"key\", \"book\", \"beer\" - optional")
        ("jsgf", "JSGF/BNF grammar text file - optional");

        // TODO: Parse options and execute example
    }
    catch(std::exception & e)
    {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch(...) 
    {
        std::cerr << "Exception of unknown type!\n";
    }

    /*
    rapp::services::service_controller ctrl;
    // Load file
    auto audio = std::make_shared<rapp::object::MicrophoneWAV>(file);
    assert ( audio );
    // Keywords to search for
    std::vector<std::string> words { };
    // Complete setences
    std::vector<std::string> sentences {  };
    // ...
    auto callback = [&]( std::vector<std::string> words  )
                       {
                           for ( const auto & str : words )
                               std::cout << str << " ";
                           std::cout << std::endl;
                       };
    // Maybe we should move the parameter "user" to a Global Var, or to the Job Scheduler
    auto sphinx4_call = std::make_shared<rapp::cloud::speechToText>( audio,           // audio file
                                                                      "en",            // Language
                                                                      "rapp",          // user
                                                                      grammar,         // grammar ? (empty)
                                                                      words,           // words to be considered
                                                                      sentences,       // sentences to be considered
                                                                      callback );
    ctrl.runJob(sphinx4_call);
    */

    return 0;
}
