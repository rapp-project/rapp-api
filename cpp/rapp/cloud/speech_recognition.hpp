#ifndef RAPP_CLOUD_SPEECH_RECOGNITION 
#define RAPP_CLOUD_SPEECH_RECOGNITION
#include "includes.ihh"
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
#include <rapp/objects/audio.hpp>
#include <rapp/cloud/asio/http_request.hpp>

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

/**
 * \class speech_recognition_sphinx4
 * \brief speech-to-text recognition using CMU sphinx4
 * \version 0.7.0
 * \date September 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class speech_recognition_sphinx4 : public http_request
{
public:
    /**
     * \brief construct a speechToText handler
     * \param audio_bytearray is the bytearray of the audio file used for speech recognition.
     * \note the audio file should be an inheriting class (\see objects/audio/audio.hpp)
     * \param audio_source is the source of the audio. It can be: "nao_ogg"
     *                                                            "nao_wav_1_ch"
     *                                                            "nao_wav_4_ch"
     *                                                            "headset"
     * \param language is the language used for speech to text
     * \param grammar is the Grammars used in Spc2Txt
     * \param user is the user token
     * \param words will be searched for in the audio
     * \param sentences will be under consideration
     * \param callback will be executed once the rapp cloud has responded
     */
    speech_recognition_sphinx4(
                                 const std::vector<rapp::types::byte> audio_data,
                                 const rapp::types::audio_source audio_src,
                                 const std::string language,
                                 const std::vector<std::string> grammar,
                                 const std::vector<std::string> words,
                                 const std::vector<std::string> sentences,
                                 std::function<void(std::vector<std::string> words)> callback
                              );
    /**
	 * \brief handle the rappl-platform JSON reply
	 */ 
    void deserialise(std::string json) const;

private:
    /// The callback called upon completion of receiving the detected words
    std::function<void(std::vector<std::string> words)> delegate_;
};

/**
 * \class set_denoise_profile
 * \brief setting the noising audio profile for speech recognition 
 * \version 0.7.0
 * \date September 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class set_noise_profile : public http_request
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
    set_noise_profile(
						 const std::vector<rapp::types::byte> audio_bytearray,
                         const rapp::types::audio_source audio_src
					   );

    /**
     * \brief handle platform reply (error notifications only)
     */
    void deserialise(std::string json) const;
};


}
}
#endif
