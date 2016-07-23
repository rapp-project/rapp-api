#ifndef RAPP_CLOUD_OBJECT_RECOGNITION
#define RAPP_CLOUD_OBJECT_RECOGNITION
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class object_recognition
 * \brief recognize object from an image
 * \version 0.6.1
 * \date April 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class object_recognition : public asio_service_http
{
public:
    /**
    * \brief Constructor
    * \param image is a picture object pointer
    * \param callback is the function that will receive a string
    */
    object_recognition(
                      const std::shared_ptr<rapp::object::picture> image,
                      std::function<void(std::string)> callback
                    )
    : asio_service_http(), delegate__(callback)
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
        header_ =  "POST /hop/object_recognition_caffe HTTP/1.1\r\n";
        header_ += "Content-Type: multipart/form-data; boundary="+boundary+"\r\n\r\n";
        callback_ = std::bind(&object_recognition::handle_reply, this, std::placeholders::_1);   
    }
private:
	/**
	 * \brief handle the rapp-platform JSON reply
	 */
    void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        std::string object_class;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);
            for (auto child : tree.get_child("object_class")) {
                object_class = child.second.get_value<std::string>();
            }
            // Check for Errors returned by the platform
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "object_recognition JSON error: " << value << std::endl;
                }
            }
        }
        catch(boost::property_tree::json_parser::json_parser_error & je) {
			std::cerr << "object_recognition::handle_reply Error parsing: " 
                      << je.filename() << " on line: " << je.line() << std::endl;
			std::cerr << je.message() << std::endl;
        }
        delegate__(object_class);
    }

    /// The callback called upon completion of receiving the detected faces
    std::function<void(std::string)> delegate__;
};
}
}
#endif
