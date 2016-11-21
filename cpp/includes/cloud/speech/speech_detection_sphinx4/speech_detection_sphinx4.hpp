#ifndef RAPP_CLOUD_SPEECH_TO_TEXT_SPHINX4
#define RAPP_CLOUD_SPEECH_TO_TEXT_SPHINX4
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class speech_detection_sphinx4
 * \brief speech-to-text recognition using CMU sphinx4
 * \version 0.6.0
 * \date April 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class speech_detection_sphinx4 : public asio_http
{
public:
    /**
     * \brief construct a speechToText handler
     * \param audio is the actual binary sound file
     * \param language is the language used for speech to text
     * \param grammar is the Grammars used in Spc2Txt
     * \param user is the user token
     * \param words will be searched for in the audio
     * \param sentences will be under consideration
     * \param callback will be executed once the rapp cloud has responded
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
	: asio_http(), delegate_(callback)
    {
        assert(file);
        std::string boundary = rapp::misc::random_boundary();
        std::string fname =  rapp::misc::random_boundary() + file->extension(); 

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

		post_  = "--" + boundary + "\r\n"
			   + "Content-Disposition: form-data; name=\"json\"\r\n\r\n"
			   + ss.str();

		post_ += "--" + boundary + "\r\n"
              + "Content-Disposition: form-data; name=\"file\"; filename=\"" + fname + "\"\r\n"
              + "Content-Transfer-Encoding: binary\r\n\r\n";

        auto bytes = file->bytearray();
        post_.insert(post_.end(), bytes.begin(), bytes.end());
        post_ += "\r\n--" + boundary + "--";

		// set the HTTP header URI pramble and the Content-Type
        head_preamble_.uri = "POST /hop/speech_detection_sphinx4 HTTP/1.1\r\n";
        head_preamble_.content_type = "Content-Type: multipart/form-data; boundary=" + boundary;

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
