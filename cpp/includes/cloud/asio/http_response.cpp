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
        http_response::reply_string = to_string();

        // NOTE: A BOOST REGEX is a BAD choice, it is slow - replace this with a non-regex solution!
        static const boost::regex reg("Content-Length:\\s[-0-9]+", boost::regex::icase);
        boost::match_results<std::string::const_iterator> results;

        // TODO: search for the `Content-Length:` keyword
        //       get the sustring from the end of it, to the first \r\n
        //       try casting it to an unsigned integer

        // search for matching regex
        if (boost::regex_search(reply_string, results, reg)) {
            if (results.size() > 0) {
                std::string key = results[0];
                key.erase(std::remove(key.begin(), key.end(), '\n'), key.end());

                // find the `: `
                std::string hay = ": ";
                std::size_t i = key.find(hay);
                if (i != std::string::npos) {
                    content_length_ = boost::lexical_cast<std::size_t>(key.substr(i+hay.size(), 
                                                                       std::string::npos));
                }
            }
        }
        once_ = true;
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
		boost::system::error_code err = boost::system::errc::make_error_code(
                                                            boost::system::errc::no_message);
        error_cb_(err);
        return false;
	}
	// reply is not HTTP Protocol
	else if (http_version.substr(0, 5) != "HTTP/") {
		boost::system::error_code err = boost::system::errc::make_error_code(
                                                            boost::system::errc::protocol_not_supported);
        error_cb_(err);
		return false; 
	}
    // TODO: if HTTP Reply is 404 = URL not found
    // TODO: if HTTP Reply is 500 = bad header
    // TODO: if HTTP Reply is 401 = Internal Server Error
	// HTTP reply is not 200
	else if (status_code != 200) {
		boost::system::error_code err = boost::system::errc::make_error_code(
                                                            boost::system::errc::protocol_error);
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
