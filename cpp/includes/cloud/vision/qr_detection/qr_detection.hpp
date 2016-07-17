#ifndef RAPP_SERVICE_CLOUD_QRDETECTOR
#define RAPP_SERVICE_CLOUD_QRDETECTOR
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class qr_detection
 * \brief Asynchronous Service which will request the cloud to detect QR codes
 * \version 0.6.0
 * \date April 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class qr_detection : public asio_service_http
{
public:
    /**
    * \brief Constructor
    * \param image is a picture object pointer
    * \param callback is the function that will receive a vector of detected qr(s)
    * \param image_format must be defined, e.g.: jpeg, png, gif, etc.
    */
    qr_detection(
                  const std::shared_ptr<rapp::object::picture> image,
                  std::function<void(std::vector<rapp::object::qr_code>)> callback,
                  rapp::cloud::platform_info info
                )
    : asio_service_http(info), delegate__(callback)
    {
        assert(image);
        std::string boundary = random_boundary();
        std::string fname = random_boundary()+"."+image->type();
        boost::property_tree::ptree tree;
        tree.put("file", fname);
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        post_  = "--" + boundary + "\r\n"
               + "Content-Disposition: form-data; name=\"json\"\r\n\r\n"
               + ss.str() + "\r\n";
        post_ += "--"+boundary+"\r\n"
              + "Content-Disposition: form-data; name=\"file_uri\"; filename=\""+fname+"\"\r\n"
              + "Content-Type: image/"+image->type()+"\r\n"
              + "Content-Transfer-Encoding: binary\r\n\r\n";
        // Append binary data
        auto imagebytes = image->bytearray();
        post_.insert(post_.end(), imagebytes.begin(), imagebytes.end());
        post_ += "\r\n";
        post_ += "--"+boundary+"--";
        header_ =  "POST /hop/qr_detection HTTP/1.1\r\n";
        header_ += "Content-Type: multipart/form-data; boundary="+boundary+"\r\n\r\n";
        callback_ = std::bind(&qr_detection::handle_reply, this, std::placeholders::_1);   
    }
private:
	/**
	 * \brief handle the rapp-platform JSON reply
	 */
    void handle_reply(std::string json)
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

    /// The callback called upon completion of receiving the detected faces
    std::function<void(std::vector<rapp::object::qr_code>)> delegate__;
};
}
}
#endif
