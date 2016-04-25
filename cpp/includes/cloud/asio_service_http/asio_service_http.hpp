#ifndef RAPP_ASIO_SERVICE_HTTP
#define RAPP_ASIO_SERVICE_HTTP
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class asio_service_http
 * \brief base class for asynchronous http websockets used for connecting to cloud services
 * \version 0.6.0
 * \date April 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class asio_service_http : public asio_socket, protected asio_handler
{
public:

	/**
	 * Construct the asio http service
	 * \param token is the rapp.cloud authentication token
	 */
	asio_service_http(const std::string token)
	: asio_handler(token)
    {}

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
        auto content_length = post_.size() * sizeof(std::string::value_type);
        header_ += "Host: " + std::string(rapp::cloud::address) + "\r\n"
                + "Accept-Token: " + token_ + "\r\n"
                + "Connection: close\r\n"
                + "Content-Length: " + boost::lexical_cast<std::string>(content_length)
                + "\r\n\r\n";

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


    /// TCP Socket
    std::unique_ptr<boost::asio::ip::tcp::socket> socket_;
};
}
}
#endif
