#include "../includes/service/service_controller/service_controller.hpp"
#include "../includes/cloud/ontologySubclassOf/ontologySubclassOf.hpp"

#include <iostream>
#include <string>

int main ( int argc, char* argv[] )
{
    /**
     * @date 18-April-2015
     * @author Alex Gkiokas
     * 
     * Example on how to query the superclasses of which the query is a subclass of.
     */
    
    rapp::services::service_controller ctrl;
    
    auto callback = [&]( const std::vector<std::string> classes )
                    { std::cout << "subclass of: " << classes.size() << " classes" << std::endl; };
                    
    auto subclassHandle = std::make_shared<rapp::cloud::ontologySubclassOf>( "sky", callback );
    
    // Test handler
    if ( subclassHandle )
    {
        // Request from service controller to run this job
        ctrl.runJob ( subclassHandle );
    }
    return 0;
}