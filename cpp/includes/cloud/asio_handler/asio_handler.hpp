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


	asio_handler()
	: io_timer_()
	{}

	/// \brief create an HTTP header using the \param info
	std::string make_header(
							rapp::cloud::platform_info info,
							rapp::cloud::header head,
							unsigned int post_length
						   );

    /// \brief Handle an Error \param error is the raised error from the client
    void error_handler(const boost::system::error_code & error);

    /// \brief Handle Invalid Query - e.g.: response which states our query was invalid 
    void invalid_request(const std::string message);
    
    /// \brief get the content leangth from \param header
    void content_length(std::string response, std::size_t& length);

    /// \brief examine if the header response contains a `content-length` filed
    bool has_content_length(std::string response);
    
    /// \brief remove/strip the HTTP header and \return the body
    std::string strip_header(std::string response);
    
	/// \brief Create a random boundary for the multipart/form in HTTP
    std::string random_boundary() const;
    
    /// \brief escape JSON strings when sending them over the socket
    /// \param str will be escaped and returned
    std::string escape_string(const std::string & str);
    
	/// \brief decode base64
    /// \param val must be encoded using base64
    std::string decode64(const std::string &val);
    
	/// \brief encode base64
    /// \param val must be plain-text string
    /// \return a base64 encoded string
    std::string encode64(const std::string &val);
    
protected:
	/// ...
	rapp::cloud::header head_preamble_;
	/// DEPRECATE
	std::string header_;
    /// Actual post Data
    std::string post_;
    /// Callback Handler - use with std::bind or boost variant
    std::function<void(std::string)> callback_;
    /// Request Container
    boost::asio::streambuf request_;
    /// Response Container
    boost::asio::streambuf response_;
    /// time-out timer
    std::unique_ptr<boost::asio::deadline_timer> timer_;
	/// time-out service (runs one timeout per class)
	boost::asio::io_service io_timer_;
    /// flag used to extract header
    std::atomic<bool> flag_  = {false};
    /// Content-Length
    std::size_t content_length_ = 0;
    /// Bytes Transferred
    std::size_t bytes_transferred_ = 0;
    /// JSON reply
    std::string json_;
	/// time-out in seconds
	const unsigned int timeout_ = 120;
};
}
}
/// convenience function `std::make_unique` for non c++14 compilers
#if __cplusplus==201402L
// c++14 - nothing here
#elif __cplusplus==201103L
// c++11 - 
namespace std {
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}
#endif
#endif
