///
/// fetch Personal data is deprecated
///
/*
int main ( int argc, char* argv[] )
{
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
*/
