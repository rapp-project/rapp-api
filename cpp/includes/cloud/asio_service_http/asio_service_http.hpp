#ifndef RAPP_ASIO_SERVICE_HTTP
#define RAPP_ASIO_SERVICE_HTTP
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class asio_service_http
 * \brief base class for asynchronous http websockets used for connecting to cloud services
 * \version 6
 * \date April 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class asio_service_http : public asio_socket, protected asio_helper
{
public:

	/**
	 * Construct the asio http service
	 * \param token is the rapp.cloud authentication token
	 */
	asio_service_http(const std::string token)
	: token_(token){}

    /** 
     * schedule this client as a job for execution using
     * \param query defines the actual URL/URI
     * \param resolver is the URL/URI resolver reference
     * \param io_service is the queue on which jobs are scheduled
     */
    void schedule( 
				  boost::asio::ip::tcp::resolver::query & query,
				  boost::asio::ip::tcp::resolver & resolver,
				  boost::asio::io_service & io_service
                 )
    {
        if (!socket_){
            socket_ = std::unique_ptr<boost::asio::ip::tcp::socket>(
									  new boost::asio::ip::tcp::socket(io_service));
		}
        std::ostream request_stream(&request_);
        request_stream << header_ << post_ << "\r\n";
        resolver.async_resolve(query,
                               boost::bind(&asio_service_http::handle_resolve,
                                           this,
                                           boost::asio::placeholders::error,
                                           boost::asio::placeholders::iterator));
    }
    
protected:  
    
    /** 
     * \brief Callback for Handling Address Resolution
     * \param err is a possible error
     * \param endpoint_iterator is boost's hostname address handler
     */
    void handle_resolve( 
                         const boost::system::error_code & err,
                         boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                       );

    /**
     * Callback for Handling Connection Events
     * \param err is a possible error
     * \param endpoint_iterator is boosts' hostname address handler
     */
    void handle_connect( 
                          const boost::system::error_code & err,
                          boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                       );

    /// Callback for handling request and waiting for response \param err is a possible error
    void handle_write_request(const boost::system::error_code & err);
    
    /// Callback for handling HTTP Header Response Data \param err is a possible error message
    void handle_read_status_line(const boost::system::error_code & err);

    /// Callback for Handling Headers \param err is a possible error message
    void handle_read_headers(const boost::system::error_code & err);
    
    /// Callback for Handling Actual Data Contents \param err is a possible error message
    void handle_read_content(const boost::system::error_code & err, std::size_t bytes);

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
	/// user authentication token
	const std::string token_;
    /// Content-Length once flag
    std::once_flag cflag_;
    /// Content-Length
    std::size_t content_length_ = 0;
    /// Bytes Transferred
    std::size_t bytes_transferred_ = 0;
    /// JSON reply
    std::string json_;
};
}
}
#endif
