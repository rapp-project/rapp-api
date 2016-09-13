#ifndef RAPP_CLOUD_SPEECH_TO_TEXT_GOOGLE 
#define RAPP_CLOUD_SPEECH_TO_TEXT_GOOGLE
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
 * \class speech_recognition_google
 * \brief delegate speech-to-text to Google via RAPP
 * \version 0.7.0
 * \date September 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class speech_recognition_google : public http_request
{
public:
	/**
	 * \brief construct the handler which will query the Google API
	 * \param audio_bytearray is the bytearray of the audio file used for speech recognition.
     * \note the audio file should be an inheriting class (\see objects/audio/audio.hpp)
     * \param audio_source is the source of the audio. It can be: "nao_ogg"
     *                                                            "nao_wav_1_ch"
     *                                                            "nao_wav_4_ch"
     *                                                            "headset"
     * \param language defines the language used for speech recognition (e.g., 'en', 'gr', etc.)
     * \param callback is the functor/lambda/function pointer delegate that will receive the result
	 */
	speech_recognition_google(
							   const std::vector<rapp::types::byte> audio_bytearray,
                               const rapp::types::audio_source audio_src,
							   const std::string language,
                               std::function<void(std::vector<std::string>, 
                                                  std::vector<std::vector<std::string>>)> callback
	  					     );
    /**
	 * \brief handle rapp-platform JSON reply
	 */
    void deserialise(std::string json) const;

private:
    /// The callback called upon completion of receiving the detected words and alternatives
    std::function<void(std::vector<std::string>, std::vector<std::vector<std::string>>)> delegate_;
};
}
}
#endif
