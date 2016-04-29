#ifndef RAPP_CLOUD_SPEECH_TO_TEXT_GOOGLE
#define RAPP_CLOUD_SPEECH_TO_TEXT_GOOGLE
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class speech_detection_google
 * \brief Asynchronous Service which will request the cloud to process speech-to-text using Google
 * \version 1
 * \date January 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class speech_detection_google : public rapp::services::asio_service_http
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
							  const std::shared_ptr<rapp::object::audio> file,
							  const std::string language,
							  const std::string user,
							  std::function<void(std::vector<std::string> words)> callback
						   )
	: rapp::services::asio_service_http (), delegate_(callback)
    {
        assert(file);
        std::string boundary = random_boundary();
        std::string fname =  random_boundary() + file->extension(); 
        boost::property_tree::ptree tree;
        tree.put("language", language);
        tree.put("user", user);
        tree.put("audio_source", file->audio_source());
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        post_ += "--" + boundary + "\r\n"
              + "Content-Disposition: form-data; name=\"file_uri\"; filename=\""+fname+"\"\r\n"
              + "Content-Transfer-Encoding: binary\r\n\r\n";
        auto bytes = file->bytearray();
        post_.insert( post_.end(), bytes.begin(), bytes.end() );
        post_ += "\r\n" + "--" + boundary + "--";
        header_ =  "POST /hop/speech_detection_google HTTP/1.1\r\n";
        header_ += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n\r\n";
        callback_ = std::bind(&speech_detection_google::handle_reply, this, std::placeholders::_1);
    }

private:
	/**
	 * \brief handle rapp-platform JSON reply
	 */
    void handle_reply(std::string json)
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
            // Check for error response from api.rapp.cloud
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "speech_detection_google error: " << value << std::endl;
				}
            }
        }
        catch(boost::property_tree::json_parser::json_parser_error & je)
        {
            std::cerr << "speech_detection_google::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate_(words);
    }

    /// The callback called upon completion of receiving the detected words
    std::function<void(std::vector<std::string> words)> delegate_;
};
}
}
#endif

speech_detection_sphinx4 ( { file_uri: '', audio_source: '',  user: '', language: ''} )
