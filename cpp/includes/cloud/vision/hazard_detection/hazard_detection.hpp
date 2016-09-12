#ifndef RAPP_CLOUD_HAZARD_DETECTION
#define RAPP_CLOUD_HAZARD_DETECTION
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class hazard_detection_door_check
 * \brief detect open doors
 * \version 0.6.0
 * \date April 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class hazard_detection_door_check : public asio_http
{
public:
    /**
    * \brief Constructor
    * \param image is a picture object pointer
    * \param callback is the function that will receive a vector of detected qr(s)
    * \param image_format must be defined, e.g.: jpeg, png, gif, etc.
    */
    hazard_detection_door_check(
                                  const rapp::object::picture & image,
                                  std::function<void(double door_angle)> callback
                                )
    : asio_http(), delegate__(callback)
    {
        std::string boundary = rapp::misc::random_boundary();
        std::string fname = rapp::misc::random_boundary() + "." + image.type();

        boost::property_tree::ptree tree;
        //tree.put("file", fname);
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

        post_  = "--" + boundary + "\r\n"
               + "Content-Disposition: form-data; name=\"json\"\r\n\r\n"
               + ss.str() + "\r\n";

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
        head_preamble_.uri = "POST /hop/hazard_detection_door_check HTTP/1.1\r\n";
        head_preamble_.content_type = "Content-Type: multipart/form-data; boundary=" + boundary;

        callback_ = std::bind(&hazard_detection_door_check::handle_reply, this, std::placeholders::_1);   
    }
private:
	/**
	 * \brief handle the rapp-platform JSON reply
	 */
    void handle_reply(std::string json)
    {
        std::stringstream ss(json);

	std::cout<<"json: "<<json<<std::endl;

        double door_angle;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

            door_angle = tree.get<double>("door_angle", -1);

            // get door angle
/*            for (auto child : tree.get_child("door_angle")) {
                door_angle = child.second.get_value<int>();
		std::cout << "Got child!\n";
            }*/

            // Check for Errors returned by the platform
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "hazard_detection_door_check JSON error: " << value << std::endl;
                }
            }
        }
        catch(boost::property_tree::json_parser::json_parser_error & je) {
			std::cerr << "hazard_detection_door_check::handle_reply Error parsing: " 
                      << je.filename() << " on line: " << je.line() << std::endl;
			std::cerr << je.message() << std::endl;
        }
        delegate__(door_angle);
    }

    /// The callback called upon completion of receiving the detected faces
    std::function<void(double)> delegate__;
};

/**
 * \class hazard_detection_light_check
 * \brief detect light levels
 * \version 0.6.0
 * \date April 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class hazard_detection_light_check : public asio_http
{
public:
    /**
    * \brief Constructor
    * \param image is a picture object pointer
    * \param callback is the function that will receive a vector of detected qr(s)
    * \param image_format must be defined, e.g.: jpeg, png, gif, etc.
    */
    hazard_detection_light_check(
                                  const rapp::object::picture & image,
                                  std::function<void(double light_level)> callback
                                )
    : asio_http(), delegate__(callback)
    {
        std::string boundary = rapp::misc::random_boundary();
        std::string fname = rapp::misc::random_boundary() + "." + image.type();

        boost::property_tree::ptree tree;
        //tree.put("file", fname);
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
        head_preamble_.uri = "POST /hop/hazard_detection_light_check HTTP/1.1\r\n";
        head_preamble_.content_type = "Content-Type: multipart/form-data; boundary=" + boundary;

        callback_ = std::bind(&hazard_detection_light_check::handle_reply, this, std::placeholders::_1);   
    }

private:
	/**
	 * \brief handle the rapp-platform JSON reply
	 */
    void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        double light_level;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

            // get door angle
            for (auto child : tree.get_child("light_level")) {
                light_level = child.second.get_value<double>();
            }

            // Check for Errors returned by the platform
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "hazard_detection_light_check JSON error: " << value << std::endl;
                }
            }
        }
        catch(boost::property_tree::json_parser::json_parser_error & je) {
			std::cerr << "hazard_detection_light_check::handle_reply Error parsing: " 
                      << je.filename() << " on line: " << je.line() << std::endl;
			std::cerr << je.message() << std::endl;
        }
        delegate__(light_level);
    }

    /// The callback called upon completion of receiving the detected faces
    std::function<void(double)> delegate__;
};
}
}
#endif
