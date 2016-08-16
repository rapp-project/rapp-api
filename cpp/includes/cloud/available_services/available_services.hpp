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
    available_services(std::function<void(std::vector<service>)> callback)
    :http_header("GET /hop/available_services HTTP/1.1\r\n"),
     http_post(http_header::get_boundary()),
     delegate_(callback)
    {}

    /**
     * \brief handle platform's JSON reply
     */
    void deserialise(std::string json) const
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

    /**
    * \brief method to fill the buffer with http_post and http_header information
    * \param info is the data of the platform    
    */
    boost::asio::streambuf fill_buffer(rapp::cloud::platform info)
    {
           return std::move(http_request::fill_buffer(info));
    }

private:
    /// 
    std::function<void(std::vector<service> services)> delegate_;
};
}
}
#endif
