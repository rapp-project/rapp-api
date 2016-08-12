#ifndef RAPP_ASIO_SOCKET_HTTPS
#define RAPP_ASIO_SOCKET_HTTPS
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class asio_https
 * \version 0.7.0
 * \date August 2016
 * \author Maria Ramos  <m.ramos@ortelio.co.uk>
 * \brief wrapper for SSL/TLS secure HTTP communication
 */
class asio_https : private asio_socket<tls_socket> 
{
public:

    asio_https(
                std::function<void(error_code error)> callback,
                boost::asio::io_service & io_service,
                boost::asio::streambuf request
             )
    : ctx_(boost::asio::ssl::context::tlsv12_client), 
      
    {
        socket_ = std::make_shared<tls_socket>(io_service, ctx_);
        hadler_ = asio_socket<tls_socket>(std::bind(&asio_https<tls_socket>::connect, this, std::placeholders::_1),
                                          callback, 
                                          socket_);
    }

	/**
	 * schedule this as a job for execution
	 * \param query defines the URL/URI
	 * \param resolver resolves the URL/URI address
     * \param io_service is the queue on which jobs are scheduled
	 */
	void begin(
			    boost::asio::ip::tcp::resolver::query & query,
			    boost::asio::ip::tcp::resolver & resolver
             );

protected:

	/// \brief verify TLS certificate
	bool verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx)
    {
        char subject_name[256];
        X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
        X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
        return preverified;
    }

	/// \brief begin connect
	void connect(const boost::system::error_code& error);

	/// \brief handle handshake
  	void handshake(const boost::system::error_code& error)
    {
         assert(socket_;
        if (!error) {
            // write to the socket
            boost::asio::async_write(*socket_,
                                     request_,
                                     boost::bind(&asio_socket::handle_write, 
                                                 this->handler_,
                                                 boost::asio::placeholders::error));
        }
        else {
            std::cerr << "Handshake failed: " << error.message() << "\n";
        }   
    }

private:
	/// tls context
	boost::asio::ssl::context ctx_;
    /// asio handler
    rapp::cloud::asio_socket<tls_socket> handler_;
    /// boost asio socket 
    std::shared_ptr<tls_socket> socket_;
    /// request object
    boost::asio::streambuf request_;
};
}
}
#endif
