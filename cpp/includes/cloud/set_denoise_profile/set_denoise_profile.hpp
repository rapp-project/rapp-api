#ifndef RAPP_CLOUD_SET_DENOISE_PROFILE
#define RAPP_CLOUD_SET_DENOISE_PROFILE
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class set_denoise_profile
 * \brief setting the denoising audio profile for speech recognition 
 * \version 2
 * \date 20-September-2015
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
     * \note the file base class should not be used, instead use of if the
     * inheriting classes (\see objects/audio/audio.hpp) which define their `audio_source`.
     */
    set_denoise_profile(
						 const std::shared_ptr<rapp::object::audio> file,
                         const std::string user,
						 const std::string token
					   )
    : asio_service_http(token)
    {
        assert(file);
        // Create a new random boundary
        std::string boundary = random_boundary();
        // Random audio file name (NOTE: Assume WAV File)
        std::string fname = random_boundary();
        // User parameter        
        post_  = "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"user\"\r\n\r\n";
        post_ += user + "\r\n";
        // Create the name for the audio file
        post_ += "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"audio_source\"\r\n\r\n";
        post_ += file->audio_source() + "\r\n";
        // Create the Multi-form POST field for the actualAUDIO/WAV data
        post_ += "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"file_uri\"; filename=\""+fname+".audio\"\r\n";
        post_ += "Content-Transfer-Encoding: binary\r\n\r\n";
        // Append binary data
        auto bytes = file->bytearray();
        post_.insert(post_.end(), bytes.begin(), bytes.end());
        post_ += "\r\n";
        post_ += "--" + boundary + "--";
        // Count Data size
        auto size = post_.size() * sizeof(std::string::value_type);
        // Form the Header
        header_ =  "POST /hop/set_denoise_profile HTTP/1.1\r\n";
        header_ += "Host: " + std::string(rapp::cloud::address) + "\r\n";
        header_ += "Connection: close\r\n";
        header_ += "Content-Length: " + boost::lexical_cast<std::string>(size) + "\r\n";
        header_ += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n\r\n";
        // bind the base class callback, to our handle_reply
        callback_ = std::bind(&set_denoise_profile::handle_reply, this, std::placeholders::_1);
    }

private:

    void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        try
        {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);
            // Check for error response from api.rapp.cloud
            for (auto child : tree.get_child("error"))
            {
                const std::string value = child.second.get_value<std::string>();
                if ( !value.empty() )
                    std::cerr << "set_denoise_profile error: " << value << std::endl;
            }
        }
        catch( boost::property_tree::json_parser::json_parser_error & je )
        {
            std::cerr << "set_denoise_profile::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
    }
};
}
}
#endif
