#include "../includes/service/service_controller/service_controller.hpp"
#include "../includes/cloud/objectDetector/objectDetector.hpp"
#include "../includes/objects/picture/picture.hpp"

int main ( int argc, char* argv[] )
{
    /**
     * @date 02-Jul-2015
     * @author Maciej Stefańczyk
     * This is now the default way of working with images
     */
    rapp::services::service_controller ctrl;
    
    auto pic = std::make_shared<rapp::object::picture>( argc > 1 ? argv[1] : "aircraft.jpg" );
    
    if ( pic )
    {
        auto callback = [&]( std::vector<rapp::object::object> objects )
                        { 
                            std::cout << "found " << objects.size() << " objects!" << std::endl;}
                        ;
                        
        auto odetect = std::make_shared<rapp::cloud::objectDetector>( pic, "jpg", 2, callback );
        
        if ( odetect )
            ctrl.runJob ( odetect );
    }
    else
        std::cerr << "Error loading image" << std::endl;

    return 0;
}
