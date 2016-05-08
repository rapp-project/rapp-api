#ifndef RAPP_ASIO_SERVICE_HTTP
#define RAPP_ASIO_SERVICE_HTTP
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class asio_service_http
 * \brief base class for asynchronous http websockets used for connecting to cloud services
 * \version 0.6.0
 * \date May 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 * TODO: rename to `asio_socket_http`
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
                 );
    
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

    /// \brief reset handler (clear data, bytes, etc) and stop connection
    void reset();

    /// \brief check timed-out
    void check_timeout();

private:
    /// TCP Socket (plain-text)
    std::unique_ptr<boost::asio::ip::tcp::socket> socket_;
};
}
}
#endif
