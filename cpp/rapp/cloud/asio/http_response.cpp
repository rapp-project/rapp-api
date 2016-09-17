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

unsigned int http_response::content_length()
{
    if (!once_) {
        using namespace boost::algorithm;
        reply_string = to_string();
        std::vector<std::string> lines;
        boost::split(lines, reply_string, boost::is_any_of("\r\n"));
        
        auto it = std::find_if(lines.begin(), lines.end(), [](std::string line) {
            return icontains<std::string, std::string>(line, "Content-Length");
        });

        if (it != lines.end()) {
            std::string line = *it;
            std::size_t begin = line.find(":") + 1;
            std::size_t end = line.find("\r\n");
            std::string key = line.substr(begin, (end - begin));
            key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
            content_length_ = boost::lexical_cast<unsigned int>(key);
            once_ = true;
        }
    }
	return content_length_;
}

unsigned int http_response::strip_http_header(unsigned int bytes) 
{
    // WARNING - call first, else if we strip we lose the `Content-Length`
    content_length_ = content_length();

	// find the "\r\n\r\n" double return after the header
	std::size_t i = reply_string.find("\r\n\r\n");

    // found OK, update the reply string
	if (i != std::string::npos) {
		reply_string = reply_string.substr(i + 4, std::string::npos);
	}
    // no "\r\n\r\n" means malformed reply
    else {
       error_cb_(boost::system::errc::make_error_code(
                                      boost::system::errc::bad_message));
       return 0;
    }

    // Transfer Bytes = Total Bytes (HTTP Header & POST data) - POST data 
    bytes_transferred_ = reply_string.size()*sizeof(std::string::value_type);
    // remaining bytes we need
    return content_length() - (bytes_transferred_);
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
		auto err = boost::system::errc::make_error_code(boost::system::errc::no_message);
        error_cb_(err);
        return false;
	}
	// reply is not HTTP Protocol
	else if (http_version.substr(0, 5) != "HTTP/") {
		auto err = boost::system::errc::make_error_code(boost::system::errc::protocol_not_supported);
        error_cb_(err);
		return false; 
	}
    // HTTP 400: bad request (bad header)
    // HTTP 404: URL not found
    // HTTP 500: Internal Server Error
    // HTTP 401: Unauthorized Acces (rapp token)
	// HTTP reply is not 200
	else if (status_code != 200) {
		auto err = boost::system::errc::make_error_code(boost::system::errc::protocol_error);
        std::cerr << http_version << " " << status_code << " " << status_message <<std::endl;
        error_cb_(err);
		return false;
	}
	return true;
}
  
unsigned int http_response::bytes_received() const
{
    return bytes_transferred_;
}

bool http_response::consume_buffer(std::function<void(std::string)> callback, unsigned int bytes)
{
	assert(callback);
    reply_string += to_string();
	bytes_transferred_ = reply_string.size()*sizeof(std::string::value_type);

	// have received the data correctly
	if (bytes_transferred_ >= content_length_) {
		callback(reply_string); 
		return true;
	}
	return false;
}

void http_response::end()
{
	reply_string.clear();
	bytes_transferred_ = 0;
}

}
}
