#include "asio_http.hpp"
namespace rapp {
namespace cloud {

asio_http::asio_http(
						std::function<void(std::string)> cloud_function,
						std::function<void(error_code error)> error_function,
						boost::asio::io_service & io_service,
						boost::asio::streambuf & request
					)
: asio_handler<http_socket>(
                            cloud_function, 
                            error_function,
                            boost::bind(&asio_http::shutdown,
                                        this,
                                        boost::asio::placeholders::error)
                           ),
  error_cb_(error_function),
  request_(request)
{
    socket_ = std::make_shared<http_socket>(io_service);
    deadline_ = std::make_shared<boost::asio::deadline_timer>(io_service);
	assert(cloud_function && error_function && socket_ && deadline_);
    asio_handler::set_socket(socket_);
    // PROBLEM: the async_wait callback will be bound to *this* 
    //          so even when the class has finished, we still have a queued
    //          operation in the io_service waiting for time_check
    deadline_->async_wait(boost::bind(&asio_http::time_check, this)); 
}

void asio_http::begin( 
						boost::asio::ip::tcp::resolver::query & query,
						boost::asio::ip::tcp::resolver & resolver,
                        unsigned int timeout
					 )
{
    deadline_->expires_from_now(boost::posix_time::seconds(timeout));
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
        shutdown(err);
    }
}

void asio_http::connect(
                         const boost::system::error_code err,
                         boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                       )
{
	if (!err) {
        // write the request to the socket
        boost::asio::async_write(*socket_.get(),
                                 request_,
                                 boost::bind(&asio_handler<http_socket>::write_request, 
                                             this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));

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
        shutdown(err);
    }
}

void asio_http::shutdown(const boost::system::error_code err)
{
    socket_->close();
    deadline_->cancel();
    deadline_.reset(); 
}

void asio_http::time_check()
{
    if (!deadline_) {
        return;
    }
    if (deadline_->expires_at() <= boost::asio::deadline_timer::traits_type::now()) {
        socket_->close();
        deadline_->cancel();
    }
    else {
        deadline_->async_wait(boost::bind(&asio_http::time_check, this));
    }
}

}
}
