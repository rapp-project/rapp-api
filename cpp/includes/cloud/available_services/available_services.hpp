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
class available_services : public caller, public http_request
{
public:
	typedef std::pair<std::string, std::string> service;
    /**
     * \brief construct without any special parameters
     * \param callback will receive a vector of services strings
     */
    available_services(std::function<void(std::vector<service>)> callback);
    
    /**
     * \brief handle platform's JSON reply
     */
    void deserialise(std::string json) const;

    /**
     * \brief method to fill the buffer with http_post and http_header information
     * \param info is the data of the platform
     * \param request is a stream buffer used for socket IO
     */
    void fill_buffer(
                       boost::asio::streambuf & request,
                       rapp::cloud::platform info
                    );
    
private:
    /// 
    std::function<void(std::vector<service> services)> delegate_;
};
}
}
#endif
