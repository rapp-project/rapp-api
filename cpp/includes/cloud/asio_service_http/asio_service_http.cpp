#include "asio_service_http.hpp"

namespace rapp {
namespace cloud {

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
    else error_handler(err);
}

/// Callback for handling request and waiting for response \param err is a possible error
void asio_service_http::handle_write_request(const boost::system::error_code & err)
{
    assert(socket_);
    if (!err) {
        // Read the response status line - Callback handler is ::handle_read_status_line
        boost::asio::async_read_until(*socket_.get(),
                                      response_, 
                                      "\r\n",
                                      boost::bind(&asio_service_http::handle_read_status_line, 
                                                  this,
                                                  boost::asio::placeholders::error));
    }
    else 
        error_handler(err);
}

/// Callback for handling HTTP Header Response Data \param err is a possible error message
void asio_service_http::handle_read_status_line(const boost::system::error_code & err)
{
    assert(socket_);
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
    assert(socket_);
    if (!err) {
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
    assert(socket_);
    if (!err)
    {
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
        std::call_once(cflag_, 
        [&]{
            if (has_content_length(buffer)) {
                content_length(buffer, content_length_);
                std::string tmp = buffer;
                buffer = strip_header(tmp);
            }
            // TODO: throw for now, later we'll simply stderr a message
            else {
                throw std::runtime_error("no `Content-Length` in header response");
            }
        });
        // append buffer and count bytes
        if (!buffer.empty()) {
            json_ += buffer;
            bytes_transferred_ += buffer.size();
            if (bytes_transferred_ == content_length_){
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
}
}
