#ifndef RAPP_SERVICE_CLOUD_QRDETECTOR
#define RAPP_SERVICE_CLOUD_QRDETECTOR
#include "Includes.ihh"
namespace rapp {
namespace cloud {
/**
 * @class qrDetector
 * @brief Asynchronous Service which will request the cloud to detect QR codes
 * @version 2
 * @date 26-April-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class qrDetector : public rapp::services::asio_service_http
{
  public:
      
    /**
    * @brief Constructor
    * @param image is a picture object pointer
    * @param callback is the function that will receive a vector of detected qr(s)
    * @param image_format must be defined, e.g.: jpeg, png, gif, etc.
    */
    qrDetector (
                 const std::shared_ptr<rapp::object::picture> image,
                 const std::string image_format,
                 std::function< void ( std::vector< rapp::object::qrCode> ) > callback
               )
    : rapp::services::asio_service_http (), delegate__ ( callback )
    {
        if ( !image )
            throw std::runtime_error ( "qrDetector::qrDetector param image null ptr" );

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
        header_ =  "POST /hop/qr_detect HTTP/1.1\r\n";
        header_ += "Host: " + std::string( hostname ) + "\r\n";
        header_ += "Connection: close\r\n";
        header_ += "Content-Length: " + boost::lexical_cast<std::string>( size ) + "\r\n";
        header_ += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n\r\n";

        // bind the asio_service_http::callback, to our handle_reply
        callback_ = std::bind ( &qrDetector::handle_reply, this, std::placeholders::_1 );   
    }

  private:

    /// Parse @param buffer received from the socket, into a vector of faces
    void handle_reply ( boost::asio::streambuf & buffer )
    {
        std::string json ( ( std::istreambuf_iterator<char>( &buffer ) ), std::istreambuf_iterator<char>() );
        std::stringstream ss ( json );
        std::vector< rapp::object::qrCode > qrCodes;

        try
        {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json( ss, tree );
            
            for ( auto child : tree.get_child( "qrs" ) )
            {
                float qr_center_x = -1.;
                float qr_center_y = -1.;
                std::string qr_message;
        
                for ( auto iter = child.second.begin(); iter!= child.second.end(); ++iter )
                {
                    std::string member( iter->first );
                    
                    if ( member == "qr_center_x" )
                        qr_center_x = iter->second.get_value<float>();
                        
                    else if ( member == "qr_center_y" )
                        qr_center_y = iter->second.get_value<float>();
                        
                    else if ( member == "qr_message" )
                        qr_message = iter->second.get_value<std::string>();
                }
                
                qrCodes.push_back( rapp::object::qrCode ( qr_center_x, qr_center_y, qr_message ) );
            }
        }
        catch( boost::property_tree::json_parser::json_parser_error & je )
        {
            std::cerr << "qrDetector::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        
        delegate__( qrCodes );
    }
    

    /// The callback called upon completion of receiving the detected faces
    std::function< void ( std::vector< rapp::object::qrCode> ) > delegate__;
};
}
}
#endif