#ifndef RAPP_SERVICE_CLOUD_FACEDETECTOR
#define RAPP_SERVICE_CLOUD_FACEDETECTOR
#include "Includes.ihh"

namespace rapp {
namespace cloud {

/**
 * @class faceDetector
 * @brief Asynchronous Service which will request the cloud to detect faces
 * @version 6
 * @date 26-April-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 * 
 * @see http://www.w3.org/TR/html401/interact/forms.html#h-17.13.4
 *      for the multipart/form-data HTTP specifications - the RFC 1867 standard 
 */
class faceDetector : public rapp::services::asio_service_http
{
  public:
      
    /**
     * @brief Constructor
     * @param image is the input image @see rapp::object::picture
     * @param image_format is the image format
     * @param callback is the function that will receive a vector of the detected face(s) coordinates
     */
    faceDetector (
                    const std::shared_ptr<rapp::object::picture> image,
                    const std::string image_format,
                    std::function< void ( std::vector< rapp::object::face > ) > callback
                 )
    : rapp::services::asio_service_http (), delegate_ ( callback )
    {
        if ( !image )
            throw std::runtime_error ( "faceDetector::faceDetector param image null ptr" );
        
        // Create a new random boundary
        std::string boundary = randomBoundary();
        
        // Create the name for the image (just a textfield request)
        post_ = "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"fileName\"\r\n\r\n";
        post_ += "image." + image_format + "\r\n";
        
        // Create the Multi-form POST field
        post_ += "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"fileContents\"; filename=\"image." + image_format + "\"\r\n";
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
        header_ =  "POST /hop/face_detect HTTP/1.1\r\n";
        header_ += "Host: " + std::string( hostname ) + "\r\n";
        header_ += "Connection: close\r\n";
        header_ += "Content-Length: " + boost::lexical_cast<std::string>( size ) + "\r\n";
        header_ += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n\r\n";
        
        // bind the base class callback, to our handle_reply
        callback_ = std::bind ( &faceDetector::handle_reply, this, std::placeholders::_1 );
    }
      
  private:
    
    /// Parse @param buffer received from the socket, into a vector of faces
    void handle_reply ( boost::asio::streambuf & buffer )
    {   
        std::string json ( ( std::istreambuf_iterator<char>( &buffer ) ), std::istreambuf_iterator<char>() );
        std::stringstream ss ( json );
        std::vector< rapp::object::face > faces;
        
        try
        {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json( ss, tree );
        
            // Find the actual json objects
            for ( auto child : tree.get_child( "faces" ) )
            {
                float top_left_x = -1.;
                float top_left_y = -1.;
                float bottom_right_x = -1.;
                float bottom_right_y = -1.;
                
                for ( auto iter = child.second.begin(); iter!= child.second.end(); ++iter )
                {
                    std::string member( iter->first );
                    
                    if ( member == "top_left_x" )
                        top_left_x = iter->second.get_value<float>();
                        
                    else if ( member == "top_left_y" )
                        top_left_y = iter->second.get_value<float>();
                        
                    else if ( member == "bottom_right_x" )
                        bottom_right_x = iter->second.get_value<float>();
                        
                    else if ( member == "bottom_right_y" )
                        bottom_right_y = iter->second.get_value<float>();
                }
                
                faces.push_back( rapp::object::face( top_left_x, top_left_y, bottom_right_x, bottom_right_y ) );
            }
        }
        catch( boost::property_tree::json_parser::json_parser_error & je )
        {
            std::cerr << "faceDetector::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        
        delegate_( faces );
    }    
    
     
    /// The callback called upon completion of receiving the detected faces
    std::function< void ( std::vector< rapp::object::face > ) > delegate_;
};

}
}

#endif
