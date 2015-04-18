#include "qrDetector.hpp"

namespace rapp {
namespace cloud {

qrDetector::qrDetector (
                            std::shared_ptr<rapp::object::picture> image,
                            std::function< void ( std::vector< rapp::object::qrCode> ) > callback
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
        
        // Always add a closing Tag
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
    // Cast buffer to string, and strip the </EOF!> tag
    std::string json ( ( std::istreambuf_iterator<char>( &buffer ) ), std::istreambuf_iterator<char>() );
    boost::replace_all( json, "</EOF!>", "" );
    std::stringstream ss ( json );

    // Discovered & parsed
    std::vector< rapp::object::qrCode > qrCodes;

    // Populate boost tree , by reading in the json
    boost::property_tree::ptree tree;
    boost::property_tree::read_json( ss, tree );
    
    /*  { qrs : [
                { qr_center_x: float
                  qr_center_y: float
                  qr_message
                },
                ...
                ] }                     */
    
    // Iterate qrs array
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
    
    // call the user defined callback
    callback__( qrCodes );
}


}
}