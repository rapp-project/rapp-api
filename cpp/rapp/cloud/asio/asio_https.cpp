#include "asio_https.hpp"
namespace rapp {
namespace cloud {

asio_https::asio_https(
						std::function<void(std::string)> cloud_function,
						std::function<void(error_code error)> error_function,
						boost::asio::io_service & io_service,
						boost::asio::streambuf & request
					  )
:  asio_handler<tls_socket>(cloud_function, 
                            error_function,
                            boost::bind(&asio_https::shutdown,
                                        this,
                                        boost::asio::placeholders::error)),  
    error_cb_(error_function), 
    ctx_(boost::asio::ssl::context::tlsv12_client),
    request_(request)
{
	socket_ = std::make_shared<tls_socket>(io_service, ctx_);
    deadline_ = std::make_shared<boost::asio::deadline_timer>(io_service);
	assert(cloud_function && error_function && socket_);
	asio_handler::set_socket(socket_);
    deadline_->async_wait(boost::bind(&asio_https::time_check, this)); 
	// set context option for TLS - allow only TLS v1.2 and later
	ctx_.set_options(boost::asio::ssl::context::default_workarounds
					 | boost::asio::ssl::context::no_sslv2
					 | boost::asio::ssl::context::no_sslv3
					 | boost::asio::ssl::context::no_tlsv1
					 | boost::asio::ssl::context::single_dh_use);
}

void asio_https::begin(
						boost::asio::ip::tcp::resolver::query & query,
						boost::asio::ip::tcp::resolver & resolver,
                        unsigned int timeout
					  )
{
	// if using a self-signed certificate the only way to pass verification
	// is to "install" it locally and use it for comparison
	ctx_.load_verify_file("ca.pem"); // WARNING/BUG: what is this hardcoded???
	socket_->set_verify_mode(boost::asio::ssl::verify_peer | 
                             boost::asio::ssl::verify_fail_if_no_peer_cert);
	socket_->set_verify_callback(boost::bind(&asio_https::verify_certificate, 
                                             this, _1, _2));
	// resolve and connect
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    boost::asio::ip::tcp::resolver::iterator end;
    boost::system::error_code error = boost::asio::error::host_not_found;

	while (error && endpoint_iterator != end) {
        socket_->lowest_layer().close();
        deadline_->expires_from_now(boost::posix_time::seconds(timeout));
		boost::asio::async_connect(socket_->lowest_layer(), 
								   endpoint_iterator,
								   boost::bind(&asio_https::connect, 
                                               this, 
                                               boost::asio::placeholders::error));
	}
	if (error) {
        asio_handler::end(error);
	}
}

bool asio_https::verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx)
{
	char subject_name[256];
	X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
	X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
	return preverified;
}

void asio_https::connect(const boost::system::error_code err)
{
	if (err) {
		asio_handler::end(err);
		return;
	}
	socket_->async_handshake(boost::asio::ssl::stream_base::client,
							 boost::bind(&asio_https::handshake, 
                                         this, 
                                         boost::asio::placeholders::error));
}

void asio_https::handshake(const boost::system::error_code err)
{
	if (err) {
        asio_handler::end(err);
#if (!NDEBUG)
		std::cerr << "Handshake failed: " << err.message() << "\n";
#endif
		return;
	}
	boost::asio::async_write(*socket_,
							 request_,
							 boost::bind(&asio_handler::write_request, 
                                         this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void asio_https::shutdown(const boost::system::error_code err)
{
    socket_->lowest_layer().close();
    deadline_->cancel();
    deadline_.reset();
}

void asio_https::time_check()
{
    if (!deadline_) {
        return;
    }
    if (deadline_->expires_at() <= boost::asio::deadline_timer::traits_type::now()) {
        socket_->lowest_layer().close();
        deadline_->cancel();   
    }
    else {
        deadline_->async_wait(boost::bind(&asio_https::time_check, this));
    }
}

}
}
