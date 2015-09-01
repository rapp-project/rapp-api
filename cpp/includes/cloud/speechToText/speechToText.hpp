#ifndef RAPP_CLOUD_SPEECH_TO_TEXT
#define RAPP_CLOUD_SPEECH_TO_TEXT
#include "Includes.ihh"
namespace rapp {
namespace cloud {
/**
 * @class speechToText
 * @brief Asynchronous Service which will request the cloud to process speech-to-text
 * @version 0
 * @date 1-February-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class speechToText : public rapp::services::asio_service_http
{
public:

    /**
     * @brief Contrusct a speechToText handler
     * @param audio is the actual binary sound file
     * @param language is the language used for speech to text
     * @param grammar is the Grammars used in Spc2Txt
     * @param user is the user token
     * @param words will be searched for in the audio
     * @param sentences will be under consideration
     * @param callback will be executed once the rapp cloud has responded
     */
    speechToText (
                    const std::shared_ptr<audio> file,
                    const std::string language,
                    const std::string grammar,
                    const std::string user,
                    const std::vector<std::string> words,
                    const std::vector<std::string> sentences,
                    std::function< void( std::vector<std::string> words ) > callback
                 )
    : rapp::services::asio_service_http (), delegate_ ( callback )
    {
        assert( file );

        // Create a new random boundary
        std::string boundary = randomBoundary();
        
        // --boundary
        // Content-Disposition: form-data; name="language"
        //
        // EN
        // --boundary
        // Content-Disposition: form-data; name="grammar"
        //
        // Blah
        // --boundary
        // Content-Disposition: form-data; name="user"
        //
        // alex
        // --boundary
        // Content-Disposition: form-data; name="words"
        // Content-Type: text/plain
        //
        // blah; blah; blah; blah;
        // --boundary
        // Content-Disposition: form-data; name="sentences"
        // Content-Type: text/plain
        //
        // one sentence;
        // second sentence;
        // third sentence;
        // --boundary

        // Create the name for the audio file - TODORandomize file name instead of 'audio.wav'
        post_ = "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"filename\"\r\n\r\n";
        post_ += "audio.wav\r\n";
        
        // Create the Multi-form POST field
        //
        // NOTE - Normally, Content-Type is 
        //      (mp3) audio/mpeg; audio/x-mpeg; audio/x-mpeg-3; audio/mpeg3
        //      (wav) audio/x-wav; audio/wav
        //      (wav) audio/vnd.wave; codec=123 - when we know the codec
        //
        // However, due to streaming tendencies, we can also try
        //      Content-Disposition: attachment;
        //      Content-Type "application/force-download
        
        post_ += "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"file_uri\"; filename=\"audio.wav\"\r\n";
        post_ += "Content-Type: audio/wav\r\n";
        post_ += "Content-Transfer-Encoding: binary\r\n\r\n";
        
        // Append binary data
        auto imagebytes = audio->bytearray();
        post_.insert( post_.end(), imagebytes.begin(), imagebytes.end() );
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
        callback_ = std::bind ( &speechToText::handle_reply, this, std::placeholders::_1 );
    }

private:
    
    void handle_reply ( std::string json )
    {
        std::stringstream ss ( json );
        std::vector< std::string > words;        
        try
        {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json( ss, tree );
       
            // JSON response is: { words: [], error: '' } 
            for ( auto child : tree.get_child( "words" ) )
                for ( auto iter = child.second.begin(); iter!= child.second.end(); ++iter )
                    words.push_back ( iter->second.get_value<std::string>() );

            // Check for error response from api.rapp.cloud
            for ( auto child : tree.get_child( "error" ) )
            {
                const std::string value = child.second.get_value<std::string>();
                if ( !value.empty() )
                    std::cerr << "speechToText error: " << value << std::endl;
            }
        }
        catch( boost::property_tree::json_parser::json_parser_error & je )
        {
            std::cerr << "speechToText::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        
        delegate_( words );
    }

    /// The callback called upon completion of receiving the detected words
    std::function< void( std::vector<std::string> words ) > callback__;
};
}
}
#endif
