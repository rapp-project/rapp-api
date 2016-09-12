#ifndef RAPP_CLOUD_TEXT2SPEECH
#define RAPP_CLOUD_TEXT2SPEECH
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
 * \class text_to_speech
 * \brief request speech audio from text
 * \version 0.7.0
 * \date September 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class text_to_speech : public http_request
{
public:
    typedef rapp::object::audio audio_file;
	/**
	 * \brief construct handler which will request speech audio from text
	 * \param text is the text to be converted to audio
	 * \param language is language
	 * \callback will receive the speech audio object
	 */
	text_to_speech(
					 const std::string text,
					 const std::string language,
					 std::function<void(audio_file)> callback
				  );

    /**
     * \brief handle platform's JSON reply
     */
    void deserialise(std::string json) const;

private:
    /// 
    std::function<void(audio_file wav)> delegate_;
};
}
}
#endif
