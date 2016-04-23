#include "../includes/cloud/service_controller/service_controller.hpp"
#include "../includes/cloud/text_to_speech/text_to_speech.hpp"
///
/// Pass as param a PNG image
/// TODO: Valigrind this example
///
int main(int argc, char* argv[])
{
    // service controler
    rapp::cloud::service_controller ctrl;

    // load the image from argv[1]
    auto callback = [&](std::unique_ptr<rapp::object::microphone_wav> audio)
                    { if(audio){audio->save("audio.wav");}};

    auto fdetect = std::make_shared<rapp::cloud::text_to_speech>("hello kids", 
                                                                 "en_US", 
                                                                 "my_token",
                                                                 callback);
    if (fdetect)
        ctrl.run_job(fdetect);

    return 0;
}
