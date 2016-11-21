#ifndef RAPP_CONFIG
#define RAPP_CONFIG
#include "includes.ihh"
namespace rapp {
namespace config {

/// \brief helper function, loads YAML configuration file
rapp::cloud::platform_info load_yaml_config(std::string filename);

/// \brief helper function, loads AUTH token from file
std::string	load_auth_token(std::string filename);

}
}
#endif
