#include "asio_handler.hpp"
namespace rapp {
namespace cloud {

std::string asio_handler::make_header(
									  rapp::cloud::platform_info info,
									  rapp::cloud::header head,
									  unsigned int post_length
									 )
{
	// craft the HTTP Header
	head.host = "Host: " + info.address + ":" + info.port + "\r\n";
	head.user_agent = "User-Agent: rapp_api/cpp/0.6.0\r\n";
	head.accept_token = "Accept-Token: " + info.token + "\r\n";
	head.connection = "Connection: Keep-Alive\r\n";
	head.content_length = "Content-Length: " 
						+ boost::lexical_cast<std::string>(post_length) +"\r\n";

	// craft the header string
	return head.uri 
		   + head.host 
		   + head.user_agent 
		   + head.connection
		   + "Accept: */*\r\n" 
		   + head.accept_token
		   + head.content_length 
		   + head.content_type 
		   + "\r\n\r\n";
}

void asio_handler::error_handler(const boost::system::error_code & error)
{
	std::cerr << boost::system::system_error(error).what() << std::endl;
}

void asio_handler::invalid_request(const std::string message)
{
    std::cerr << "invalid http request: " <<  message << std::endl;
}

void asio_handler::content_length(std::string response, std::size_t & length)
{
    static const boost::regex reg("Content-Length:\\s[-0-9]+", 
                                  boost::regex::icase);
    boost::match_results<std::string::const_iterator> results;
    // search for matching regex
    if (boost::regex_search(response, results, reg)) {
        if (results.size() > 0) {
            std::string key = results[0];
            key.erase(std::remove(key.begin(), 
                                  key.end(), '\n'), 
                                  key.end());
            // find the `: `
            std::string hay = ": ";
            std::size_t i = key.find(hay);
            if (i != std::string::npos) {
                length = boost::lexical_cast<std::size_t>(
                                    key.substr(i+hay.size(), std::string::npos));
            }
            else {
                std::cerr << "malformed `Content-Lengtht` delimiter" << std::endl;
            }
        }
    }
}

bool asio_handler::has_content_length(std::string response)
{
    static const boost::regex reg("Content-Length:\\s[-0-9]+", boost::regex::icase);
    boost::match_results<std::string::const_iterator> results;
    // search for matching regex
    if (boost::regex_search(response, results, reg)) {
        return (results.size() > 0 ? true : false);
    }
    else {
        return false;
    }
}

std::string asio_handler::strip_header(std::string response)
{

    // find the "\r\n\r\n" double return after the header
    std::size_t i = response.find("\r\n\r\n");
    if (i != std::string::npos) {
        return response.substr(i+4, std::string::npos);
    }
    else {
        throw std::runtime_error("no double return after header");
    }
}

}
}
