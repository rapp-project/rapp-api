#ifndef RAPP_ASIO_SERVICE_HTTP
#define RAPP_ASIO_SERVICE_HTTP
#include "includes.ihh"
#include "asio_socket.hpp"
namespace rapp {
namespace cloud {

typedef boost::system::error_code error_code;
typedef boost::asio::ip::tcp::resolver resolver;   
typedef boost::asio::ip::tcp::socket http_socket;
/**
 * \class asio_http
 * \brief base class for asynchronous http websockets used for connecting to cloud services
 * \version 0.7.0
 * \date August 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class asio_http 
{
public:

    asio_http(
                std::function<void(error_code error)> callback,
                boost::asio::io_service & io_service,
                boost::asio::streambuf request
            )
    : error_cb_(callback)
    {
        socket_  = std::make_shared<http_socket>(io_service);
        handler_ = asio_socket<http_socket>(std::bind(&asio_http<http_socket>::connect, this, std::placeholders::_1),
                                           callback, 
                                           socket_);
    }

    /** 
     * schedule this client as a job for execution using
     * \param query defines the actual URL/URI
     * \param resolver is the URL/URI resolver reference
     * \param io_service is the queue on which jobs are scheduled
     */
    void begin( 
                resolver::query & query,
                resolver & resolver
              )
    {
        //start the communication
        handler_->start(query, resolver);
    }
    
    /**
     * \brief connection handler
     * \param err is a possible error
     * \param endpoint_iterator is boosts' hostname address handler
     */
     void connect(boost::system::errc err)
     {
        assert(asio_socket::socket_);
        if (!err) {
    		// write the request (see each class for what that request is)
            boost::asio::async_write(*socket_,
                                     request_,
                                     boost::bind(&asio_socket<http_socket>::write_request, 
                                                 this->handler_,
                                                 boost::asio::placeholders::err));
        }
        else {
	       error_cb_(err); 
        }   
     };

private:
     /// error callback
     std::function<void(boost::system::errc)> error_cb_;
     /// socket ptr
     std::shared_ptr<http_socket> socket_;
     /// socket handler
     rapp::cloud::asio_socket<http_socket> handler_;
     /// buffer filled with request
     boost::asio::streambuf request_;

};
}
}
#endif
