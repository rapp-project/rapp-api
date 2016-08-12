#include "asio_http.hpp"
namespace rapp {
namespace cloud {

asio_http::asio_http(
						std::function<void(std::string)> cloud_function,
						std::function<void(error_code error)> error_function,
						boost::asio::io_service & io_service,
						boost::asio::streambuf request
					)
: error_cb_(error_function)
{
	assert(cloud_function && error_function);
	socket_ = std::make_shared<http_socket>(io_service);
	assert(socket_);
	handler_ = asio_socket<http_socket>(cloud_function, error_function, socket_);
}

void asio_http::begin( 
						boost::asio::ip::tcp::resolver::query & query,
						boost::asio::ip::tcp::resolver & resolver
					 )
{
	 // resolve and connect
	 boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	 boost::system::error_code error = boost::asio::error::host_not_found;

	 while (error && endpoint_iterator != end) {
		 socket_->close();
		 // start timeout countdown
		 handler_->start_timer(30);
		 // try connecting
		 boost::asio::async_connect(*socket_, 
									endpoint_iterator,
									boost::bind(&asio_http::connect, this, place_error));
	 }
	 if (error) {
		error_cb_(error);
		return;	 
	 }
}

void asio_http::connect(boost::system::errc err)
{
	if (err) {
		error_cb_(err); 
		return;
	}
	boost::asio::async_write(*socket_,
							 request_,
							 boost::bind(&asio_socket<http_socket>::do_request, this->handler_, place_error));
}

}
}
