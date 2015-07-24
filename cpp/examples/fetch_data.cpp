#include "../includes/service/service_controller/service_controller.hpp"
#include "../includes/cloud/fetchPersonalData/fetchPersonalData.hpp"

#include <iostream>
#include <string>

int main ( int argc, char* argv[] )
{
    /**
     * @date 18-April-2015
     * @author Alex Gkiokas
     * 
     * Example on how to fetch a user's personal data (a JSON string)
     */
    rapp::services::service_controller ctrl;
    
    auto callback = [&]( const std::string json ){ std::cout << "JSON: " << json << std::endl;};
    auto fetchHandle = std::make_shared<rapp::cloud::fetchPersonalData>( "alex", callback );
    
    // Create the fetch Data handler, and pass it the username and a callback that will receive the reply.
    if ( fetchHandle )
    {
        // Request from service controller to run this job
        ctrl.runJob ( fetchHandle );
    }
    return 0;
}