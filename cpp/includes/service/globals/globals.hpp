#ifndef RAPP_SERVICE_CLOUD_GLOBALS
#define RAPP_SERVICE_CLOUD_GLOBALS

namespace rapp {
    
namespace cloud {

    /**
    * A few global strings needed internally
    * @version 3
    * @date 13-February-2015
    * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
    */

    /// api.rapp.cloud - use deployment IP@ITI
    constexpr char address[] = "155.207.19.229";

    /// api.rapp.cloud - HOP server port
    constexpr char port[] = "9001";    

    /// base64 encoded authentication token
    constexpr char auth_token[] = "cmFwcGRldjpyYXBwZGV2";
}

namespace types
{    
    typedef char byte;
}

}
#endif
