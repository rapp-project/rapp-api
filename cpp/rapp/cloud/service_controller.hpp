#ifndef RAPP_SERVICE_CONTROLLER
#define RAPP_SERVICE_CONTROLLER
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
#include <rapp/cloud/asio/platform.hpp>
#include <rapp/cloud/asio/asio_http.hpp>
#include <rapp/cloud/asio/asio_https.hpp>
#include <rapp/cloud/asio/caller.hpp>
namespace rapp {
namespace cloud {
/**
 * \class service_controller
 * \brief Main class that controllers RAPP Services
 * \version 0.7.2
 * \date 16 December 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 * TODO (0.7.3): enable choice of HTTP or TLS
 *				 enable choice of TLS CA.PEM file (pass to asio_https)
 *               enable choice of ignoring CA on TLS
 */
class service_controller
{
public:

    /// \brief construct a service controller using a rapp::cloud::platform object
	service_controller(rapp::cloud::platform info);

	/** 
     * \brief construct a service controller using
	 * \param info the cloud platform
	 * \param error_handler the error callback which receives boost asio errors
     */
	service_controller(
						rapp::cloud::platform info,
						std::function<void(boost::system::error_code error)> error_handler
					  );

    /// \brief set a time-out different than the default of 1 second
    void set_timeout(unsigned long int timeout);

    /** 
     * \brief make_call will instantly run an asynchronous cloud job
     * \typename T is a templated cloud class
     * \param args is the T cloud class arguments
     */
    template <typename T, typename... Args>
    void make_call(Args... args);

    /** 
     * \brief create batch of cloud calls using a variadic template
     * \param args is a variadic template of cloud classes
     * \note construct inline passing each class's arguments
     */
    template <typename... Args> 
    void make_calls(Args... args);

    /// \brief stop the service controller
    void stop();

	/// \brief handle asio errors
	void default_error_handler(boost::system::error_code error) const;

private:
	// cloud params
    rapp::cloud::platform info_;
    // resolution, query and io service
    boost::asio::ip::tcp::resolver::query query_;
	// service IO for TCP/IP control
    boost::asio::io_service io_;
	// address resolver
    boost::asio::ip::tcp::resolver resol_;
	// error handler
	std::function<void(boost::system::error_code)> error_;
	// default error handler
	std::function<void(boost::system::error_code)> derr_cb_;
    // default timeout
    unsigned long int timeout_;
};

#include "service_controller.impl"
}
}
#endif
