#ifndef RAPP_ASIO_HANDLER
#define RAPP_ASIO_HANDLER
/**
 * Copyright 2015 RAPP
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * #http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "includes.ihh"
#include "http_response.hpp"
#include "asio_timer.hpp"

typedef boost::asio::ip::tcp::socket http_socket;
typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> tls_socket;
typedef boost::system::error_code error_code;
typedef boost::asio::ip::tcp::resolver resolver;

namespace rapp {
namespace cloud {
/**
 * \class asio_handler
 * \version 0.7.0
 * \date 12 August 2016 
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 * \brief ASIO socket controller of boost asio socket type T
 * \note This class is used internally from `asio_http` and `asio_https`.
 * \see asio_http
 * \see asio_https
 * \see http_response
 */
template <class T> class asio_handler : protected http_response 
{
public:
	/**
     * \brief construct by callbacks and socket T pointer 
     * \param cloud_function will receive the platform JSON reply
	 * \param error_function will receive any asio errors
	 * \param socket is the actual type T socket pointer
	 */
    asio_handler(
                  const std::function<void(std::string)> cloud_function,
                  const std::function<void(const boost::system::error_code)> error_function,
                  const std::function<void(const boost::system::error_code)> shutdown_function
                );

    /// \brief set socket pointer
    void set_socket(const std::shared_ptr<T> socket);

	/// \brief start the timer
	/// \param seconds will countdown and then invoke `has_timed_out`
	void start_timer(unsigned int seconds);
    
    /// \brief write the cloud request to the socket
	/// \param err is propagated from boost asio
    void do_request(const boost::system::error_code & err);
    
    /// \brief read first HTTP line and check for a 200 response
	/// \param err is propagated from boost asio
    void read_status_line(const boost::system::error_code & err);
    
    /// \brief read HTTP headers and validate
	/// \param err is propagated from boost asio
    void read_headers(const boost::system::error_code & err);

    /// \brief strip the header and read the POST data
	/// \param err is propagated from boost asio
    void read_content(
                      const boost::system::error_code & err,
                      const std::size_t bytes
                     );

    /// \brief close socket and cleanup members
	/// \param err is propagated from boost asio
    void end(const boost::system::error_code & err);

    /// \brief socket operation timed out
    void has_timed_out();

protected:
    /// our socket T pointer
    std::shared_ptr<T> socket_;
        /// json_callback
    std::function<void(std::string)> cloud_cb_;
    /// error handler callback
    std::function<void(const boost::system::error_code)> error_cb_;
    /// shutdown callback
    std::function<void(const boost::system::error_code)> close_cb_;

    /// timer - asio_http and asio_https can't access timer
    rapp::cloud::asio_timer timer_;
    /// newline
    const std::string rn_ = "\r\n";
    ///two new lines
    const std::string double_rn_ = "\r\n\r\n";
};
}
}
#include "asio_handler.impl"
#endif
