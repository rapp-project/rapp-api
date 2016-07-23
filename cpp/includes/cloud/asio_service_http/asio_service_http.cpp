#include "asio_service_http.hpp"

namespace rapp {
namespace cloud {

void asio_service_http::schedule( 
                                   boost::asio::ip::tcp::resolver::query & query,
                                   boost::asio::ip::tcp::resolver & resolver,
                                   boost::asio::io_service & io_service,
								   rapp::cloud::platform_info info
                                 )
{
	// calculate HTTP POST size
    auto content_length = post_.size() * sizeof(std::string::value_type);
	// create the HTTP header
    header_ = make_header(info, content_length);
    std::ostream request_stream(&request_);
	// append HTTP header and HTTP POST data
    request_stream << header_ << post_ << "\r\n";
    // init tiemeout timer
    if (!timer_) {
        timer_ = std::unique_ptr<boost::asio::deadline_timer>(
                                 new boost::asio::deadline_timer(io_service));
    }
    timer_->async_wait(boost::bind(&asio_service_http::check_timeout, this));
    // init socket
    if (!socket_) {
        socket_ = std::unique_ptr<boost::asio::ip::tcp::socket>(
                                  new boost::asio::ip::tcp::socket(io_service));
    }
	// resolve the address and chain the callbacks
    resolver.async_resolve(query,
                           boost::bind(&asio_service_http::handle_resolve,
                                       this,
                                       boost::asio::placeholders::error,
                                       boost::asio::placeholders::iterator));
}

void asio_service_http::handle_resolve( 
                                         const boost::system::error_code & err,
                                         boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                                       )
{
    assert(socket);
    if (!err){
        auto endpoint = * endpoint_iterator;
        socket_->async_connect(endpoint,
                               boost::bind(&asio_service_http::handle_connect,
                                           this,
                                           boost::asio::placeholders::error, 
                                           ++endpoint_iterator));
    }
    else 
        error_handler(err);
}

void asio_service_http::handle_connect(
                                        const boost::system::error_code & err,
                                        boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                                      )
{
    assert(socket_);
    if (!err) {
        timer_->expires_from_now(boost::posix_time::seconds(30));
        boost::asio::async_write(*socket_.get(),
                                 request_,
                                 boost::bind(&asio_service_http::handle_write_request, 
                                             this,
                                             boost::asio::placeholders::error));
    }
    else if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator()) {
        socket_->close();   
        auto endpoint = *endpoint_iterator;
        socket_->async_connect(endpoint,
                               boost::bind(&asio_service_http::handle_connect, 
                                           this,
                                           boost::asio::placeholders::error, 
                                           ++endpoint_iterator));
    }
    else { 
        error_handler(err);
    }
}

/// Callback for handling request and waiting for response \param err is a possible error
void asio_service_http::handle_write_request(const boost::system::error_code & err)
{
    assert(socket_ && timer_);
    if (!err) {
        timer_->expires_from_now(boost::posix_time::seconds(30));
        // Read the response status line - Callback handler is ::handle_read_status_line
        boost::asio::async_read_until(*socket_.get(),
                                      response_, 
                                      "\r\n",
                                      boost::bind(&asio_service_http::handle_read_status_line, 
                                                  this,
                                                  boost::asio::placeholders::error));
    }
    else {
        error_handler(err);
    }
}

/// Callback for handling HTTP Header Response Data \param err is a possible error message
void asio_service_http::handle_read_status_line(const boost::system::error_code & err)
{
    assert(socket_ && timer_);
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
        boost::asio::async_read_until(*socket_.get(),
                                      response_, 
                                      "\r\n\r\n",
                                      boost::bind(&asio_service_http::handle_read_headers, 
                                                  this,
                                                  boost::asio::placeholders::error));
    }
    else  {
        error_handler(err);
    }
}

/// Callback for Handling Headers \param err is a possible error message
void asio_service_http::handle_read_headers(const boost::system::error_code & err)
{
    assert(socket_ && timer_);
    if (!err) {
        timer_->expires_from_now(boost::posix_time::seconds(30));
        // Start reading Content data until EOF (see handle_read_content)
        boost::asio::async_read_until(*socket_.get(),
                                      response_,
                                      "\r\n\r\n",
                                      boost::bind(&asio_service_http::handle_read_content,
                                                  this,
                                                  boost::asio::placeholders::error,
                                                  boost::asio::placeholders::bytes_transferred));
    }
    else {
        error_handler(err);
    }
}

/// Callback for Handling Actual Data Contents \param err is a possible error message
void asio_service_http::handle_read_content(const boost::system::error_code & err, std::size_t bytes)
{
    assert(socket_ && timer_);
    if (!err) {
        timer_->expires_from_now(boost::posix_time::seconds(30));
        // Continue reading remaining data until EOF - It reccursively calls its self
        boost::asio::async_read(*socket_.get(),
                                response_,
                                boost::asio::transfer_at_least(1),
                                boost::bind(&asio_service_http::handle_read_content, 
                                            this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));

        // Parse HTTP Content.
        std::string buffer((std::istreambuf_iterator<char>(&response_)), 
                            std::istreambuf_iterator<char>());

        // extract content length once and strip header
        if (!flag_) {
            if (has_content_length(buffer)) {
                content_length(buffer, content_length_);
                std::string tmp = buffer;
                buffer = strip_header(tmp);
            }
            else {
                throw std::runtime_error("no `Content-Length` in header response");
            }
            flag_ = true;
        }

        // append buffer and count bytes
        if (!buffer.empty()) {
            json_ += buffer;
            bytes_transferred_ += buffer.size();
            if (bytes_transferred_ >= content_length_){
                assert(callback_);
                callback_(json_);
            }
        }
    }
    // some error
    else if (err != boost::asio::error::eof) {
        error_handler(err);
    }
    // Received end of file
    else if (err == boost::asio::error::eof) {
        if (bytes_transferred_ != content_length_){
            std::cerr << "connection dropped unexpectedly" << std::endl;
            return;
        }
    }
}

void asio_service_http::reset()
{
    assert(timer_ && socket_);
    header_.clear();
    post_.clear();
    json_.clear();
    content_length_ = 0;
    bytes_transferred_ = 0;
    flag_ = false;
    socket_->close();
    timer_->expires_at(boost::posix_time::pos_infin);
}

void asio_service_http::check_timeout()
{
    assert(timer_);
    if (timer_->expires_at() <= boost::asio::deadline_timer::traits_type::now()) {
        std::cerr << "connection time-out" << std::endl;
        reset();
    }
    // Put the actor back to sleep.
    timer_->async_wait(boost::bind(&asio_service_http::check_timeout, this));
}


}
}
