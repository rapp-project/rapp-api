/**
 * Copyright 2015 RAPP
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * #http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <rapp/cloud/service_controller.hpp>
#include <rapp/cloud/speech_recognition_sphinx4.hpp>
#include <rapp/objects/audio.hpp>
/*
 * \brief Example to recognise words from an audio file with Sphinx4
 */
int main()
{
    using namespace std::string_literals;
    /*
     * Construct the platform info setting the hostname/IP, port and authentication token
     * Then proceed to create a cloud controller.
     * We'll use this object to create cloud calls to the platform.
     */
    rapp::cloud::platform info = {"rapp.ee.auth.gr", "9001", "rapp_token"}; 
    rapp::cloud::service_controller ctrl(info);

    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a vector with the words that they have
     * been recognized.
     */
    auto callback = [&](std::vector<std::string> words) { 
            if (words.size() != 0) {
                std::cout << "Words: " << std::endl;
                for (auto each_word : words) {
                    std::cout << each_word << std::endl;
                }
            }
            else {
                std::cout << "No words found" << std::endl;
            }
    };

    /*
     * The audio is loaded from its path to a audio class.
     * If you run the example inside examples folder, this path is valid.
     * In other cases, you'll have to change it for a proper one.
     */
    rapp::object::audio audio("data/yes-no.wav");

    /*
     * We have to say the source of the audio. In the case of the 
     * file above, its source is `nao_ogg`. In the case you take another
     * example, be careful with what source it has.
     * For more information /see rapp::cloud::speech_recognition_sphinx4
     *                      /see rapp::types::audio_source
     */
    rapp::types::audio_source audio_src = rapp::types::nao_wav_1_ch;

    /*
     *  \brief JSGF speech grammar format. It's an optional input, but with
     *  it we can achieve more accuracy in the recognition. 
     */
    std::string jsgf =  "#JSGF V1.0;\r\n\r\n";
                jsgf += "grammar simpleExample; \r\n\r\n";
                jsgf += "public <greet> = Yes | No;\r\n";

    /*
     * We make a call to speech_recognition_google to detect the words said
     * in a audio with sphinx4 tools.
     * For more information \see rapp::cloud::speech_recognition_sphinx
     */
    ctrl.make_call<rapp::cloud::speech_recognition_sphinx4>(audio.bytearray(), 
                                                            audio_src, 
                                                            "en",
                                                            std::vector<std::string>({{jsgf}}),
                                                            std::vector<std::string>({"yes", "no"}),
                                                            std::vector<std::string>({""}),
                                                            callback);
    return 0;
}
