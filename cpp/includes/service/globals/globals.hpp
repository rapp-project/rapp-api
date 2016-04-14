#ifndef RAPP_SERVICE_CLOUD_GLOBALS
#define RAPP_SERVICE_CLOUD_GLOBALS
namespace rapp {
namespace cloud {
///
/// A few global strings needed internally
/// @version 3
/// @date 13-February-2015
/// @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
///
/// TODO: DEPRECATE address, port, auth_token: compose within `service_controller`
/// api.rapp.cloud - use deployment IP@ITI Deployment: 155.207.19.13, Development: 155.207.19.229
constexpr char address[] = "localhost";
/// api.rapp.cloud - HOP server port
constexpr char port[] = "9001";    
}
namespace types {
typedef char byte;
}
}
#endif
