#ifndef RAPP_ASIO_HANDLER
#define RAPP_ASIO_HANDLER
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \struct platform_info
 * \version 0.6.0
 * \date July 2016
 * \brief use to construct a service controller with correct params
 */
struct platform_info
{
    std::string address;
    std::string port;
    std::string token;
};

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

    /// ctor
    asio_handler(rapp::cloud::platform_info info)
    : token_(info.token), address_(info.address), port_(info.port)
    {}

    /// Handle an Error \param error is the raised error from the client
    void error_handler(const boost::system::error_code & error);

    /// Handle Invalid Query - e.g.: response which states our query was invalid 
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
    /// Header that will be used
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
    /// flag used to extract header
    std::atomic<bool> flag_  = {false};
    /// Content-Length
    std::size_t content_length_ = 0;
    /// Bytes Transferred
    std::size_t bytes_transferred_ = 0;
    /// JSON reply
    std::string json_;

    /// user authentication token
	const std::string token_;
    const std::string address_;
    const std::string port_;
};
}
}
#endif
