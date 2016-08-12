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
        handler_ = asio_socket<http_socket>(callback, socket_);
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
         // resolve and connect
		 boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		 boost::system::error_code error = boost::asio::error::host_not_found;
		 while (error && endpoint_iterator != end) {
			 socket_->close();
			 boost::asio::async_connect(*socket_, 
									    endpoint_iterator,
									    boost::bind(&asio_http::connect, 
												    this,
												    boost::asio::placeholders::error));
		 }
		 if (error) {
		 	 error_cb_(error); 	
		 }
    }
    
    /**
     * \brief connection handler
     * \param err is a possible error
     * \param endpoint_iterator is boosts' hostname address handler
     */
     void connect(boost::system::errc err)
     {
        if (err) {
			error_cb_(err); 
			return;
		}
		boost::asio::async_write(*socket_,
								 request_,
								 boost::bind(&asio_socket<http_socket>::write_request, 
											 this->handler_,
											 boost::asio::placeholders::err));
     }

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
