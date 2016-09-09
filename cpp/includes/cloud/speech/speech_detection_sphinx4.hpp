#ifndef RAPP_CLOUD_SPEECH_TO_TEXT_SPHINX4
#define RAPP_CLOUD_SPEECH_TO_TEXT_SPHINX4
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
 * \class speech_detection_sphinx4
 * \brief speech-to-text recognition using CMU sphinx4
 * \version 0.7.0
 * \date September 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class speech_detection_sphinx4 : public http_request
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
    speech_detection_sphinx4(
							  const std::vector<rapp::types::byte> audio_bytearray,
                              const std::string audio_source,
                              const std::string language,
							  const std::string user,
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
}
}
#endif
