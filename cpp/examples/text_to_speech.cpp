#include "cloud/service_controller/service_controller.hpp"
#include "cloud/speech/text_to_speech/text_to_speech.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 
///
///
int main(int argc, char* argv[])
{
    if (argc > 1) {
        // service controler
        rapp::cloud::platform_info info = {"localhost", "9001", "mytoken"}; 
        rapp::cloud::service_controller ctrl(info);

        // load audio from file
        auto callback = [&](std::unique_ptr<rapp::object::microphone_wav> audio)
                        { 
                            if(audio){
                                audio->save("audio.wav");
                            }
                            std::cout << "got reply\r\n";
                        };

        ctrl.make_call<rapp::cloud::text_to_speech>("hello kids", "en_US", callback);
        return 0;
    }
    else {
        std::cerr << "missing param\r\n";
        return 1;
    }
}
