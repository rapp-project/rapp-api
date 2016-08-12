#include "http_request.hpp"
namespace rapp {
namespace cloud {

http_request::http_request(
					const rapp::cloud::http_header header, 
					const rapp::cloud::http_post post
				)
: header_(header), post_(post)
{}

boost::asio::streambuf http_request::fill_buffer(rapp::cloud::platform info) 
{
	boost::asio::streambuf buffer;
	std::ostream http_request_stream(&buffer);
	http_request_stream << header_.to_string(info, post_.size()) 
					    << post_.to_string();
	return std::move(buffer);
}

}
}
