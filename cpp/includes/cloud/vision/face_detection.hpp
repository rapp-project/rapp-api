#ifndef RAPP_CLOUD_FACEDETECTOR
#define RAPP_CLOUD_FACEDETECTOR
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class face_detection
 * \brief Asynchronous Service which will request the cloud to detect faces
 * \version 0.7.0
 * \date 15 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class face_detection : public caller, public http_request
{
public:

    /**
     * \brief constructor
     * \param image is the input image \see rapp::object::picture
     * \param fast defines if this will be a fast call or not.
     * \param callback is the function that will receive a vector of detected face(s) 
     */
    face_detection(
                    const rapp::object::picture & image,
                    bool fast,
                    std::function<void(std::vector<rapp::object::face>)> callback
                  )
    : http_header("POST /hop/face_detection HTTP/1.1\r\n"),
      http_post(http_header::get_boundary()),
      delegate_(callback)
    {
        std::string fname = rapp::misc::random_boundary()+"."+image.type();

		// setup the POST preamble
        boost::property_tree::ptree tree;
        tree.put("fast", fast);
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
		
		// unquote JSON PDT values
        std::string json = misc::json_unquote_pdt_value<bool>()(ss.str(), fast);
        http_post::add_content("json", json, false);

        // add picture bytes
        http_post::add_content("file", fname, image.bytearray());
        http_post::end();
    }

    /** 
	 * \brief handle the rapp-platform JSON reply
	 */
    void deserialise(std::string json) const
    {   
        std::stringstream ss(json);
        std::vector<rapp::object::face> faces;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

            for (auto child : tree.get_child("faces")) {
                std::pair<float,float> up_left;
                std::pair<float,float> down_right;

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
                faces.push_back(rapp::object::face(std::get<0>(up_left),
                                                   std::get<1>(up_left),
                                                   std::get<0>(down_right),
                                                   std::get<1>(down_right)));
            }

            // Check for Errors returned by the platform
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "face_detection JSON error: " << value << std::endl;
                }
            }
        }
        catch (boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "face_detection::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate_(faces);
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
    std::function<void(std::vector<rapp::object::face>)> delegate_;
};
}
}
#endif
