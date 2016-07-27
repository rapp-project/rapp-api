#ifndef RAPP_CLOUD_SET_DENOISE_PROFILE
#define RAPP_CLOUD_SET_DENOISE_PROFILE
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class set_denoise_profile
 * \brief setting the denoising audio profile for speech recognition 
 * \version 0.6.0
 * \date July 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class set_denoise_profile : public asio_service_http
{
public:
    /**
     * \brief set a de-noising profile for a user (for speech recognition) 
	 * \note This class does not return something, it only captures an error
     * \param file is the noise audio file used for de-noising
     * \param user is the user denoise profile
     */
    set_denoise_profile(
						 const std::shared_ptr<rapp::object::audio> file,
                         const std::string user
					   )
    : asio_service_http()
    {
        assert(file);
        std::string boundary = rapp::misc::random_boundary();
        std::string fname = rapp::misc::random_boundary();

        boost::property_tree::ptree tree;
        tree.put("user", user);
        tree.put("audio_source", file->audio_source());
        tree.put("filename", fname + "." + file->extension());
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

        post_  = "--" + boundary + "\r\n"
               + "Content-Disposition: form-data; name=\"json\"\r\n\r\n"
               + ss.str();

        post_ += "--" + boundary + "\r\n"
              + "Content-Disposition: form-data; name=\"file_uri\";\r\n"
              + "Content-Transfer-Encoding: binary\r\n\r\n";

        auto bytes = file->bytearray();
        post_.insert(post_.end(), bytes.begin(), bytes.end());
        post_ += "\r\n--" + boundary + "--";

		// set the HTTP header URI pramble and the Content-Type
        head_preamble_.uri = "POST /hop/set_denoise_profile HTTP/1.1\r\n";
        head_preamble_.content_type = "Content-Type: multipart/form-data; boundary=" + boundary;

        callback_ = std::bind(&set_denoise_profile::handle_reply, this, std::placeholders::_1);
    }

private:
    /**
     * \brief handle platform reply (error notifications only)
     */
    void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

            // Check for error response from api.rapp.cloud
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "set_denoise_profile error: " << value << std::endl;
                }
            }
        }
        catch (boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "set_denoise_profile::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
    }
};
}
}
#endif
