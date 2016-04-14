#ifndef RAPP_ASIO_SOCKET_HTTPS
#define RAPP_ASIO_SOCKET_HTTPS
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class asio_socket_https
 * \version 1
 * \date April 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 * \brief wrapper for SSL/TLS secure HTTP communication
 */
class asio_socket_https : public asio_socket, protected asio_helper
{
public:
	typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> boost_tls_socket;

	/**
     * \brief construct using:
     * \param token: authentication token
     * \param user: rapp.cloud username
	 */
	asio_socket_https(const std::string token)
  	: ctx_(boost::asio::ssl::context::tlsv12_client), token_(token)
	{}

	/**
	 * schedule this as a job for execution
	 * \param query defines the URL/URI
	 * \param resolver resolves the URL/URI address
     * \param io_service is the queue on which jobs are scheduled
	 */
	void schedule(
				  boost::asio::ip::tcp::resolver::query & query,
				  boost::asio::ip::tcp::resolver & resolver,
				  boost::asio::io_service & io_service
				 )
	{
		if (!tls_socket_) {
			tls_socket_ = std::unique_ptr<boost_tls_socket>(
										  new boost_tls_socket(io_service, ctx_));
		}
		// disable ssl v2 and ssl v3 (allow only tls)
		ctx_.set_options(boost::asio::ssl::context::default_workarounds
        				|boost::asio::ssl::context::no_sslv2
        				|boost::asio::ssl::context::no_sslv3
						|boost::asio::ssl::context::no_tlsv1
        				|boost::asio::ssl::context::single_dh_use);
		//ctx_.load_verify_file("ca.pem");
		// resolve iterator
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		assert(tls_socket_);
		// set TLS verify mode
    	tls_socket_->set_verify_mode(boost::asio::ssl::verify_peer);
    	tls_socket_->set_verify_callback(boost::bind(&asio_socket_https::verify_certificate, 
												  this, _1, _2));
		// begin connect
    	boost::asio::async_connect(tls_socket_->lowest_layer(), 
							   	   endpoint_iterator,
							   	   boost::bind(&asio_socket_https::handle_connect, 
										   	   this,
         								   	   boost::asio::placeholders::error));
	}

	/// \brief verify TLS certificate - WARNING: is this proper verification?
	bool verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx)
  	{
		/*
    	char subject_name[256];
    	X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    	X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
		*/
    	return preverified;
  	}

	/// \brief begin connect
	void handle_connect(const boost::system::error_code& error)
  	{
		assert(tls_socket_);
    	if (!error) {
      		tls_socket_->async_handshake(boost::asio::ssl::stream_base::client,
          							     boost::bind(&asio_socket_https::handle_handshake, 
												  	 this,
            									  	 boost::asio::placeholders::error));
		}
		else {
		  	std::cerr << "connect failed: " << error.message() << "\n";
		}
  	}

	/// \brief handle handshake
  	void handle_handshake(const boost::system::error_code& error)
  	{
		assert(tls_socket_);
   		if (!error) {
			// read stream = header + post body into request_
      		std::ostream request_stream(&request_);
			request_stream << header_ << post_ << "\r\n";

			// write to the socket
      		boost::asio::async_write(*tls_socket_,
          							 request_,
          							 boost::bind(&asio_socket_https::handle_write, 
											     this,
            									 boost::asio::placeholders::error,
            									 boost::asio::placeholders::bytes_transferred));
    	}
    	else {
      		std::cerr << "Handshake failed: " << error.message() << "\n";
    	}
  	}

	/// \brief handle socket write - TODO: see asio_service_http
	//							   - first read the status line
	//							   - verify that we got a 200 response
	//							   - then read the actual header untill the double return
  	void handle_write(const boost::system::error_code& error, size_t bytes_transferred)
  	{
		assert(tls_socket_);
		// read into response_
    	if (!error) {
      		boost::asio::async_read(*tls_socket_,
          							response_,
          							boost::bind(&asio_socket_https::handle_read,
												this,
            									boost::asio::placeholders::error,
            									boost::asio::placeholders::bytes_transferred));
    	}
    	else {
      		std::cerr << "Write failed: " << error.message() << "\n";
    	}
  	}

	/// \brief handle socket response - TODO: handle_read_status_line
  	void handle_read(const boost::system::error_code& error, size_t bytes_transferred)
  	{
    	if (!error) {
			std::string json((std::istreambuf_iterator<char>(&response_)), 
                              std::istreambuf_iterator<char>());


      		std::cout << "Reply: " << json << "\r\n";
    	}
    	else {
      		std::cout << "Read failed: " << error.message() << "\n";
    	}
  	}

	/// TODO: handle_read_headers

	/// TODO: handle_read_content

	///

private:
	/// Header that will be used
    std::string header_;
    /// Actual post Data
    std::string post_;
    /// Callback Handler - use with std::bind or boost variant
    std::function<void(std::string)> callback_;
	/// ssl socket stream
  	std::unique_ptr<boost_tls_socket> tls_socket_;
	/// tls context
	boost::asio::ssl::context ctx_;
	/// Request Container
    boost::asio::streambuf request_;
    /// Response Container
    boost::asio::streambuf response_;
	/// user authentication token
	const std::string token_;
};
}
}
#endif
