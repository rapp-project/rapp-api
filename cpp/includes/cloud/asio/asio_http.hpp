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
#include "asio_socket.hpp"
namespace rapp {
namespace cloud {
/**
 * \class asio_http
 * \brief ASIO socket controller for cloud service calls (plaintext)
 * \version 0.7.0
 * \date 12 August 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 * \see asio_handler
 * \see request
 * \see response
 */
class asio_http 
{
public:
	/**
	 * \brief construct a plaintext http socket type
	 * \param cloud_function is the `json_parser::deserialise` virtual method
	 * \param error_function is a the callback receiving errors
	 * \param io_service will control the asio operation
	 * \param request is the buffer containing the request data
	 */
    asio_http(
                std::function<void(std::string)> cloud_function,
                std::function<void(error_code error)> error_function,
                boost::asio::io_service & io_service,
                boost::asio::streambuf request
             );
    
    /** 
     * schedule this client as a job for execution using
     * \param query defines the actual URL/URI
     * \param resolver is the URL/URI resolver reference
     * \param io_service is the queue on which jobs are scheduled
     */
    void begin( 
                boost::asio::ip::tcp::resolver::query & query,
			    boost::asio::ip::tcp::resolver & resolver
              );
        
    /**
     * \brief connection handler
     * \param err is a possible error
     * \param endpoint_iterator is boosts' hostname address handler
     */
     void connect(boost::system::errc err);

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
