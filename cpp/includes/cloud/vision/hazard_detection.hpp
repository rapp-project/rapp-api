#ifndef RAPP_CLOUD_HAZARD_DETECTION
#define RAPP_CLOUD_HAZARD_DETECTION
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class hazard_detection_door_check
 * \brief detect open doors
 * \version 0.7.0
 * \date 15 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class hazard_detection_door_check : public caller, public http_request
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
    : http_header("POST /hop/hazard_detection_door_check HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()), 
      delegate__(callback)
    {
        std::string fname = rapp::misc::random_boundary() + "." + image.type();

        boost::property_tree::ptree tree;
        tree.put("file", fname);
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

        std::string json = ss.str();
        http_post::add_content("json", json, false);

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
        double door_angle;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

            // get door angle
            for (auto child : tree.get_child("door_angle")) {
                door_angle = child.second.get_value<double>();
            }

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
    std::function<void(double)> delegate__;
};

/**
 * \class hazard_detection_light_check
 * \brief detect light levels
 * \version 0.7.0
 * \date 15 August2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class hazard_detection_light_check : public caller, public http_request
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
    : http_header("POST /hop/hazard_detection_light_check HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()), 
      delegate__(callback)
    {
        std::string fname = rapp::misc::random_boundary() + "." + image.type();

        boost::property_tree::ptree tree;
        tree.put("file", fname);
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

        std::string json = ss.str();
        http_post::add_content("json", json, false);

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
    std::function<void(double)> delegate__;
};
}
}
#endif
