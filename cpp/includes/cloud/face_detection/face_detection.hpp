#ifndef RAPP_CLOUD_FACEDETECTOR
#define RAPP_CLOUD_FACEDETECTOR
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * @class face_detection
 * @brief Asynchronous Service which will request the cloud to detect faces
 * @version 6
 * @date 26-April-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class face_detection : public rapp::services::asio_service_http
{
public:
          
    /**
     * @brief Constructor
     * @param image is the input image @see rapp::object::picture
     * @param image_format is the image format
     * @param fast defines if this will be a fast call or not.
     * @param callback is the function that will receive a vector of the detected face(s) coordinates
     */
    face_detection(
                    const std::shared_ptr<rapp::object::picture> image,
                    const std::string image_format,
                    bool fast,
                    std::function<void(std::vector<rapp::object::face>)> callback
                  )
    : rapp::services::asio_service_http (), delegate_(callback)
    {
        assert(image);
        // Create a new random boundary
        std::string boundary = random_boundary();
        // Create a random file name + extension
        std::string fname = random_boundary() + "." + image_format;
		// set the `fast` param
        post_  = "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"fast\"\r\n\r\n";
        post_ += (fast ? "1" : "0") + "\r\n";
        // Create the Multi-form POST field
        post_ += "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"file_uri\"; filename=\"" + fname  + "\"\r\n";
        post_ += "Content-Type: image/" + image_format + "\r\n";
        post_ += "Content-Transfer-Encoding: binary\r\n\r\n";
        // Append binary data
        auto imagebytes = image->bytearray();
        post_.insert( post_.end(), imagebytes.begin(), imagebytes.end() );
        post_ += "\r\n";
        post_ += "--" + boundary + "--";
        // Count Data size
        auto size = post_.size() * sizeof( std::string::value_type );
        // Form the Header
        header_ =  "POST /hop/face_detection HTTP/1.1\r\n";
        header_ += "Host: " + std::string( rapp::cloud::address ) + "\r\n";
        header_ += "Connection: close\r\n";
        header_ += "Content-Length: " + boost::lexical_cast<std::string>( size ) + "\r\n";
        header_ += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n\r\n";
        // bind the base class callback, to our handle_reply
        callback_ = std::bind(&face_detection::handle_reply, this, std::placeholders::_1);
    }

private:
    
    void handle_reply(std::string json)
    {   
        std::stringstream ss(json);
        std::vector<rapp::object::face> faces;
        try
        {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);
            for (auto child : tree.get_child("faces"))
            {
                std::tuple<float,float,float> up_left;
                std::tuple<float,float,float> down_right;
                for (auto iter = child.second.begin(); iter!= child.second.end(); ++iter)
                {
                    if (iter->first == "up_left_point")
                    {
                        for (auto it : iter->second)
                        {
                           if (it.first == "x")
                               std::get<0>(up_left) = it.second.get_value<float>();
                           else if (it.first == "y")
                               std::get<1>(up_left) = it.second.get_value<float>();
                        }
                    }
                    else if ( iter->first == "down_right_point" )
                    {
                        for ( auto it : iter->second )
                        {
                            if ( it.first == "x" )
                                std::get<0>( down_right) = it.second.get_value<float>();
                            else if ( it.first == "y" )
                                std::get<1>( down_right ) = it.second.get_value<float>();
                        }
                    }
                }
                faces.push_back( rapp::object::face( std::get<0>( up_left ),
                                                     std::get<1>( up_left ),
                                                     std::get<2>( up_left ),
                                                     std::get<0>( down_right ),
                                                     std::get<1>( down_right ),
                                                     std::get<2>( down_right ) ) );
            }
        }
        catch ( boost::property_tree::json_parser::json_parser_error & je )
        {
            std::cerr << "face_detection::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate_(faces);
    }    
     
    /// The callback called upon completion of receiving the detected faces
    std::function< void ( std::vector< rapp::object::face > ) > delegate_;
};
}
}
#endif
