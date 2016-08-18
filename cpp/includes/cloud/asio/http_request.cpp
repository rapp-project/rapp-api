#include "http_request.hpp"
namespace rapp {
namespace cloud {

http_request::http_request(const std::string uri)
{
    if (uri.empty()) {
        throw std::runtime_error("empty uri param");
    }
    header_ = std::make_unique<rapp::cloud::http_header>(uri);
    post_   = std::make_unique<rapp::cloud::http_post>(header_->get_boundary());
    assert(header_ && post_);
}

void http_request::fill_buffer(
                                boost::asio::streambuf & buffer,
                                rapp::cloud::platform info
                              ) 
{
	std::ostream http_request_stream(&buffer);
	http_request_stream << header_->to_string(info, post_->size()) 
					    << post_->to_string();
}

void http_request::close()
{
    post_->end();
}

std::string http_request::to_string(rapp::cloud::platform info) const
{
    return header_->to_string(info, post_->size()) + post_->to_string();
}

bool http_request::operator==(const http_request & rhs) const
{
    return (this->header_ == rhs.header_) && (this->post_ == rhs.post_);
}

}
}
