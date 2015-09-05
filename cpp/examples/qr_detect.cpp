#include "../includes/service/service_controller/service_controller.hpp"
#include "../includes/cloud/qrDetector/qrDetector.hpp"
#include "../includes/objects/picture/picture.hpp"

int main ( int argc, char* argv[] )
{
    /**
     * @date 13-February-2015
     * @author Alex Gkiokas
     * This is now the default way of working with images
     */
    rapp::services::service_controller ctrl;
    
    auto pic = std::make_shared<rapp::object::picture>( "qrcode.png" );
    
    auto callback = [&]( std::vector< rapp::object::qrCode > codes )
                    {
                        std::cout << "found " << codes.size() << " QR codes" << std::endl;
                        for ( const auto code : codes )
                            std::cout << code.label() << std::endl;
                        
                    };
    
    auto fdetect = std::make_shared<rapp::cloud::qrDetector>( pic, "png", callback );
    
    ctrl.runJob ( fdetect );
    
    return 0;
} 
