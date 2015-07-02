#ifndef RAPP_SERVICE_CLOUD_OBJECTDETECTOR
#define RAPP_SERVICE_CLOUD_OBJECTDETECTOR
#include "Includes.ihh"

namespace rapp {
namespace cloud {

/**
 * @class objectDetector
 * @brief Asynchronous Service which will request the cloud to detect objects
 * @version 6
 * @date 02-July-2015
 * @author Maciej Stefańczyk <stefanczyk.maciek@gmail.com>
 * 
 * @see http://www.w3.org/TR/html401/interact/forms.html#h-17.13.4
 *      for the multipart/form-data HTTP specifications - the RFC 1867 standard 
 */
class objectDetector : public rapp::services::asio_service_http
{
  public:
      
    /**
     * @brief Constructor
     * @param image is the input image @see rapp::object::picture
     * @param image_format is the image format
     * @param callback is the function that will receive a vector of the detected object(s) information
     */
    objectDetector (
                    const std::shared_ptr<rapp::object::picture> image,
                    const std::string image_format,
                    int limit,
                    std::function< void ( std::vector< rapp::object::object > ) > callback
                 )
    : rapp::services::asio_service_http (), delegate_ ( callback )
    {
        if ( !image )
            throw std::runtime_error ( "objectDetector::objectDetector param image null ptr" );
        
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
        
        // Add limit value
        post_ += "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"limit\"\r\n";
        post_ += "Content-Type: text\r\n";
        post_ += "Content-Transfer-Encoding: utf8\r\n\r\n";
        post_ += boost::lexical_cast<std::string>(limit);
        post_ += "\r\n";
        post_ += "--" + boundary + "--";
        
        // Count Data size
        auto size = post_.size() * sizeof( std::string::value_type );
        
        // Form the Header
        header_ =  "POST /hop/detect_objects HTTP/1.1\r\n";
        header_ += "Host: " + std::string( hostname ) + "\r\n";
        header_ += "Connection: close\r\n";
        header_ += "Content-Length: " + boost::lexical_cast<std::string>( size ) + "\r\n";
        header_ += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n\r\n";
        
        // bind the base class callback, to our handle_reply
        callback_ = std::bind ( &objectDetector::handle_reply, this, std::placeholders::_1 );
    }
      
  private:
    
    /// Parse @param buffer received from the socket, into a vector of faces
    void handle_reply ( boost::asio::streambuf & buffer )
    {   
        std::string json ( ( std::istreambuf_iterator<char>( &buffer ) ), std::istreambuf_iterator<char>() );
        std::stringstream ss ( json );
        std::vector< rapp::object::object > objects;
        
        try
        {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json( ss, tree );
        
            // Find the actual json objects
            for ( auto child : tree.get_child( "objects" ) )
            {
                std::string name = "Unknown";
                float score = -1;
                
                for ( auto iter = child.second.begin(); iter!= child.second.end(); ++iter )
                {
                    std::string member( iter->first );
                    
                    if ( member == "name" )
                        name = iter->second.get_value<std::string>();
                        
                    else if ( member == "score" )
                        score = iter->second.get_value<float>();
                }
                
                objects.push_back( rapp::object::object( name, score ) );
            }
        }
        catch( boost::property_tree::json_parser::json_parser_error & je )
        {
            std::cerr << "objectDetector::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        
        delegate_( objects );
    }    
    
     
    /// The callback called upon completion of receiving the detected faces
    std::function< void ( std::vector< rapp::object::object > ) > delegate_;
};

}
}

#endif
