#include "http_response.hpp"

namespace rapp {
namespace cloud {

http_response::http_response(std::function<void(error_code error)> callback)
: callback_(callback)
{}

http_response::http_response(std::string arg)
{
	std::istringstream ss(arg);
	ss >> buffer_;
}

std::size_t http_response::has_content_length() const
{
	const std::string head = response::to_string();
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
		error_cb_(boost::systemm::errc::bad_message);
	}
}

std::string http_response::to_string() const  
{
	std::string buffer((std::istreambuf_iterator<char>(&buffer_)), 
						std::istreambuf_iterator<char>());
	return buffer;
}

bool http_response::check_http_header() const
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
		error_cb_(boost::system::errc::no_message);
		return false;
	}
	// reply is not HTTP Protocol
	else if (http_version.substr(0, 5) != "HTTP/") {
		error_cb_(boost::system::errc::protocol_not_supported);
		return false; 
	}
	// HTTP reply is not 200
	else if (status_code != 200) {
		error_cb_(boost::system::errc::protocol_error);
		std::cerr << status_code << std::endl;
		return false;
	}
	return true;
}
  
bool http_response::consume_buffer(std::function<void(std::string)> callback)
{
	assert(callback);
	json_ += to_string();
	bytes_transferred_ += response.size();
	// have received the data correctly
	if (bytes_transferred_ >= content_length_) {
		callback(json_); 
		return true;
	}
	return false;
}

void http_response::end()
{
	json_.clear();
	content_length_ = 0;
	bytes_transferred_ = 0;
}

}
}
