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
 * \      it could be used with http or https 
 * 
 * The possible errors range but a few specific ones are:
 *      - boost::asio::error::eof implies the connection was dropped/aborted by the platform
 *      - 
 * Other errors received are inherited from \class rapp::cloud::response
 *
 * TODO - change name of class from asio_socket, to asio_handler
 */
template <class T>
class asio_socket : public rapp::cloud::response 
{
public:

    /// \brief construct by passing an error callback 
    /// \param callback will receive errors
    asio_socket(
                std::function<void(error_code)> connect_cb
                std::function<void(error_code)> error_cb,
                std::shared_ptr<T> 
               );
    
private:
 
    ///\brief resolve the address and chain the callbacks
    void start( 
               resolver::query & query,
               resolver & resolver
              );
 
    ///brief connect the endpoint 
    void resolve (
                   error_code  err,
                   resolver::iterator endpoint_iterator
                 );

    /// \brief it's the first step to start communication
    void write_request(error_code err);
    
    ///\brief method to check the status of the message 
    void read_status_line(error_code err);
    
    ///\brief get the headers and check them
    void read_headers(error_code err);

    /// \brief strip the header and read the data
    void read_content(error_code err);

    /// \brief clean the variables and shutdown the socket
    void reset(error_code err);

    /// \brief receives timeout
    void has_timed_out() const;
 

    /// our socket T pointer
    std::shared_ptr<T> socket_;
    /// inheriting classes must set this connector properly
    std::function<void(error_code)> connect_cb_;
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
                            std::function<void(error_code, resolver::iterator)> connect_cb_
                            std::function<void(error_code)> error_cb,
                            std::unique_ptr<T> socket  
                          )
: connect_cb_(connect_cb), user_callback_(error_cb), socket_(socket)
{
    timer_ = rapp::cloud::timer(boost::bind(&asio_socket<T>::has_timed_out, this)); 
}

///
template<class T>
void asio_socket<T>::start( 
                            resolver::query & query,
                            resolver & resolver
                          )
{
    timer_->set_timeout(30);
    resolver.async_resolve(query,
                           boost::bind(&asio_socket<T>::resolve,
                                       this,
                                       boost::asio::placeholders::error,
                                       boost::asio::placeholders::iterator));
}

///
template <class T>
void asio_socket<T>::resolve( 
                             error_code  err,
                             resolver::iterator endpoint_iterator
                            )
{
    assert(socket);
    if (!err){
        auto endpoint = * endpoint_iterator;
        socket_->async_connect(endpoint,
                               boost::bind(&this->connect_cb_, 
                                           this,
                                           boost::asio::placeholders::error));
    }
    else {
        reset(err);
    }
}

template <class T> 
void asio_socket<T>::write_request(error_code err)
{       
    
    assert(socket_ && timer_);
    if (!err) {
        boost::asio::async_read_until(*socket_,
                                      buffer_,
                                      rn_,
                                      boost::bind(&asio_socket<T>::read_status_line,
                                                  this,
                                                  boost::asio::placeholders::error));
    }
    else {
        reset(err);       
    }
}

template <class T>
void asio_socket<T>::read_status_line(error_code err)
{
    assert(socket_ && timer_);
    if (!err & check_http_header() == true) {
        // Read the response headers, which are terminated by a blank line. 
        // This is HTTP Protocol 1.0 & 1.1
        boost::asio::async_read_until(*socket_,
                                      buffer_, 
                                      double_rn_,
                                      boost::bind(&asio_socket<T>::read_headers, 
                                                  this,
                                                  boost::asio::placeholders::error));
    }
    else {
        reset(err);
	}
}

template <class T>
void asio_socket<T>::read_headers(error_code err)
{
    assert(socket_ && timer_);
    if (!err) {
        // Start reading Content data until EOF (see handle_read_content)
        boost::asio::async_read_until(*socket_,
                                      buffer_,
                                      double_rn_,
                                      boost::bind(&asio_socket<T>::read_content,
                                                  this,
                                                  boost::asio::placeholders::error,
                                                  boost::asio::placeholders::bytes_transferred));
    }
    else {
        reset(err);
	}
}

template <class T>
void asio_socket<T>::read_content(error_code err)
{
    assert(socket_ && timer_);
    if (!err) {
        // Continue reading remaining data until EOF - It reccursively calls its self
        boost::asio::async_read(*socket_,
                                buffer_,
                                boost::asio::transfer_at_least(1),
                                boost::bind(&asio_socket<T>::read_content, 
                                            this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
        // keep consuming data - if EOF - reset 
        if (response::take_data(json_cb_)) {
            reset(boost::system:errc::success);
        }
    }
    else {
		reset(err);
	}
}

template<class T>
void asio_socket<T>::has_timed_out() const
{
   if (timer->check_timeout()){
       reset(boost::asio::error::timed_out);
   }
}

template <class T>
void asio_socket<T>::reset(error_code err)
{
    if (err) {
        error_cb_(err);
    }
    response::reset();
    socket_->shutdown(boost::asio::ip::tcp::socket::shutdown_send, err);
    timer_->reset();
}
 
}
}
#endif
