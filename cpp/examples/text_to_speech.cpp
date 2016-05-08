#include "../includes/cloud/service_controller/service_controller.hpp"
#include "../includes/cloud/text_to_speech/text_to_speech.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 
///
/// Pass as param a PNG image
///
int main(int argc, char* argv[])
{
    // service controler
    rapp::cloud::service_controller ctrl;
    std::vector<std::shared_ptr<rapp::cloud::asio_socket>> queue;

    // load the image from argv[1]
    auto callback = [&](std::unique_ptr<rapp::object::microphone_wav> audio)
                    { 
                        if(audio){
                            audio->save("audio.wav");
                        }
                        std::cout << "got reply\r\n";
                    };

    for (int i = 0; i < 10; i++){
        //ctrl.run_job(fdetect);
        auto fdetect = std::make_shared<rapp::cloud::text_to_speech>("hello kids", 
                                                                     "en_US", 
                                                                     "my_token",
                                                                     callback);
        queue.push_back(fdetect);
    }
    ctrl.run_jobs(queue);
    ctrl.stop();

    return 0;
}
