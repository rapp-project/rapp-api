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
class speech_detection_sphinx4 : public asio_service_http
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
							  std::function<void(std::vector<std::string> words)> callback,
							  std::string token
						    )
	: asio_service_http(token), delegate_(callback)
    {
        assert(file);
        // Create a new random boundary
        std::string boundary = random_boundary();
        std::string fname =  random_boundary() + file->extension(); 
        boost::property_tree::ptree tree;
        tree.put("language", language);
        tree.put("user", user);
        tree.put("audio_source", file->audio_source());
        boost::property_tree::ptree grammar_array;
        for (const auto gram : grammar) {
            boost::property_tree::ptree child;
            child.put("", gram);
            grammar_array.push_back(std::make_pair("", child));
        }
        tree.add_child("grammar", grammar_array);
        boost::property_tree::ptree words_array;
        for (const auto word : words) {
            boost::property_tree::ptree child;
            child.put("", word);
            words_array.push_back(std::make_pair("", child));
        }
        tree.add_child("words", words_array);
        boost::property_tree::ptree sentence_array;
        for (const auto sents : sentences) {
            boost::property_tree::ptree child;
            child.put("", sents);
            sentence_array.push_back(std::make_pair("", child));
        }
        tree.add_child("sentences", sentence_array);
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        post_ += "--" + boundary + "\r\n"
            + "Content-Disposition: form-data; name=\"file_uri\"; filename=\""+fname+"\"\r\n"
            + "Content-Transfer-Encoding: binary\r\n\r\n";
        auto bytes = file->bytearray();
        post_.insert( post_.end(), bytes.begin(), bytes.end() );
        post_ += "\r\n--" + boundary + "--";
        header_ =  "POST /hop/speech_detection_sphinx4 HTTP/1.1\r\n";
        header_ += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n\r\n";
        callback_ = std::bind(&speech_detection_sphinx4::handle_reply, this, std::placeholders::_1);
    }

private:
    /**
	 * \brief handle the rappl-platform JSON reply
	 */ 
    void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        std::vector<std::string> words;        
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);
            // JSON response is: { words: [], error: '' } 
            for (auto child : tree.get_child("words")) {
                words.push_back(child.second.get_value<std::string>());
			}
            // Check for error response from api.rapp.cloud
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "speech_detection_sphinx4 error: " << value << std::endl;
				}
            }
        }
        catch(boost::property_tree::json_parser::json_parser_error & je) {
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
