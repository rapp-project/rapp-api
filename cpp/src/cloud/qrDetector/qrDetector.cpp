#include "qrDetector.hpp"

namespace rapp {
namespace cloud {

qrDetector::qrDetector (
                            std::shared_ptr<rapp::object::picture> image,
                            std::function< void( std::vector<std::pair<float,float>> ) > callback
                       )
: callback__ ( callback )
{
    if ( image )
    {
        // Add the TAG of the Data type NOW!
        std::string tag = "<QRC>";
        std::vector<char> bytearray ( tag.begin(), tag.end() );
        
        /* 
         *  Copy the actual picture contents 
         *  asio_service_raw automatically adds an </EOF!>
         *  BUG copy to local variable the actual vector - don't use the pointer directly, we'll get std::bad_alloc!
         */
        auto imagebytes = image->bytearray();
        bytearray.insert( bytearray.end(), imagebytes.begin(), imagebytes.end() );
        
        std::string close_tag = "</EOF!>";
        bytearray.insert( bytearray.end(), close_tag.begin(), close_tag.end() );
        
        // Send raw stream over the socket
        client__ = std::make_shared<rapp::services::asio_service_raw>( bytearray,
                                                                       std::bind ( &qrDetector::handle, 
                                                                                   this,
                                                                                   std::placeholders::_1 ) );
    }
    else
        throw std::runtime_error ( "qrDetector::qrDetector param image null ptr" );
}


std::shared_ptr<rapp::services::asio_socket> qrDetector::Job ( ) const
{
    return client__;
}


void qrDetector::handle ( boost::asio::streambuf & buffer )
{   
    std::cout << "qrDetector::handle" << std::endl;
    
    // Convert the buffer into a string
    std::string reply ( ( std::istreambuf_iterator<char>( &buffer ) ), std::istreambuf_iterator<char>() );
    std::cout << reply << std::endl;

    // Discovered & parsed
    std::vector<std::pair<float,float>> qrCodes;
    
    /* 
        TODO: evaluate JSON response.
        
        { qrs : [
                { qr_center_x: float
                  qr_center_y: float
                  qr_message
                },
                ...
                ]
        }
     */
    
    // call the user defined callback
    callback__( qrCodes );
}


}
}