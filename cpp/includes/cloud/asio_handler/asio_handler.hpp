#ifndef RAPP_ASIO_HANDLER
#define RAPP_ASIO_HANDLER
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class asio_handler
 * \version 0.6.0
 * \date April 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 * \brief base class for asio handling, including helper methods
 *        and most protected members
 */
class asio_handler
{
public:

    /// ctor
    asio_handler(const std::string token)
    : token_(token)
    {}

    /// Handle an Error \param error is the raised error from the client
    void error_handler(const boost::system::error_code & error)
    {
        std::cerr << "error: " << error.message() << std::endl;
    }

    /// Handle Invalid Query - e.g.: response which states our query was invalid 
    void invalid_request(const std::string message)
    {
        std::cerr << "invalid request: " <<  message << std::endl;
    }

    /// \brief get the content leangth from
    /// \param header
    void content_length(std::string response, std::size_t & length)
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

    bool has_content_length(std::string response)
    {
        static const boost::regex reg("Content-Length:\\s[-0-9]+", 
                                      boost::regex::icase);
        boost::match_results<std::string::const_iterator> results;
        // search for matching regex
        if (boost::regex_search(response, results, reg)) {
            return (results.size() > 0 ? true : false);
        }
        else {
            return false;
        }
    }

    std::string strip_header(std::string response)
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

	/// \brief Create a random boundary for the multipart/form in HTTP
    std::string random_boundary() const
    {
        std::string chars("abcdefghijklmnopqrstuvwxyz"
                          "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                          "1234567890");
        boost::random::random_device rng;
        std::string uid;
        // Randomly chose 16 characters
        boost::random::uniform_int_distribution<> index_dist(0, chars.size() - 1);
        for (int i = 0; i < 16; ++i){
            uid.push_back(chars[index_dist(rng)]);
		}
        return uid;
    }

    /// \brief escape JSON strings when sending them over the socket
    /// \param str will be escaped and returned
    std::string escape_string(const std::string & str) 
    {
        std::ostringstream ss;
        for (auto iter = str.cbegin(); iter != str.cend(); iter++) {
            switch (*iter) {
                case '\\': ss << "\\\\"; break;
                case '"': ss << "\\\""; break;
                case '/': ss << "\\/"; break;
                case '\b': ss << "\\b"; break;
                case '\f': ss << "\\f"; break;
                case '\n': ss << "\\n"; break;
                case '\r': ss << "\\r"; break;
                case '\t': ss << "\\t"; break;
                default: ss << *iter; break;
            }
        }
        return ss.str();
    } 

	/// \brief decode base64
    /// \param val must be encoded using base64
    std::string decode64(const std::string &val)
    {
        using namespace boost::archive::iterators;
        using It = transform_width<binary_from_base64<std::string::const_iterator>, 8, 6>;
        return boost::algorithm::trim_right_copy_if(std::string(It(std::begin(val)), 
																It(std::end(val))), 
																[](char c) {return c == '\0';});
    }

	/// \brief encode base64
    /// \param val must be plain-text string
    /// \return a base64 encoded string
    std::string encode64(const std::string &val)
    {
        using namespace boost::archive::iterators;
        using It = base64_from_binary<transform_width<std::string::const_iterator, 6, 8>>;
        auto tmp = std::string(It(std::begin(val)), It(std::end(val)));
        return tmp.append((3 - val.size() % 3) % 3, '=');
    }

protected:

    /// Header that will be used
    std::string header_;
    /// Actual post Data
    std::string post_;
    /// Callback Handler - use with std::bind or boost variant
    std::function<void(std::string)> callback_;
    /// Actual Socket
    std::unique_ptr<boost::asio::ip::tcp::socket> socket_;
    /// Request Container
    boost::asio::streambuf request_;
    /// Response Container
    boost::asio::streambuf response_;
    /// Content-Length once flag
    std::once_flag cflag_;
    /// Content-Length
    std::size_t content_length_ = 0;
    /// Bytes Transferred
    std::size_t bytes_transferred_ = 0;
    /// JSON reply
    std::string json_;
    /// user authentication token
	const std::string token_;
};
}
}
#endif
