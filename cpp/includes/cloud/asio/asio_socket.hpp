#ifndef RAPP_ASIO_SOCKET_
#define RAPP_ASIO_SOCKET_
#include "includes.ihh"
#include "response.hpp"
namespace rapp {
namespace cloud {

/**
 * \brief enum for error reporting
 * \version TODO
 */
enum
{
	errors_warn = 0,
	errors_ignore = 1
};


typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> tls_socket;
typedef boost::system::error_code error_code;
typedef boost::asio::ip::tcp::resolver resolver;

/**
 * \Template class asio_socket
 * \version 0.7.0
 * \date August 2016 
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 * \brief class for the implementation of the communication protocol
 */
template <class T>
class asio_socket : public rapp::cloud::response 
{
public:

    /// \brief construct by passing an error callback 
    /// \param callback will receive errors
    asio_socket(
                std::function<void(error_code)> error_cb,
                std::shared_ptr<T> 
               );
    
     /// \brief it's the first step to start communication
    void write_request(error_code err);
    
    ///\brief method to check the status of the message 
    void read_status_line(error_code err);
    
    ///\brief get the headers and check them
    void read_headers(error_code err);

    /// \brief strip the header and read the data
    void read_content(error_code err);

    /// \brief close socket and cleanup members
    void end(error_code err);

    /// \brief receives timeout
    void has_timed_out() const;

private:
    /// our socket T pointer
    std::shared_ptr<T> socket_;
    /// error handler callback
    std::function<void(error_code)> error_cb_;
    /// json_callback
    std::function<void(std::string)> json_cb_;
    /// timer - asio_http and asio_https can't access timer
    rapp::cloud::timer timer_;
    /// newline
    const std::string rn_ = "\r\n";
    ///two new lines
    const std::string double_rn_ = "\r\n\r\n";
};


/// asio_socket implementation
///
template <class T> 
asio_socket<T>::asio_socket(
                            std::function<void(error_code)> error_cb,
                            std::unique_ptr<T> socket  
                          )
: user_callback_(error_cb), socket_(socket)
{
    timer_ = rapp::cloud::timer(boost::bind(&asio_socket<T>::has_timed_out, this)); 
	assert(timer_ && socket_);
}

template <class T> 
void asio_socket<T>::write_request(error_code err)
{       
    if (!err) {
        end(err);       
		return;
	}
	// read until first newline (HTTP 1.1\r\n)
	boost::asio::async_read_until(*socket_,
								  buffer_,
								  rn_,
								  boost::bind(&asio_socket<T>::read_status_line,
											  this,
											  boost::asio::placeholders::error));
}

template <class T>
void asio_socket<T>::read_status_line(error_code err)
{
    if (err & !check_http_header()) {
        end(err);
		return;
	}
	// read entire header (double newlines denote end of HTTP header)
	boost::asio::async_read_until(*socket_,
								  buffer_, 
								  double_rn_,
								  boost::bind(&asio_socket<T>::read_headers, 
											  this,
											  boost::asio::placeholders::error));
}

template <class T>
void asio_socket<T>::read_headers(error_code err)
{
    if (err) {
        end(err);
		return;
	}
 	unsigned int c_len = has_content_length();	
	if (c_len > 0) {
		// remove HTTP header and keep only POST data
		response::json_ = strip_http_header(to_string());
		// read as much as the Content-Length
		boost::asio::async_read(*socket_,
								buffer_,
								boost::asio::transfer_at_least(c_len),
								boost::bind(&asio_socket<T>::read_content,
											this,
											boost::asio::placeholders::error,
											boost::asio::placeholders::bytes_transferred));
	}
	else {
		end(boost::system::errc::bad_message);
	}
}

template <class T>
void asio_socket<T>::read_content(error_code err)
{
    if (err) {
        end(err);
		return;
	}
	// consume buffer - if transferred bytes >= Content-Length then = EOF && end 
	if (response::consume_buffer(json_cb_)) {
		end(boost::system:errc::success);
	}
	// Continue reading remaining data until EOF - It reccursively calls its self
	boost::asio::async_read(*socket_,
							buffer_,
							boost::asio::transfer_at_least(1),
							boost::bind(&asio_socket<T>::read_content, 
										this,
										boost::asio::placeholders::error,
										boost::asio::placeholders::bytes_transferred));
}

template<class T>
void asio_socket<T>::has_timed_out() const
{
   if (timer->check_timeout()){
       end(boost::asio::error::timed_out);
   }
}

template <class T>
void asio_socket<T>::end(error_code err)
{
    if (err) {
        error_cb_(err);
    }
    response::end();
    socket_->shutdown(boost::asio::ip::tcp::socket::shutdown_send, err);
    timer_->reset();
}
 
}
}
#endif
