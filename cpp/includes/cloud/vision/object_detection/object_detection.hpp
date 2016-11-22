#ifndef RAPP_CLOUD_OBJECT_DETECTION
#define RAPP_CLOUD_OBJECT_DETECTION
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class object_detection_find_objects
 * \brief recognize object from an image
 * \version 0.6.1
 * \date November 2016
 * \author Maciej Stefańczyk <M.Stefanczyk@elka.pw.edu.pl>
 */
class object_detection_find_objects : public asio_http
{
public:
    /**
    * \brief Constructor
    * \param image is a picture object pointer
    * \param limit is a limit of the objects to return
    * \param callback is the function that will receive a string
    */
    object_detection_find_objects(
                      const rapp::object::picture::Ptr & image,
                      int limit,
                      std::function<void(std::vector<std::string>, std::vector<rapp::object::point>, std::vector<float>, int)> callback
                    )
    : asio_http(), delegate__(callback)
    {
        std::string boundary = rapp::misc::random_boundary();
        std::string fname = rapp::misc::random_boundary() + "." + image->type();

        boost::property_tree::ptree tree;
        tree.put("file", fname);
        tree.put("limit", limit);
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

        post_  = "--" + boundary + "\r\n"
               + "Content-Disposition: form-data; name=\"json\"\r\n\r\n"
               + ss.str();
        
        post_ += "--" + boundary + "\r\n"
              + "Content-Disposition: form-data; name=\"file\"; filename=\"" + fname + "\"\r\n"
              + "Content-Type: image/" + image->type() + "\r\n"
              + "Content-Transfer-Encoding: binary\r\n\r\n";

        // Append binary data
        auto imagebytes = image->bytearray();
        post_.insert(post_.end(), imagebytes.begin(), imagebytes.end());
        post_ += "\r\n";
        post_ += "--"+boundary+"--";

        // set the HTTP header URI pramble and the Content-Type
        head_preamble_.uri = "POST /hop/object_detection_find_objects HTTP/1.1\r\n";
        head_preamble_.content_type = "Content-Type: multipart/form-data; boundary=" + boundary;

        callback_ = std::bind(&object_detection_find_objects::handle_reply, this, std::placeholders::_1);   
    }
private:
    /**
     * \brief handle the rapp-platform JSON reply
     */
    void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        std::vector<std::string> names;
        std::vector<rapp::object::point> centers;
        std::vector<float> scores;
        int result;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

            // read found names
            for (auto child : tree.get_child("found_names")) {
                names.push_back(child.second.get_value<std::string>());
            }

            // read found centers
            for (auto child : tree.get_child("found_centers")) {
                centers.push_back(rapp::object::point(child.second));
            }



            // Check for Errors returned by the platform
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "object_detection JSON error: " << value << std::endl;
                }
            }
        }
        catch(boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "object_detection::handle_reply Error parsing: " 
                      << je.filename() << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate__(names, centers, scores, result);
    }

    /// The callback called upon completion of receiving the detected faces
    std::function<void(std::vector<std::string>, std::vector<rapp::object::point>, std::vector<float>, int)> delegate__;
};
}
}
#endif
