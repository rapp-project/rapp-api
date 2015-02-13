#include "faceDetector.hpp"

namespace rapp {
namespace cloud {
    
faceDetector::faceDetector ( 
                              std::shared_ptr<rapp::object::picture> image,
                              std::function< void (  std::vector< rapp::object::face > ) > callback
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
    // Cast buffer to string, and strip the </EOF!> tag
    std::string json ( ( std::istreambuf_iterator<char>( &buffer ) ), std::istreambuf_iterator<char>() );
    boost::replace_all( json, "</EOF!>", "" );
    std::stringstream ss ( json );

    // Discovered & parsed
    std::vector< rapp::object::face > faces;
    
    // Populate boost tree , by reading in the json
    boost::property_tree::ptree tree;
    boost::property_tree::read_json( ss, tree );
    
    /* 
    { faces : [
                {
                    top_left_x : float,
                    top_left_y : float,
                    bottom_right_x : float,
                    botom_right_y : float
                },
                ...
                ]
    } */
    
    // Iterate faces array
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
    
    // call the user defined callback
    callback__( faces );
}


}
}
