#ifndef RAPP_SERVICE_CLOUD_FACEDETECTOR
#define RAPP_SERVICE_CLOUD_FACEDETECTOR
#include "Includes.ihh"

namespace rapp {
namespace cloud {

/**
 * @class faceDetector
 * @brief Asynchronous Service which will request the cloud to detect faces
 * @version 5
 * @date 19-April-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 * 
 * @see http://www.w3.org/TR/html401/interact/forms.html#h-17.13.4
 *      for the multipart/form-data HTTP specifications 
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
        
        // Create the Multi-form POST field
        post_ = boundary + "\r\n";
        post_ += "Content-Disposition: file-data; name=\"img\"; filename=\"face_image\"\r\n";
        post_ += "Content-Type: image/" + image_format + "\r\n";
        //post_ += "Content-Type: application/octet-stream\r\n";
        //post_ += "Content-Transfer-Encoding: binary\r\n";
        
        // Append binary data
        auto imagebytes = image->bytearray();
        post_.insert( post_.end(), imagebytes.begin(), imagebytes.end() );
        post_ += "\r\n";
        
        // Close the boundary for the raw data
        post_ += boundary + "--\r\n";
        
        // Count Data size with the boundaries and endlines
        auto size = post_.size() * sizeof( std::string::value_type );
        
        // Form the Header
        header_ =  "POST /hop/face_detector/ HTTP/1.1\r\n";
        header_ += "Content-Type: multipart/form-data; ";
        header_ += "boundary=" + boundary + "\r\n";
        //header_ += "Content-Length: " + boost::lexical_cast<std::string>( size ) + "\r\n";
        header_ += "Host: " + std::string( hostname ) + "\r\n";
        header_ += "Connection: keep-alive\r\n";
        header_ += "Transfer-Encoding: chunked\r\n\r\n";
    }
      
      
  private:
    
    
    /// Parse @param buffer received from the socket, into a vector of faces
    void handle ( boost::asio::streambuf & buffer )
    {   
        std::string json ( ( std::istreambuf_iterator<char>( &buffer ) ), std::istreambuf_iterator<char>() );
        std::stringstream ss ( json );
        std::vector< rapp::object::face > faces;
        
        // Parse JSON Tree
        boost::property_tree::ptree tree;
        boost::property_tree::read_json( ss, tree );
        
        // TODO: There should be some kind of error checking here when trying to parse the JSON reply
        
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
        
        delegate_( faces );
    }    
    
    
    /// Create a random boundary for the multipart/form
    std::string randomBoundary ( ) const
    {
        std::string chars( "abcdefghijklmnopqrstuvwxyz"
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                           "1234567890" );
        
        // Non-deterministic PRNG from boost
        boost::random::random_device rng;
        
        std::string uid;
        
        // Randomly chose 16 characters
        boost::random::uniform_int_distribution<> index_dist(0, chars.size() - 1);
        for ( int i = 0; i < 16; ++i )
            uid.push_back( chars[index_dist(rng)] );
        
        // Multipart/form length = 16 hyphens + 16 random chars, RFC 2016 states max length is 70.
        return std::string( 16, '-') + uid;
    }
    
    
      
    /// The callback called upon completion of receiving the detected faces
    std::function< void ( std::vector< rapp::object::face > ) > delegate_;
};

}
}

#endif
