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
 * \class speech_detection_google
 * \brief delegate speech-to-text to Google via RAPP
 * \version 0.7.0
 * \date 26 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
template <class T>
class speech_detection_google : public caller, public http_request
{
public:
	/**
	 * \brief construct the handler which will query the Google API
	 * \param  file is the audio file used for speech recognition.
     * \note the audio file should be an inheriting class (\see objects/audio/audio.hpp)
     * \param language defines the language used for speech recognition (e.g., 'en', 'gr', etc.)
     * \param user is required so that denoising can take place
     * \param callback is the functor/lambda/function pointer delegate that will receive the result
	 */
	speech_detection_google(
							  const T audiofile,
							  const std::string language,
							  const std::string user,
							  std::function<void(std::vector<std::string>, std::vector<std::string>)> callback
						   )
	: http_header("POST /hop/speech_detection_google HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()), 
      delegate_(callback)
    {
        assert(audiofile);
        std::string fname =  rapp::misc::random_boundary() + audiofile->extension(); 

        boost::property_tree::ptree tree;
        tree.put("language", language);
        tree.put("user", user);
        tree.put("audio_source", audiofile->audio_source());
        
		std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        std::string json = ss.str();
        http_post::add_content("json", json, false);

        auto bytes = audiofile->bytearray();
        http_post::add_content("file",fname, bytes);
        http_post::end();
       
    }

	/**
	 * \brief handle rapp-platform JSON reply
	 */
    void deserialise(std::string json) const
    {
        std::stringstream ss(json);
        std::vector<std::string> words;        
		std::vector<std::string> alternatives;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

            // JSON response is: { words: [], alternatives: [], error: '' } 
            for (auto child : tree.get_child("words")) {
                words.push_back(child.second.get_value<std::string>());
			}

			for (auto child : tree.get_child("alternatives")) {
				alternatives.push_back(child.second.get_value<std::string>());
			}

            // Check for error response from platform
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "speech_detection_google error: " << value << std::endl;
				}
            }
        }
        catch (boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "speech_detection_google::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate_(words, alternatives);
    }

    /**
    * \brief method to fill the buffer with http_post and http_header information
    * \param info is the data of the platform    
    */
    boost::asio::streambuf fill_buffer(rapp::cloud::platform info)
    {
           return std::move(http_request::fill_buffer(info));
    }

private:
    /// The callback called upon completion of receiving the detected words and alternatives
    std::function<void(std::vector<std::string>, std::vector<std::string>)> delegate_;
};
}
}
#endif
