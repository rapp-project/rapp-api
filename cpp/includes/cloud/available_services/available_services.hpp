#ifndef RAPP_CLOUD_AVAILABLE_SERVICES
#define RAPP_CLOUD_AVAILABLE_SERVICES
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class available_services
 * \brief requests available services from platform
 * \version 0.6.0
 * \date May 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class available_services : public asio_http
{
public:
	typedef std::pair<std::string, std::string> service;
    /**
     * \brief construct without any special parameters
     * \param callback will receive a vector of services strings
     */
    available_services(std::function<void(std::vector<service>)> callback)
    : asio_http(), delegate_(callback)
    {
		// set the HTTP header URI pramble and the Content-Type
        head_preamble_.uri = "GET /hop/available_services HTTP/1.1\r\n";

		// bind base downcasted virtual method
        callback_ = std::bind(&available_services::handle_reply, this, std::placeholders::_1);
    }

private:
    /**
     * \brief handle platform's JSON reply
     */
    void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        std::vector<service> services;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);
			// get services
            for (auto child : tree.get_child("services")) {
				for (auto iter = child.second.begin(); iter!= child.second.end(); ++iter) {
					std::string name, uri;
					if (iter->first == "name") {
						name = iter->second.get_value<std::string>();
					}
					else if (iter->first == "url") {
						uri = iter->second.get_value<std::string>();
					}
					services.push_back(std::make_pair(name, uri));
				}
            }
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "available_services JSON error: " << value << std::endl;
                }
            }
	    }
        catch (boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "available_services::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate_(std::move(services));
    }
    /// 
    std::function<void(std::vector<service> services)> delegate_;
};
}
}
#endif
