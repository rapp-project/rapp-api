#ifndef RAPP_ASIO_SOCKET_HTTPS
#define RAPP_ASIO_SOCKET_HTTPS
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class asio_socket_https
 * \version 0.6.0
 * \date April 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 * \brief wrapper for SSL/TLS secure HTTP communication
 */
class asio_socket_https : public asio_socket, public asio_handler
{
public:
    /// boost tls wraps around a tcp socket
	typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> boost_tls_socket;

	/**
     * \brief construct using:
     * \param token: authentication token
     * \param user: rapp.cloud username
	 */
	asio_socket_https()
  	: asio_handler(), ctx_(boost::asio::ssl::context::tlsv12_client)
	{
        // TODO: using this only for TEST
        header_ =  "POST / HTTP/1.1\r\n";
    }

	/**
	 * schedule this as a job for execution
	 * \param query defines the URL/URI
	 * \param resolver resolves the URL/URI address
     * \param io_service is the queue on which jobs are scheduled
	 */
	void schedule(
				   boost::asio::ip::tcp::resolver::query & query,
				   boost::asio::ip::tcp::resolver & resolver,
				   boost::asio::io_service & io_service,
				   rapp::cloud::platform_info info
				 );

protected:
	/// \brief verify TLS certificate
	bool verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx);

	/// \brief begin connect
	void handle_connect(const boost::system::error_code& error);

	/// \brief handle handshake
  	void handle_handshake(const boost::system::error_code& error);

    /// Callback for handling request and waiting for response \param err is a possible error
    void handle_write(const boost::system::error_code & err);
    
    /// Callback for handling HTTP Header Response Data \param err is a possible error message
    void handle_read_status_line(const boost::system::error_code & err);

    /// Callback for Handling Headers \param err is a possible error message
    void handle_read_headers(const boost::system::error_code & err);
    
    /// Callback for Handling Actual Data Contents \param err is a possible error message
    void handle_read_content(const boost::system::error_code & err);

    /// \brief reset handler (clear data, bytes, etc) and stop connection
    void reset();

    /// \brief check timed-out
    void check_timeout();


private:
    /// tls/ssl socket wrapper
    std::unique_ptr<boost_tls_socket> tls_socket_;
	/// tls context
	boost::asio::ssl::context ctx_;
};
}
}
#endif
