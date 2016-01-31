#ifndef RAPP_CLOUD_SPEECH_TO_TEXT_SPHINX4
#define RAPP_CLOUD_SPEECH_TO_TEXT_SPHINX4
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class speech_detection_sphinx4
 * \brief Asynchronous Service which will request the cloud to process speech-to-text using CMU sphinx4
 * \version 1
 * \date 19-September-2015
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class speech_detection_sphinx4 : public rapp::services::asio_service_http
{
public:
    /**
     * \brief Contrusct a speechToText handler
     * \param audio is the actual binary sound file
     * \param language is the language used for speech to text
     * \param grammar is the Grammars used in Spc2Txt
     * \param user is the user token
     * \param words will be searched for in the audio
     * \param sentences will be under consideration
     * \param callback will be executed once the rapp cloud has responded
     * \note avoid using the class `audio` but insteas use one of it's derivatives.
     * \see objects/audio/audio.hpp for more
     */
    speech_detection_sphinx4(
							  const std::shared_ptr<rapp::object::audio> file,
							  const std::string language,
							  const std::string user,
							  const std::vector<std::string> grammar,
							  const std::vector<std::string> words,
							  const std::vector<std::string> sentences,
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
        // Grammar[]
        post_ += "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"grammar\"\r\n\r\n";
        post_ += "[ ";
        for (const auto gram : grammar ) post_ += "\"" + gram + "\",";
        post_.pop_back();
        post_ += "]\r\n";
        // Words[]
        post_ += "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"words\"\r\n\r\n";
        post_ += "[ ";
        for (const auto word : words) post_ += "\"" + escape_string(word) + "\",";
        post_.pop_back();
        post_ += "]\r\n";
        // Sentences[]
        post_ += "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"sentences\"\r\n\r\n";
        post_ += "[ ";
        for (const auto sent : sentences) post_ += "\"" + escape_string(sent) + "\",";
        post_.pop_back();
        post_ += "]\r\n";
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
        header_ =  "POST /hop/speech_detection_sphinx4 HTTP/1.1\r\n";
        header_ += "Host: " + std::string( rapp::cloud::address ) + "\r\n";
        header_ += "Connection: close\r\n";
        header_ += "Content-Length: " + boost::lexical_cast<std::string>( size ) + "\r\n";
        header_ += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n\r\n";
        // bind the base class callback, to our handle_reply
        callback_ = std::bind(&speech_detection_sphinx4::handle_reply, this, std::placeholders::_1);
    }

private:
    
    void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        std::vector<std::string> words;        
        try
        {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json( ss, tree );
            // JSON response is: { words: [], error: '' } 
            for ( auto child : tree.get_child( "words" ) )
                words.push_back ( child.second.get_value<std::string>() );
            // Check for error response from api.rapp.cloud
            for ( auto child : tree.get_child( "error" ) )
            {
                const std::string value = child.second.get_value<std::string>();
                if ( !value.empty() )
                    std::cerr << "speech_detection_sphinx4 error: " << value << std::endl;
            }
        }
        catch(boost::property_tree::json_parser::json_parser_error & je)
        {
            std::cerr << "speech_detection_sphinx4::handle_reply Error parsing: " << je.filename() 
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
