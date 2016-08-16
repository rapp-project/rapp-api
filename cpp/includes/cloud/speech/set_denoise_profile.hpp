#ifndef RAPP_CLOUD_SET_DENOISE_PROFILE
#define RAPP_CLOUD_SET_DENOISE_PROFILE
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class set_denoise_profile
 * \brief setting the denoising audio profile for speech recognition 
 * \version 0.7.0
 * \date 15 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class set_denoise_profile : public caller, public http_request
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
    : http_header("POST /hop/set_denoise_profile HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()),
    {
        assert(file);
        boost::property_tree::ptree tree;
        tree.put("user", user);
        tree.put("audio_source", file->audio_source());
        tree.put("filename", fname + "." + file->extension());

        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

        std::string json = ss.str();
        http_post::add_content("json", json, false); 
        
        auto bytes = file->bytearray();
        http_post::add_content("file", fname, bytes);
        http_post::end();
   }

    /**
     * \brief handle platform reply (error notifications only)
     */
    void deserialise(std::string json) const
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

    /**
    * \brief method to fill the buffer with http_post and http_header information
    * \param info is the data of the platform    
    */
    boost::asio::streambuf fill_buffer(rapp::cloud::platform info)
    {
           return std::move(http_request::fill_buffer(info));
    }

};
}
}
#endif
