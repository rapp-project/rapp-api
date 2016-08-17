#include "http_response.hpp"

namespace rapp {
namespace cloud {

http_response::http_response(std::function<void(error_code error)> callback)
: error_cb_(callback)
{}

http_response::http_response(std::string arg)
{
	std::ostream ss(&buffer_);
	ss << arg;
}

std::size_t http_response::has_content_length()
{
	std::string head = this->to_string();
	static const boost::regex reg("Content-Length:\\s[-0-9]+", boost::regex::icase);
	boost::match_results<std::string::const_iterator> results;
	std::size_t length = -1;
	// search for matching regex
	if (boost::regex_search(head, results, reg)) {
		if (results.size() > 0) {
			std::string key = results[0];
			key.erase(std::remove(key.begin(), key.end(), '\n'), key.end());
			// find the `: `
			std::string hay = ": ";
			std::size_t i = key.find(hay);
			if (i != std::string::npos) {
				length = boost::lexical_cast<std::size_t>(key.substr(i+hay.size(),
																	 std::string::npos));
			}
		}
	}
	return length;
}

std::string http_response::strip_http_header(const std::string & data) const
{
	// find the "\r\n\r\n" double return after the header
	std::size_t i = data.find("\r\n\r\n");
	if (i != std::string::npos) {
		return data.substr(i+4, std::string::npos);
	}
	else {
        boost::system::error_code err = boost::system::errc::make_error_code(boost::system::errc::bad_message);
        error_cb_(err);
        std::string error = "Error";
        return error;
	}
}

std::string http_response::to_string() 
{
	std::string buffer((std::istreambuf_iterator<char>(&buffer_)), 
						std::istreambuf_iterator<char>());
	return buffer;
}

bool http_response::check_http_header()
{
	std::istream buffer_stream(&buffer_);
	std::string http_version;
	buffer_stream >> http_version;
	unsigned int status_code;
	buffer_stream >> status_code;
	std::string status_message;
	std::getline(buffer_stream, status_message);
	// did not receive a reply
	if (!buffer_stream) {
		boost::system::error_code err = boost::system::errc::make_error_code(boost::system::errc::no_message);
        error_cb_(err);
        return false;
	}
	// reply is not HTTP Protocol
	else if (http_version.substr(0, 5) != "HTTP/") {
		boost::system::error_code err = boost::system::errc::make_error_code(boost::system::errc::protocol_not_supported);
        error_cb_(err);
		return false; 
	}
	// HTTP reply is not 200
	else if (status_code != 200) {
		boost::system::error_code err = boost::system::errc::make_error_code(boost::system::errc::protocol_error);
        error_cb_(err);
		std::cerr << status_code << std::endl;
		return false;
	}
	return true;
}
  
bool http_response::consume_buffer(std::function<void(std::string)> callback)
{
	assert(callback);
	json_ += to_string();
	bytes_transferred_ += buffer_.size();
	// have received the data correctly
	if (bytes_transferred_ >= has_content_length()) {
		callback(json_); 
		return true;
	}
	return false;
}

void http_response::end()
{
	json_.clear();
	bytes_transferred_ = 0;
}

}
}
