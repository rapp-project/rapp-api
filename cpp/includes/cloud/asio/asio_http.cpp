#include "asio_http.hpp"

namespace rapp {
namespace cloud {

// TODO: remove error_handler, and accept as parameter
//		 then set it to a local member

void asio_http::schedule(
                            resolver::query & query,
                            resolver & resolver,
                            boost::asio::io_service & io_service,
						    rapp::cloud::platform_info info
                        )
{
	// craft the header and fill the request buffer
	// altering the (boost::asio::streambuf) - member asio::handler::request_
	asio_handler::make_request_buffer(info, header, post);
	
	// TODO: move timer (and io_timer_) into a seperate struct/class
    // init timeout timer
    if (!timer_) {
        timer_ = std::make_unique<boost::asio::deadline_timer>(io_timer_);
    }
    timer_->async_wait(boost::bind(&asio_http::check_timeout, this));

    // init socket
    if (!socket_) {
        socket_ = std::make_unique<boost::asio::ip::tcp::socket>(io_service);
    }

	// resolve the address and chain the callbacks
    resolver.async_resolve(query,
                           boost::bind(&asio_http::handle_resolve,
                                       this,
                                       boost::asio::placeholders::error,
                                       boost::asio::placeholders::iterator));
}


void asio_http::handle_connect(
                                        boost::system::error_code err,
                                        boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                                      )
{
    assert(socket_);
    if (!err) {
		// set timeout now
        set_timeout(10);

		// write the request (see each class for what that request is)
        boost::asio::async_write(*socket_.get(),
                                 request_,
                                 boost::bind(&asio_http::handle_write_request, 
                                             this,
                                             boost::asio::placeholders::error));
    }
	// do we need this ? we won't be connecting to another endpoint, will we?
    else if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator()) {
        socket_->close();   
        auto endpoint = *endpoint_iterator;
        socket_->async_connect(endpoint,
                               boost::bind(&asio_http::handle_connect, 
                                           this,
                                           boost::asio::placeholders::error, 
                                           ++endpoint_iterator));
    }
    else {
        error_handler(err);
		socket_->shutdown(boost::asio::ip::tcp::socket::shutdown_send, err);
	}
}


}
}
