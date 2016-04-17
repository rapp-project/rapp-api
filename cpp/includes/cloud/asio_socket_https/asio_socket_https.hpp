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
	{
        // MOVE all header manipulation here in base class
        header_ =  "POST / HTTP/1.1\r\n";
        header_ += "Host: "+std::string(rapp::cloud::address)+"\r\n";
        header_ += "Accept-Token: "+token+"\r\n";
        header_ += "Connection: close\r\n";

        // TODO inheriting classes must set either Content-Length, or Chunked.
        auto size = post_.size() * sizeof(std::string::value_type);
        header_ += "Content-Length: "+boost::lexical_cast<std::string>(size)+"\r\n";

        // TODO: inheriting classes must set either 'application/json'
        //       or multipart/form-data 
        header_ += "Content-Type: application/json\r\n";
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

        // if using a self-signed certificate the only way to pass verification
        // is to "install" it locally and use it for comparison
        ctx_.load_verify_file("ca.pem");

		// resolve iterator
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		assert(tls_socket_);

		// set TLS verify mode
    	tls_socket_->set_verify_mode(boost::asio::ssl::verify_peer 
                                    |boost::asio::ssl::verify_fail_if_no_peer_cert);
        // verify callback
    	tls_socket_->set_verify_callback(boost::bind(&asio_socket_https::verify_certificate, 
												  this, _1, _2));
		// begin connect
    	boost::asio::async_connect(tls_socket_->lowest_layer(), 
							   	   endpoint_iterator,
							   	   boost::bind(&asio_socket_https::handle_connect, 
										   	   this,
         								   	   boost::asio::placeholders::error));
	}

protected:

    void error_handler(const boost::system::error_code & error)
    {
        std::cerr << "asio_service_http error: " << error.message() << std::endl;
    }

    /// Handle Invalid Query - e.g.: response which states our query was invalid 
    void invalid_request(const std::string message)
    {
        std::cerr << "asio_service_http invalid request: " <<  message << std::endl;
    }

	/// \brief verify TLS certificate - WARNING: is this proper verification?
	bool verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx)
  	{
    	char subject_name[256];
    	X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    	X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
        /*
        std::cout << "Verifying: " << subject_name << "\n"
                     "Verified: " << preverified << std::endl;
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
            									 boost::asio::placeholders::error));
    	}
    	else {
      		std::cerr << "Handshake failed: " << error.message() << "\n";
    	}
  	}

    /// Callback for handling request and waiting for response \param err is a possible error
    void handle_write(const boost::system::error_code & err)
    {
        assert(tls_socket_);
        if (!err) {
            // Read the response status line - Callback handler is ::handle_read_status_line
            boost::asio::async_read_until(*tls_socket_,
                                          response_, 
                                          "\r\n",
                                          boost::bind(&asio_socket_https::handle_read_status_line, 
                                                      this,
                                                      boost::asio::placeholders::error));
        }
        else 
            error_handler(err);
    }
    
    /// Callback for handling HTTP Header Response Data \param err is a possible error message
    void handle_read_status_line(const boost::system::error_code & err)
    {
        assert(tls_socket_);
        if (!err) {
            // Check that HTTP Header Response is OK.
            std::istream response_stream(&response_);
            std::string http_version;
            response_stream >> http_version;
            unsigned int status_code;
            response_stream >> status_code;
            std::string status_message;
            std::getline( response_stream, status_message );
            if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
                invalid_request("http Invalid response");
                return;
            }
            if (status_code != 200) {
                invalid_request(std::to_string(status_code));
                return;
            }
            // Read the response headers, which are terminated by a blank line. 
			// This is HTTP Protocol 1.0 & 1.1
            boost::asio::async_read_until(*tls_socket_,
                                          response_, 
                                          "\r\n\r\n",
                                          boost::bind(&asio_socket_https::handle_read_headers, 
                                                      this,
                                                      boost::asio::placeholders::error));
        }
        else 
            error_handler(err);
    }

    /// Callback for Handling Headers \param err is a possible error message
    void handle_read_headers(const boost::system::error_code & err)
    {
        assert(tls_socket_);
        if (!err) {
            // Start reading Content data until EOF (see handle_read_content)
            boost::asio::async_read_until(*tls_socket_,
                                          response_,
                                          "\r\n\r\n",
                                          boost::bind(&asio_socket_https::handle_read_content,
                                                      this,
                                                      boost::asio::placeholders::error));
        }
        else {
			error_handler(err);
		}
    }
    
    /// Callback for Handling Actual Data Contents \param err is a possible error message
    void handle_read_content(const boost::system::error_code & err)
    {
        assert(socket_);
        if (!err) {
            // Continue reading remaining data until EOF - It reccursively calls its self
            boost::asio::async_read(*tls_socket_,
                                    response_,
                                    boost::asio::transfer_at_least(1),
                                    boost::bind(&asio_socket_https::handle_read_content, 
                                                this,
                                                boost::asio::placeholders::error ) );

            // Parse HTTP Content.
            std::string json((std::istreambuf_iterator<char>(&response_)), 
                              std::istreambuf_iterator<char>());

            /*
            // find the "\r\n\r\n" double return
            std::size_t i = json.find("\r\n\r\n");
            if (i != std::string::npos) {
                json = json.substr(i+4, std::string::npos);
            }
            else {
                std::cerr << "no double return carriage after header" << std::endl;
                return;
            }
            // Now call the callback
            assert(callback_);
            callback_(json);
            */
            std::cout << json << std::endl;
        }
        else if (err != boost::asio::error::eof) {
            error_handler(err);
		}
    }

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
