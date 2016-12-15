#ifndef RAPP_ASIO_HTTP
#define RAPP_ASIO_HTTP
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
#include <boost/asio.hpp>
#include "asio_handler.hpp"

namespace rapp {
namespace cloud {
/**
 * \class asio_http
 * \brief ASIO socket controller asynchronous http websockets used for cloud service calls
 * \version 0.7.2
 * \date 15 December 2016
 * \author Alex Giokas  <a.gkiokas@ortelio.co.uk>
 * \see asio_handler
 * \see request
 * \see response
 */
class asio_http : public asio_handler<http_socket>
{
public:
    /**
 	 * \brief constructor
	 * \brief `cloud_function` is the virtual `json_parser::deserialize` receiving the data
	 * \brief `error_function` is the handler which may receive the errors
	 * \brief `io_service` is the ASIO service controller
	 * \brief `request` is a stream buffer containing the request
	 */
    asio_http(
                std::function<void(std::string)> cloud_function,
                std::function<void(error_code error)> error_function,
                boost::asio::io_service & io_service,
                boost::asio::streambuf & request
             );

	/**
	 * \brief begin connection
	 * \param query defines the URL/URI
	 * \param resolver resolves the URL/URI address
     * \param io_service is the queue on which jobs are scheduled
     * \warning disable ssl v2 and ssl v3 (allow only tls)
	 */
	void begin(
			    boost::asio::ip::tcp::resolver::query & query,
			    boost::asio::ip::tcp::resolver & resolver
              );

    /// \brief shutdown connection
    void shutdown(const boost::system::error_code);

private:

    /// \brief resolve
    void resolve(
                   boost::system::error_code  err,
                   boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                );

    /// \brief begin connection
	void connect(
                   const boost::system::error_code err,
                   boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                );

    /// \brief check if we have timed out
    void time_check();

private:
    /// error callback
    std::function<void(boost::system::error_code)> error_cb_;
    /// boost asio socket 
    std::shared_ptr<http_socket> socket_;
    /// request object
    boost::asio::streambuf & request_;
    /// deadline timer for timeouts
    std::shared_ptr<boost::asio::deadline_timer> deadline_;
};
}
}
#endif
