#ifndef RAPP_ASIO_HTTPS
#define RAPP_ASIO_HTTPS
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
#include <boost/asio/ssl.hpp>
#include "asio_handler.hpp"
namespace rapp {
namespace cloud {
/**
 * \class asio_https
 * \brief ASIO socket controller for TLS (encrypred) cloud service calls
 * \version 0.7.0
 * \date 12 August 2016
 * \author Alex Giokas  <a.gkiokas@ortelio.co.uk>
 * \see asio_handler
 * \see request
 * \see response
 */
class asio_https : public asio_handler<tls_socket>
{
public:
	/**
	 * \brief constructor
	 * \brief `cloud_function` is the virtual `json_parser::deserialize` receiving the data
	 * \brief `error_function` is the handler which may receive the errors
	 * \brief `io_service` is the ASIO service controller
	 * \brief `request` is a stream buffer containing the request
	 * TODO: pass a PEM filename to evaluate CA
	 */
    asio_https(
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

private:
	/// \brief verify TLS certificate
	bool verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx);

	/// \brief begin connection
	void connect(const boost::system::error_code err);

	/// \brief handle handshake
  	void handshake(const boost::system::error_code err);

    /// \brief shutdown handler
    void shutdown(const boost::system::error_code);

private: 
    /// error callback
    std::function<void(boost::system::error_code err)> error_cb_;
	/// tls context
	boost::asio::ssl::context ctx_;
    /// boost asio socket 
    std::shared_ptr<tls_socket> socket_;
    /// request object
    boost::asio::streambuf & request_;
};
}
}
#endif
