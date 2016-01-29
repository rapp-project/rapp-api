#ifndef RAPP_CLOUD_SPEECH_TO_TEXT_GOOGLE
#define RAPP_CLOUD_SPEECH_TO_TEXT_GOOGLE
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * @class speech_detection_google
 * @brief Asynchronous Service which will request the cloud to process speech-to-text using Google
 * @version 1
 * @date January 2016
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class speech_detection_google : public rapp::services::asio_service_http
{
public:
	/**
	 * @brief construct the handler which will query the Google API
	 * @param 
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
        // Create a new random boundary
        std::string boundary = random_boundary();
        std::string fname =  random_boundary() + file->extension(); 
        // Boundary start and 1st POST
        post_  = "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"language\"\r\n\r\n";
        post_ += language + "\r\n";
        // User
        post_ += "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"user\"\r\n\r\n";
        post_ += user + "\r\n";
        // Audio Source (Audio Type)
        post_ += "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"audio_source\"\r\n\r\n";
        post_ += file->audio_source() + "\r\n";
        // file_uri
        post_ += "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"file_uri\"; filename=\"" + fname + "\"\r\n";
        post_ += "Content-Transfer-Encoding: binary\r\n\r\n";
        // Append binary data
        auto bytes = file->bytearray();
        post_.insert( post_.end(), bytes.begin(), bytes.end() );
        post_ += "\r\n";
        post_ += "--" + boundary + "--";
        // Count Data size
        auto size = post_.size() * sizeof( std::string::value_type );
        // Form the Header
        header_ =  "POST /hop/speech_detection_google HTTP/1.1\r\n";
        header_ += "Host: " + std::string(rapp::cloud::address) + "\r\n";
        header_ += "Connection: close\r\n";
        header_ += "Content-Length: " + boost::lexical_cast<std::string>( size ) + "\r\n";
        header_ += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n\r\n";
        // bind the base class callback, to our handle_reply
        callback_ = std::bind(&speech_detection_google::handle_reply, this, std::placeholders::_1);
    }

private:

    void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        std::vector<std::string> words;        
		std::vector<std::string> alternatives;
        try
        {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);
            // JSON response is: { words: [], alternatives: [], error: '' } 
            for (auto child : tree.get_child("words"))
                words.push_back(child.second.get_value<std::string>());
			for (auto child : tree.get_child("alternatives"))
				alternatives.push_back(child.second.get_value<std::string>());
            // Check for error response from api.rapp.cloud
            for (auto child : tree.get_child("error"))
            {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty())
                    std::cerr << "speech_detection_google error: " << value << std::endl;
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
