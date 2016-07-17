#ifndef RAPP_CLOUD_GEOLOCATION
#define RAPP_CLOUD_GEOLOCATION
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \brief geolocation service
 * \class geolocation
 * \version 0.6.0
 * \date May 2016
 */
class geolocation : public asio_service_http
{
public:
    /**
     * \param ipaddr: the machine's ip
     * \param engine: the API (default ip-api)
     * \param callback: receives a JSON reply
     */
    geolocation(
                 const std::string ipaddr,
                 const std::string engine,
                 std::function<void(std::string)> callback,
                 rapp::cloud::platform_info info
               )
	: asio_service_http(info), delegate_(callback)
	{
        boost::property_tree::ptree tree;
        tree.put("ipaddr", ipaddr);
        tree.put("engine", engine);
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        post_ = ss.str();
        header_ = "POST /hop/geolocation HTTP/1.1\r\n"
                + "Content-Type: application/x-www-form-urlencoded\r\n";
        callback_ = std::bind(&geolocation::handle_reply, this, std::placeholders::_1);
	}
private:
    /**
     * \brief handle platform's JSON reply
     */
	void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        delegate_(std::move(json));
    }
    /// 
    std::function<void(std::string)> delegate_;
};
}
}
#endif
