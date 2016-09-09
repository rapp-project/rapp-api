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
#include "cloud/service_controller/service_controller.hpp"
#include "cloud/speech/set_denoise_profile.hpp"
#include "objects/audio/audio.hpp"
/*
 * \brief Example to take an audio for denoise
 */
int main()
{
    /*
     * The audio is loaded from its path to a audio class.
     * If you run the example inside examples folder, this path is valid.
     * In other cases, you'll have to change it for a proper one.
     */
    rapp::object::audio audio("data/object_classes_audio_1.ogg");

    /*
     * We have to say the source of the audio. In the case of the 
     * file above, its source is `nao_ogg`. In the case you take another
     * example, be careful with what source it has.
     * For more information /see rapp::cloud::set_noise_profile
     */
    std::string audio_source = "nao_ogg";

    /*
     * Construct the platform info setting the hostname/IP, port and authentication token
     * Then proceed to create a cloud controller.
     * We'll use this object to create cloud calls to the platform.
     */
    rapp::cloud::platform info = {"rapp.ee.auth.gr", "9001", "rapp_token"}; 
    rapp::cloud::service_controller ctrl(info);

    /*
     * We make a call to set_denoise to give tha audio and the data needed.
     * For more information \see rapp::cloud::set_denoise_profile
     */
    ctrl.make_call<rapp::cloud::set_denoise_profile>(audio.bytearray(), audio_source);
    return 0;
}
