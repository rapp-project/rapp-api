#ifndef RAPP_CLOUD_AVAILABLE_SERVICES
#define RAPP_CLOUD_AVAILABLE_SERVICES
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class available_services
 * \brief requests available services from platform
 * \version 0.7.0
 * \date 14 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class available_services : public http_request
{
public:
	typedef std::pair<std::string, std::string> service;

    /**
     * \brief construct without any special parameters
     * \param callback will receive a vector of services strings
     */
    available_services(std::function<void(std::vector<service>)> callback);
    
    /** 
     * \brief fill the buffer and return a handler
     * \param request is the buffer which will contain the request for asio
     * \param info is the rapp cloud platform
     */
    void operator()(
                      boost::asio::streambuf & request,
                      rapp::cloud::platform info
                   );

private:

    /**
     * \brief handle platform's JSON reply
     */
    void deserialise(std::string json);

    /// user's handler
    std::function<void(std::vector<service> services)> delegate_;
};
}
}
#endif
