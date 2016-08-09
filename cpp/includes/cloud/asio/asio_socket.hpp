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

typedef boost::asio::ip::tcp::socket http_socket;
typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> tls_socket;
typedef boost::system::error_code error_code;

/**
 */
template <class T>
class asio_socket : public response 
{
public:

    /// \brief construct by passing an error callback 
    /// \param callback will receive errors
    asio_socket(
                std::function<void(error_code error)> callback,
                std::unique_ptr<T> socket  
               )
    : user_callback_(callback), socket_(socket)
    {
        timer_ = rapp::cloud::timer(boost::bind(&asio_socket::has_timed_out, this)); 
        // do NOT setup the socket here - it will be done by inheriting classes
    }


protected:
    /// our socket T pointer
    std::unique_ptr<T> socket_;
    
    /// JSON reply from platform
    std::string json_;
    
    /// amount of bytes received
    unsigned int bytes_transfered_;

    /// still reading data into streambuf
    std::atomic<bool> read_flag_;
    
    /// the user-defined error handling callback
    std::function<void(boost::system::error_code)> handle_callback;

private:

  //  void has_timed_out()
  //  {
  //      boost::system::error_code ec = boost::asio::error::timed_out;
  //      user_callback_(ec);

        // TODO: call "reset" or "stop"
  //  }

    
    /// time-out handler
 //   rapp::cloud::timer timer_;
    /// user's error callback
 //   std::function<void(error_code)> user_callback_;
 
    /// \brief
    void handle_write_request(error_code err)
    {
        rapp::cloud::timer timer = rapp::cloud::timer(handle_callback); // is it fine???
        assert(socket_);
        if (!err) {
            timer.set_timeout(10);
            
            //Read the response status line
            boost::asio::async_read_until(*socket_.get(),
                                          response_,
                                          "\r\n",
                                          boost::bind(&asio_socket::handle_read_status_line,
                                                      this,
                                                      boost::asio::placeholders::error));
        }
        else {
           handle_callback(err);
           socket_->shutdown(boost::asio::ip::tcp::socket::shutdown_send, err);
	 
        }


    }

    ///\brief
    void handle_read_status_line()
    {
        assert(socket_);
        if (!err){
            std::string http_version;
            rapp::cloud::response(http_version);
        }

    }

    ///\brief
    void handle_read_headers()
    {

    }

    /// \brief
    void handle_read_content()
    {

    }


};

}
}
#endif
