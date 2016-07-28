#ifndef RAPP_CLOUD_HUMAN_DETECTION
#define RAPP_CLOUD_HUMAN_DETECTION
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class human_detection
 * \brief detect humans in an image
 * \version 0.6.0
 * \date July 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class human_detection : public asio_service_http
{
public:
    /**
    * \brief Constructor
    * \param image is a picture object pointer
    * \param callback is the function that will receive a vector of detected qr(s)
    * \param image_format must be defined, e.g.: jpeg, png, gif, etc.
    */
    human_detection(
                      const rapp::object::picture & image,
                      std::function<void(std::vector<rapp::object::human>)> callback
                    )
    : asio_service_http(), delegate__(callback)
    {
        std::string boundary = rapp::misc::random_boundary();
        std::string fname = rapp::misc::random_boundary() + "." + image.type();

        boost::property_tree::ptree tree;
        tree.put("file", fname);
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

        post_  = "--" + boundary + "\r\n"
               + "Content-Disposition: form-data; name=\"json\"\r\n\r\n"
               + ss.str();

		post_ += "--" + boundary + "\r\n"
              + "Content-Disposition: form-data; name=\"file\"; filename=\"" + fname + "\"\r\n"
              + "Content-Type: image/" + image.type() + "\r\n"
              + "Content-Transfer-Encoding: binary\r\n\r\n";

        // Append binary data
        auto imagebytes = image.bytearray();
        post_.insert(post_.end(), imagebytes.begin(), imagebytes.end());
        post_ += "\r\n";
        post_ += "--"+boundary+"--";

		// set the HTTP header URI pramble and the Content-Type
        head_preamble_.uri = "POST /hop/human_detection HTTP/1.1\r\n";
        head_preamble_.content_type = "Content-Type: multipart/form-data; boundary=" + boundary;

        callback_ = std::bind(&human_detection::handle_reply, this, std::placeholders::_1);   
    }
private:
	/**
	 * \brief handle the rapp-platform JSON reply
	 */
    void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        std::vector<rapp::object::human> humans;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

            // iterate detected humans (json object `human`)
            for (auto child : tree.get_child("humans")) {
                std::pair<float,float> up_left;
                std::pair<float,float> down_right;

                // iterate `human` json members
                for (auto iter = child.second.begin(); iter!= child.second.end(); ++iter) {
                    if (iter->first == "up_left_point") {
                        for (auto it : iter->second) {
                            if (it.first == "x") {
                               std::get<0>(up_left) = it.second.get_value<float>();
							}
                            else if (it.first == "y") {
                               std::get<1>(up_left) = it.second.get_value<float>();
							}
                        }
                    }
                    else if (iter->first == "down_right_point") {
                        for (auto it : iter->second) {
                            if ( it.first == "x" ) {
                                std::get<0>(down_right) = it.second.get_value<float>();
							}
                            else if (it.first == "y") {
                                std::get<1>(down_right) = it.second.get_value<float>();
							}
                        }
                    }
                }
                humans.push_back(rapp::object::human(std::get<0>(up_left),
                                                     std::get<1>(up_left),
                                                     std::get<0>(down_right),
                                                     std::get<1>(down_right)));
            }

            // Check for Errors returned by the platform
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "human_detection JSON error: " << value << std::endl;
                }
            }
        }
        catch(boost::property_tree::json_parser::json_parser_error & je) {
			std::cerr << "human_detection::handle_reply Error parsing: " 
                      << je.filename() << " on line: " << je.line() << std::endl;
			std::cerr << je.message() << std::endl;
        }
        delegate__(humans);
    }

    /// The callback called upon completion of receiving the detected faces
    std::function<void(std::vector<rapp::object::human>)> delegate__;
};
}
}
#endif
