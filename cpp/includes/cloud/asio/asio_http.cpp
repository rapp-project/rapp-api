#include "asio_http.hpp"
namespace rapp {
namespace cloud {

asio_http::asio_http(
						std::function<void(std::string)> cloud_function,
						std::function<void(error_code error)> error_function,
						boost::asio::io_service & io_service,
						boost::asio::streambuf & request
					)
: asio_handler<http_socket>(cloud_function, 
                            error_function,
                            boost::bind(&asio_http::shutdown,
                                        this,
                                        boost::asio::placeholders::error)),  
  error_cb_(error_function)
{
    socket_ = std::make_shared<http_socket>(io_service);
	assert(cloud_function && error_function && socket_);
    asio_handler::set_socket(socket_);
}

void asio_http::begin( 
						boost::asio::ip::tcp::resolver::query & query,
						boost::asio::ip::tcp::resolver & resolver
					 )
{
     //asio_handler::start_timer(30);
     resolver.async_resolve(query,
                            boost::bind(&asio_http::resolve,
                                        this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::iterator));
}

void asio_http::resolve(
                           boost::system::error_code  err,
                           boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                        )
{
    if (!err) {
        auto endpoint = * endpoint_iterator;
        socket_->async_connect(endpoint,
                               boost::bind(&asio_http::connect, 
                                           this, 
                                           boost::asio::placeholders::error,
                                           ++endpoint_iterator));
    }
    else {
        error_cb_(err);
    }
}

void asio_http::connect(
                         const boost::system::error_code err,
                         boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                       )
{
	if (!err) {
        boost::asio::async_write(*socket_,
                                 request_,
                                 boost::bind(&asio_handler<http_socket>::do_request, 
                                             this,
                                             boost::asio::placeholders::error));

    }
    else if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator()) {
        socket_->close();
        auto endpoint = *endpoint_iterator;
        socket_->async_connect(endpoint,
                               boost::bind(&asio_http::connect, 
                                           this, 
                                           boost::asio::placeholders::error,
                                           ++endpoint_iterator));
    }
    else {
        error_cb_(err); 
    }
}

void asio_http::shutdown(const boost::system::error_code err)
{
    socket_->shutdown(boost::asio::ip::tcp::socket::shutdown_send);
    socket_->close();
}

}
}
