#ifndef RAPP_CLOUD_FACEDETECTOR
#define RAPP_CLOUD_FACEDETECTOR
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class face_detection
 * \brief Asynchronous Service which will request the cloud to detect faces
 * \version 0.7.0
 * \date September 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class face_detection : public http_request
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
    : http_request("POST /hop/face_detection HTTP/1.1\r\n"),
      delegate_(callback)
    {
        http_request::make_multipart_form();
        std::string fname = rapp::misc::random_boundary()+"."+image.type();

		json json_doc = {{"fast", fast}};
        http_request::add_content("json", json_doc.dump(-1), true);
        // add picture bytes
        http_request::add_content("file", fname, image.bytearray());
        http_request::close();
    }

    /** 
	 * \brief handle the rapp-platform JSON reply
	 */
    void deserialise(std::string json) const
    {   
        if (json.empty()) {
            throw std::runtime_error("empty json reply");
        }
        std::vector<rapp::object::face> faces;
        auto json_f = json::parse(json);
        try {
            for (const nlohman::json::const_iterator & obj : json_f["faces"]) {
                faces.push_back(std::move(rapp::object::face(obj)));
            }
            std::string error = misc::get_json_value<std::string>("error", json_f);
            if (!error.empty()) {
                std::cerr << "error JSON: " << error << std::endl;
            }
        }
        catch {
            std::cerr << e.what() << std::endl;
        }
        delegate_(faces);
    }

private:
     
    /// The callback called upon completion of receiving the detected faces
    std::function<void(std::vector<rapp::object::face>)> delegate_;
};
}
}
#endif
