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
#include <rapp/cloud/text_to_speech.hpp>
/*
 * \brief Example to recognise words from an audio file with Google 
 */
int main()
{
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
     * All it does is receive a rapp::object::audio and we save it 
     */
    auto callback = [&](rapp::object::audio audio) { 
        if (audio.save("audio.wav")) {
            std::cout << "File saved" << std::endl;
        }
        else {
            std::cout << "Error: file not save\r\n";
        }
    };

    /*
     * We make a call to text_to_speech. We pass words or a sentence
     * and it becomes an audio.
     * For more information \see rapp::cloud::text_to_speech
     */
    ctrl.make_call<rapp::cloud::text_to_speech>("hello world", "en", callback);
    return 0;
}
