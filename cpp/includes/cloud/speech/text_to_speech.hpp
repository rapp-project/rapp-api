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
 * \date 15 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class text_to_speech : public caller, public http_request
{
public:
    typedef rapp::object::microphone_wav wav_file;
	/**
	 * \brief construct handler which will request speech audio from text
	 * \param text is the text to be converted to audio
	 * \param language is language
	 * \callback will receive the speech audio object
	 */
	text_to_speech(
					 const std::string text,
					 const std::string language,
					 std::function<void(wav_file)> callback
				  )
	: http_header("POST /hop/ontology_subclasses_of HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()), 
      delegate_(callback)
	{
        boost::property_tree::ptree tree;
        tree.put("text", text);
        tree.put("language", language);

        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

        std::string json = ss.str();
        http_post::add_content("json", json, false); 
        http_post::end();
     }

    /**
     * \brief handle platform's JSON reply
     */
    void deserialise(std::string json) const
    {
        std::stringstream ss(json);
        std::vector<rapp::types::byte> bytearray;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

		    // capture audio payload (base64-encoded)	
            for (auto child : tree.get_child("payload")) {
                // base64-encoded audio
                std::string result = child.second.get_value<std::string>();
                std::string decoded = rapp::misc::decode64(result);
                std::copy(decoded.begin(), decoded.end(), std::back_inserter(bytearray));
            }

			// get platform errors
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "text_to_speech JSON error: " << value << std::endl;
                }
            }
	    }
        catch (boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "text_to_speech::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        // create wav file and move it to the delegate
        auto wav = rapp::object::microphone_wav(bytearray);
        delegate_(std::move(wav));
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
    /// 
    std::function<void(wav_file wav)> delegate_;
};
}
}
#endif
