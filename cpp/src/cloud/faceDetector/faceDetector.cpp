#include "faceDetector.hpp"

namespace rapp {
namespace cloud {
    
faceDetector::faceDetector ( 
                              std::shared_ptr<rapp::object::picture> image,
                              std::function< void( std::vector<std::pair<float,float>> ) > callback
                           )
:  callback__ ( callback )
{
    if ( image )
    {
        // Add the TAG of the Data type NOW
        std::string open_tag = "<FCE>";
        std::vector<char> bytearray ( open_tag.begin(), open_tag.end() );
        
        /* 
         * Copy the actual picture contents 
         * asio_service_raw automatically adds an </EOF!>
         * ΒΘΓ copy to local variable the actual vector - don't use the pointer directly, we'll get std::bad_alloc!
         */
        auto imagebytes = image->bytearray();
        bytearray.insert( bytearray.end(), imagebytes.begin(), imagebytes.end() );
        
        std::string close_tag = "</EOF!>";
        bytearray.insert( bytearray.end(), close_tag.begin(), close_tag.end() );
        
        // Send raw stream over the socket
        client__ = std::make_shared<rapp::services::asio_service_raw>( bytearray,
                                                                       std::bind ( &faceDetector::handle, 
                                                                                   this,
                                                                                   std::placeholders::_1 ) );
    }
    else
        throw std::runtime_error ( "faceDetector::faceDetector param image null ptr" );
}


std::shared_ptr<rapp::services::asio_socket> faceDetector::Job ( ) const
{
    return client__;
}


void faceDetector::handle ( boost::asio::streambuf & buffer )
{   
    // Convert the buffer into a string
    std::cout << "faceDetector::handle" << std::endl;
    
    std::string reply ( ( std::istreambuf_iterator<char>( &buffer ) ), std::istreambuf_iterator<char>() );
    std::cout << reply << std::endl;

    // Discovered & parsed
    std::vector<std::pair<float,float>> faces;
    
    /* 
        TODO: evaluate JSON response
        
        { faces : [
                    {
                        top_left_x : float,
                        top_left_y : float,
                        bottom_right_x : float,
                        botom_right_y : float
                    },
                    ...
                  ]
        }
     */
    
    // call the user defined callback
    callback__( faces );
}


}
}
