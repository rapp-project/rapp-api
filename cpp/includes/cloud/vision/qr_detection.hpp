#ifndef RAPP_SERVICE_CLOUD_QRDETECTOR
#define RAPP_SERVICE_CLOUD_QRDETECTOR
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class qr_detection
 * \brief Asynchronous Service which will request the cloud to detect QR codes
 * \version 0.7.0
 * \date 15 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class qr_detection : public caller, public http_request
{
public:
    /**
    * \brief Constructor
    * \param image is a picture object pointer
    * \param callback is the function that will receive a vector of detected qr(s)
    * \param image_format must be defined, e.g.: jpeg, png, gif, etc.
    */
    qr_detection(
                  const rapp::object::picture & image,
                  std::function<void(std::vector<rapp::object::qr_code>)> callback
                )
    : http_header("POST /hop/qr_detection HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()), 
      delegate__(callback)
    {
        std::string fname = rapp::misc::random_boundary() + "." + image.type();

        // Append binary data
        auto imagebytes = image.bytearray();
        http_post::add_content("file", fname, imagebytes);
        http_post::end();
		    
    }
	/**
	 * \brief handle the rapp-platform JSON reply
	 */
    void deserialise(std::string json) const
    {
        std::stringstream ss(json);
        std::vector<rapp::object::qr_code> qrCodes;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);
            for (auto child : tree.get_child("qr_centers")) {
                std::tuple<float,float,std::string> qrcode;
                for (auto iter = child.second.begin(); iter != child.second.end(); ++iter) {
                    if (iter->first == "x") {
                        std::get<0>(qrcode) = iter->second.get_value<float>();
					}
                    else if (iter->first == "y") {
                        std::get<1>(qrcode) = iter->second.get_value<float>();
					}
                    else if (iter->first == "message") {
                        std::get<2>(qrcode) = iter->second.get_value<std::string>();
					}
                }
                qrCodes.push_back(rapp::object::qr_code(std::get<0>(qrcode),
                                                        std::get<1>(qrcode),
                                                        std::get<2>(qrcode)));
            }
            // Check for Errors returned by the platform
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "qr_detection JSON error: " << value << std::endl;
                }
            }
        }
        catch(boost::property_tree::json_parser::json_parser_error & je) {
			std::cerr << "qr_detection::handle_reply Error parsing: " 
                      << je.filename() << " on line: " << je.line() << std::endl;
			std::cerr << je.message() << std::endl;
        }
        delegate__(qrCodes);
    }

    /**
    * \brief method to fill the buffer with http_post and http_header information
    * \param info is the data of the platform    
    */
    boost::asio::streambuf fill_buffer(rapp::cloud::platform info)
    {
           return std::move(http_request::fill_buffer(info));
    }

private:
    /// The callback called upon completion of receiving the detected faces
    std::function<void(std::vector<rapp::object::qr_code>)> delegate__;
};
}
}
#endif
