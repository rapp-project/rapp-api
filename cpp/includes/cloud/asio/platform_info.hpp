#ifndef RAPP_ASIO_PLATFORM_INFO
#define RAPP_ASIO_PLATFORM_INFO
#include <string>
namespace rapp {
namespace cloud {
/**
 * \struct platform_info
 * \version 0.6.0
 * \date July 2016
 * \brief use to construct a service controller with correct params
 */
struct platform_info
{
   std::string address;
   std::string port;
   std::string token;
   std::string protocol;
};
}
}
#endif
