#include "asio_http.hpp"
namespace rapp {
namespace cloud {

asio_http::asio_http(
						std::function<void(std::string)> cloud_function,
						std::function<void(error_code error)> error_function,
						boost::asio::io_service & io_service,
						boost::asio::streambuf request
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
	 // resolve and connect
	 boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
     boost::asio::ip::tcp::resolver::iterator end;
	 boost::system::error_code error = boost::asio::error::host_not_found;

	 while (error && endpoint_iterator != end) {
		 socket_->close();
		 // start timeout countdown
         asio_handler::start_timer(30);
		 // try connecting
		 boost::asio::async_connect(*socket_, 
									endpoint_iterator,
									boost::bind(&asio_http::connect, 
                                                this, 
                                                boost::asio::placeholders::error));
	 }
	 if (error) {
		error_cb_(error);
		return;	 
	 }
}

void asio_http::connect(const boost::system::error_code err)
{
	if (err) {
		error_cb_(err); 
		return;
	}
	boost::asio::async_write(*socket_,
							 request_,
							 boost::bind(&asio_http::do_request, 
                                         this,
                                         boost::asio::placeholders::error));
}

void asio_http::shutdown(const boost::system::error_code err)
{
    socket_->shutdown(boost::asio::ip::tcp::socket::shutdown_send);
    socket_->close();
}

}
}
