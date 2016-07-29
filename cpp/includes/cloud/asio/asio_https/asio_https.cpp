#include "asio_https.hpp"

namespace rapp {
namespace cloud {

void asio_https::schedule(
                            boost::asio::ip::tcp::resolver::query & query,
                            boost::asio::ip::tcp::resolver & resolver,
                            boost::asio::io_service & io_service,
						    rapp::cloud::platform_info info
                          )
{
	// calculate HTTP POST size
    auto content_length = post_.size() * sizeof(std::string::value_type);
	// append the HTTP header to the previous craft (POST and content type)
	header_= make_header(info, head_preamble_, content_length);

    // init timeout timer
	// TODO: add unique per-class timeout service
    if (!timer_) {
        timer_ = std::make_unique<boost::asio::deadline_timer>(io_service);
    }
    timer_->async_wait(boost::bind(&asio_https::check_timeout, this));

    // init tls socket wrapper
    if (!tls_socket_) {
        tls_socket_ = std::make_unique<boost_tls_socket>(io_service, ctx_);
    }
    assert(tls_socket_);

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
    // set TLS verify mode
    tls_socket_->set_verify_mode(boost::asio::ssl::verify_peer 
                                |boost::asio::ssl::verify_fail_if_no_peer_cert);
    // verify callback
    tls_socket_->set_verify_callback(boost::bind(&asio_https::verify_certificate, 
                                              this, _1, _2));
    // begin connect
    boost::asio::async_connect(tls_socket_->lowest_layer(), 
                               endpoint_iterator,
                               boost::bind(&asio_https::handle_connect, 
                                           this,
                                           boost::asio::placeholders::error));
}

/// \brief verify TLS certificate - WARNING: is this proper verification?
bool asio_https::verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx)
{
    char subject_name[256];
    X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
    return preverified;
}

/// \brief begin connect
void asio_https::handle_connect(const boost::system::error_code& error)
{
    assert(tls_socket_);
    if (!error) {
        timer_->expires_from_now(boost::posix_time::seconds(30));
        tls_socket_->async_handshake(boost::asio::ssl::stream_base::client,
                                     boost::bind(&asio_https::handle_handshake, 
                                                 this,
                                                 boost::asio::placeholders::error));
    }
    else {
        std::cerr << "connect failed: " << error.message() << "\n";
    }
}

/// \brief handle handshake
void asio_https::handle_handshake(const boost::system::error_code& error)
{
    assert(tls_socket_ && timer_);
    if (!error) {
        // read stream = header + post body into request_
        std::ostream request_stream(&request_);
        request_stream << header_ << post_ << "\r\n";
        timer_->expires_from_now(boost::posix_time::seconds(30));
        // write to the socket
        boost::asio::async_write(*tls_socket_,
                                 request_,
                                 boost::bind(&asio_https::handle_write, 
                                             this,
                                             boost::asio::placeholders::error));
    }
    else {
        std::cerr << "Handshake failed: " << error.message() << "\n";
    }
}

/// Callback for handling request and waiting for response \param err is a possible error
void asio_https::handle_write(const boost::system::error_code & err)
{
    assert(tls_socket_ && timer_);
    if (!err) {
        timer_->expires_from_now(boost::posix_time::seconds(30));
        // Read the response status line - Callback handler is ::handle_read_status_line
        boost::asio::async_read_until(*tls_socket_,
                                      response_, 
                                      "\r\n",
                                      boost::bind(&asio_https::handle_read_status_line, 
                                                  this,
                                                  boost::asio::placeholders::error));
    }
    else {
        error_handler(err);
    }
}

/// Callback for handling HTTP Header Response Data \param err is a possible error message
void asio_https::handle_read_status_line(const boost::system::error_code & err)
{
    assert(tls_socket_ && timer_);
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
        timer_->expires_from_now(boost::posix_time::seconds(30));
        // Read the response headers, which are terminated by a blank line. 
        // This is HTTP Protocol 1.0 & 1.1
        boost::asio::async_read_until(*tls_socket_,
                                      response_, 
                                      "\r\n\r\n",
                                      boost::bind(&asio_https::handle_read_headers, 
                                                  this,
                                                  boost::asio::placeholders::error));
    }
    else {
        error_handler(err);
    }
}

/// Callback for Handling Headers \param err is a possible error message
void asio_https::handle_read_headers(const boost::system::error_code & err)
{
    assert(tls_socket_ && timer_);
    if (!err) {
        timer_->expires_from_now(boost::posix_time::seconds(30));
        // Start reading Content data until EOF (see handle_read_content)
        boost::asio::async_read_until(*tls_socket_,
                                      response_,
                                      "\r\n\r\n",
                                      boost::bind(&asio_https::handle_read_content,
                                                  this,
                                                  boost::asio::placeholders::error));
    }
    else {
        error_handler(err);
    }
}

/// Callback for Handling Actual Data Contents \param err is a possible error message
void asio_https::handle_read_content(const boost::system::error_code & err)
{
    assert(tls_socket_ && timer_);
    if (!err) {
        timer_->expires_from_now(boost::posix_time::seconds(30));
        // Continue reading remaining data until EOF - It reccursively calls its self
        boost::asio::async_read(*tls_socket_,
                                response_,
                                boost::asio::transfer_at_least(1),
                                boost::bind(&asio_https::handle_read_content, 
                                            this,
                                            boost::asio::placeholders::error));

        // Parse HTTP Content.
        std::string json((std::istreambuf_iterator<char>(&response_)), 
                          std::istreambuf_iterator<char>());

        // TODO: see asio_service_http
    }
    else if (err != boost::asio::error::eof) {
        error_handler(err);
    }
}

void asio_https::reset()
{
    assert(timer_ && tls_socket_);
    header_.clear();
    post_.clear();
    json_.clear();
    content_length_ = 0;
    bytes_transferred_ = 0;
    flag_ = false;
    tls_socket_->lowest_layer().close();
    timer_->expires_at(boost::posix_time::pos_infin);
}

void asio_https::check_timeout()
{
    assert(timer_);
    if (timer_->expires_at() <= boost::asio::deadline_timer::traits_type::now()) {
        std::cerr << "connection time-out" << std::endl;
        reset();
    }
    // Put the actor back to sleep.
    timer_->async_wait(boost::bind(&asio_https::check_timeout, this));
}


}
}
