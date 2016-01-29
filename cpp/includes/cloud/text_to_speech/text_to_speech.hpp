#ifndef RAPP_CLOUD_TEXT2SPEECH
#define RAPP_CLOUD_TEXT2SPEECH
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * @class text_to_speech
 * @brief Asynchronous Service will obtain speech audio from text
 * @version 6
 * @date January 2016
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class text_to_speech : public rapp::services::asio_service_http
{
public:
	/**
	 * @brief construct handler which will request speech audio from text
	 * @param text is the text to be converted to audio
	 * @param language is language
	 * @callback will receive the speech audio object
	 */
	text_to_speech(
					 const std::string text,
					 const std::string language,
					 std::function<void(rapp::object::audio)> callback
				  )
	: rapp::services::asio_service_http (), delegate_(callback)
	{
		std::string boundary = random_boundary();
        post_  = "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"language\"\r\n\r\n";
        post_ += language + "\r\n";
        post_ += "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"text\"\r\n\r\n";
        post_ += escape_string(text) + "\r\n";
        header_ = "POST /hop/text_to_speech HTTP/1.1\r\n";
        header_ += "Host: " + std::string(rapp::cloud::address) + "\r\n";
        header_ += "Content-Type: application/x-www-form-urlencoded\r\n";
        header_ += "Content-Length: " + boost::lexical_cast<std::string>(post_.length()) + "\r\n";
        header_ += "Connection: close\r\n\r\n";
        callback_ = std::bind(&text_to_speech::handle_reply, this, std::placeholders::_1);
	}

private:
    
    void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        std::vector<std::string> words;        
        try
        {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);
			// TODO: parse reply, obtain raw bytes, insert into audio obj
	    }
        catch(boost::property_tree::json_parser::json_parser_error & je)
        {
            std::cerr << "text_to_speech::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate_(words);
    }

    /// The callback called upon completion of receiving the detected words
    std::function<void(rapp:object::audio)> delegate_;
};
}
}
#endif
