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
typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> tls_socket;

class asio_https  
{
public:

    asio_https(
                std::function<void(std::string)> cloud_cb,
                std::function<void(error_code error)> callback,
                boost::asio::io_service & io_service,
                boost::asio::streambuf request
             )
    : ctx_(boost::asio::ssl::context::tlsv12_client), error_cb_(callback) 
      
    {
        socket_ = std::make_shared<tls_socket>(io_service, ctx_);
        hadler_ = asio_socket<tls_socket>(cloud_cb, callback, socket_);
		assert(socket_ && handler_);
    }

	/**
	 * \brief begin connection
	 * \param query defines the URL/URI
	 * \param resolver resolves the URL/URI address
     * \param io_service is the queue on which jobs are scheduled
     * \warning disable ssl v2 and ssl v3 (allow only tls)
	 */
	void begin(
			    boost::asio::ip::tcp::resolver::query & query,
			    boost::asio::ip::tcp::resolver & resolver
              )
    {
        ctx_.set_options(boost::asio::ssl::context::default_workarounds
                        |boost::asio::ssl::context::no_sslv2
                        |boost::asio::ssl::context::no_sslv3
                        |boost::asio::ssl::context::no_tlsv1
                        |boost::asio::ssl::context::single_dh_use);
        // if using a self-signed certificate the only way to pass verification
        // is to "install" it locally and use it for comparison
        ctx_.load_verify_file("ca.pem");
        socket_->set_verify_mode(boost::asio::ssl::verify_peer 
                                |boost::asio::ssl::verify_fail_if_no_peer_cert);
        socket_->set_verify_callback(boost::bind(verify_certificate, 
                                                 this, _1, _2));
        // resolve and connect
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		boost::system::error_code error = boost::asio::error::host_not_found;
		while (error && endpoint_iterator != end) {
			socket_->close();
			boost::asio::async_connect(socket_->lowest_layer(), 
									   endpoint_iterator,
									   boost::bind(&asio_https::connect, 
												   this,
												   boost::asio::placeholders::error));
		}
		if (error) {
			handler_->end(error);
		}
	}

protected:

	/// \brief verify TLS certificate
	bool verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx)
    {
        char subject_name[256];
        X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
        X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
        return preverified;
    }

	/// \brief begin connection
	void connect(const boost::system::errc err)
    {
		if (erro) {
            handler_->end(boost::system::errc::not_connected);
			return;
		}
		socket_->async_handshake(boost::asio::ssl::stream_base::client,
								 boost::bind(&asio_https::handshake, 
											 this,
											 boost::asio::placeholders::err));
    }

	/// \brief handle handshake
  	void handshake(const boost::system::errc err)
    {
        if (err) {
			handler_->end(error);
            std::cerr << "Handshake failed: " << err.message() << "\n";
			return;
		}
		boost::asio::async_write(*socket_,
								 request_,
								 boost::bind(&asio_socket::write_request, 
											 this->handler_,
											 boost::asio::placeholders::err));
    }

private: 

    /// error callback
    std::function<void(boost::system::errc)> error_cb_;
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
