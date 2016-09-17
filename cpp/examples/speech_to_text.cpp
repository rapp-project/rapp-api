#include <rapp/cloud/service_controller.hpp>
#include <rapp/cloud/speech_detection_sphinx4.hpp>
#include <rapp/objects/audio.hpp>
#include <boost/program_options.hpp>
#include <string>
#include <fstream>
#include <streambuf>

namespace po = boost::program_options;

// A helper function to simplify the main part.
template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
    return os;
}

// load a JSGF text file to a string
std::string load_jsgf(const std::string filename)
{
    std::ifstream t(filename);
    if (!t.is_open())
        throw std::runtime_error("could not open: "+filename);
    std::string str;
    t.seekg(0, std::ios::end);   
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);
    str.assign((std::istreambuf_iterator<char>(t)),
                std::istreambuf_iterator<char>());
    return str;
}

///
/// Query the CMU Sphinx4 engine for keywords and sentences using a WAV file
/// argv[1]: audio file
/// argv[2]: audio source type
/// argv[3]: language
/// argv[4]: user
/// argv[5]: words to search for - OPTIONAL
/// argv[6]: sentences to search for - OPTIONAL
/// argv[7]: grammar file (JSGF text file) - OPTIONAL
///
int main(int argc, char* argv[])
{
    try
    {
        po::options_description desc("Allowed options - See headers `audio.hpp` and `speech_detection_sphinx4.hpp` for details");
        desc.add_options()
        ("help", "produce help message")
        ("audio", po::value<std::string>(), "(required) the wav/pcm audio input")
        ("audio-source", po::value<std::string>(), "(required) the audio source type")
        ("lang", po::value<std::string>(), "(required) set language, e.g: `en` or `gr`")
        ("user", po::value<std::string>(), "(required) set user, e.g: rapp")
        ("words", po::value<std::vector<std::string>>()->multitoken(), 
                  "(optional) keyword search, e.g: key book beer")
        ("sentences", po::value<std::vector<std::string>>()->multitoken(),
                   "(optional) sentence matching, e.g: find my keys")
        ("jsgf", po::value<std::string>(), "(optional) JSGF grammar file");

        po::positional_options_description p;
        p.add("input-file", -1);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
        po::notify(vm);

        int checks = 0;
        std::string audio_file, audio_source, lang, user, jsgf = "";
        std::vector<std::string> words = {}, sentences = {};

        if (vm.count("help")) {
            std::cout << "Usage: options_description [options]\n";
            std::cout << desc;
            return 0;
        }
        if (vm.count("audio")) {
            std::cout << "audio: " << vm["audio"].as<std::string>() << "\n";
            checks++;
            audio_file = vm["audio"].as<std::string>();
        }
        if (vm.count("audio-source")) {
            std::cout << "audio-source: " << vm["audio-source"].as<std::string>() << "\n";
            checks++;
            audio_source = vm["audio-source"].as<std::string>();
        }
        if (vm.count("lang")) {
            std::cout << "lang: " << vm["lang"].as<std::string>() << "\n";
            checks++;
            lang = vm["lang"].as<std::string>();
        }
        if (vm.count("user")) {
            std::cout << "user: " << vm["user"].as<std::string>() << "\n";
            checks++;
            user = vm["user"].as<std::string>();
        }
        if (vm.count("words")) {
            std::cout << "words: " << vm["words"].as<std::vector<std::string>>() << "\n";
            words =  vm["words"].as<std::vector<std::string>>();
        }
        if (vm.count("sentences")) {
            std::cout << "sentences: " << vm["sentences"].as<std::vector<std::string>>() << "\n";
            sentences = vm["sentences"].as<std::vector<std::string>>();
        }
        if (vm.count("jsgf")) {
            std::cout << "JSGF: " << vm["jsgf"].as<std::string>() << "\n";  
            jsgf =  vm["jsgf"].as<std::string>();
        }

        // we have the required params set
        if (checks == 4) {
			rapp::cloud::platform_info info = {"localhost", "9001", "mytoken"}; 
			rapp::cloud::service_controller ctrl(info);

            std::shared_ptr<rapp::object::audio> audio;
            std::vector<std::string> gram;

            if (audio_source == "microphone_wav")
                audio = std::make_shared<rapp::object::microphone_wav>(audio_file);
            else if (audio_source == "nao_single_channel_wav")
                audio = std::make_shared<rapp::object::nao_single_channel_wav>(audio_file);
            else if (audio_source == "nao_quad_channel_wav")
                audio = std::make_shared<rapp::object::nao_quad_channel_wav>(audio_file);
            else if (audio_source == "ogg")
                audio = std::make_shared<rapp::object::ogg>(audio_file);
            else
                throw std::runtime_error("uknown audio source");

            assert(audio);
            if (!jsgf.empty()) {
                gram.push_back(load_jsgf(jsgf));
            }
            if (audio) {
                // the callback
                auto callback = [&](std::vector<std::string> words)
                                {
                                    for (const auto & str : words)
                                        std::cout << str << " ";
                                    std::cout << std::endl;
                                };

                // make the call
                ctrl.make_call<rapp::cloud::speech_detection_sphinx4>(audio,
                                                                      lang,
                                                                      user,
                                                                      gram,
                                                                      words,      
                                                                      sentences,
                                                                      callback);
            }
        }
        else {
            std::cerr << "missing required arguments -- please see \"--help\"\n";
        }
    }
    catch(std::exception & e) {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch(...) {
        std::cerr << "Exception of unknown type!\n";
    }

    return 0;
}
