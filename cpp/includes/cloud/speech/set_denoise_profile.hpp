#ifndef RAPP_CLOUD_SET_DENOISE_PROFILE
#define RAPP_CLOUD_SET_DENOISE_PROFILE
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
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class set_denoise_profile
 * \brief setting the noising audio profile for speech recognition 
 * \version 0.7.0
 * \date September 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class set_denoise_profile : public http_request
{
public:
    /**
     * \brief set a de-noising profile for a user (for speech recognition) 
	 * \note This class does not return something, it only captures an error
     * \param audio_bytearray is the noise audio bytearray used for de-noising
     * \param audio_source is the source of the audio. It can be: "nao_ogg"
     *                                                            "nao_wav_1_ch"
     *                                                            "nao_wav_4_ch"
     *                                                            "headset"
     */
    set_denoise_profile(
						 const std::vector<rapp::types::byte> audio_bytearray,
                         std::string audio_source
					   );

    /**
     * \brief handle platform reply (error notifications only)
     */
    void deserialise(std::string json) const;

};
}
}
#endif
