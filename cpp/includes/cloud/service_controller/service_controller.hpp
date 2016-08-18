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

namespace rapp {
namespace cloud {
/**
 * \class service_controller
 * \brief Main class that controllers RAPP Services
 * \version 0.7.0
 * \date 12 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 *
 * TODO: rename to `cloud_endpoint` or `cloud_control`
 * TODO (0.7.0) enable custom error handler 
 *				enable setting time-out parameter
 *				enable choice of HTTP or TLS
 *				enable choice of TLS CA.PEM file
 */
class service_controller
{
public:

    /// \brief construct a service controller using a rapp::cloud::platform object
	service_controller(rapp::cloud::platform info)
	: info_(info), query_(info.address, info.port), io_(), resol_(io_)
	{
		derr_cb_ = std::bind(&service_controller::default_error_handler, this, std::placeholders::_1);
	}

	/// \brief construct a service controller using
	/// \param info the cloud platform
	/// \param error_handler the error callback which receives boost asio errors
	service_controller(
						rapp::cloud::platform info,
						std::function<void(boost::system::error_code error)> error_handler
					  )
	: info_(info), query_(info.address, info.port), io_(), resol_(io_), error_(error_handler) 
	{}

    /// \brief make_call will instantly run an asynchronous cloud job
    template <typename T, typename... Args>
    void make_call(Args... args)
    {
		auto ptr = std::make_shared<T>(args...);
        assert(ptr);

        boost::asio::streambuf request;
        ptr->fill_buffer(boost::ref(request), info_);
        
        auto callback = std::bind(&T::deserialise, ptr.get(), std::placeholders::_1);

        auto asio = std::make_unique<asio_http>(callback, derr_cb_, io_, request); 
        assert(asio);
		asio->begin(query_, resol_);
		io_.run();
		io_.reset();
    }

    /**
     * \brief run a group of jobs asynchronously as a single batch
     * \param jobs is vector of constant pointers to client services
	 * \note subsequent calls of `run_job` or `run_jobs` will block in a FIFO queue
     */
    /*
    void run_calls(const std::vector<std::shared_ptr<>> jobs)
	{
		for (const std::shared_ptr<asio_socket> & job : jobs) {
			assert(job);
			job->schedule(query_, resol_, io_, cloud_);
		}
		io_.run();
		io_.reset();
	}
    */

    /// \brief stop the service controller
    void stop()
	{
		io_.stop();
	}

protected:

	/// \brief handle asio errors
	void default_error_handler(boost::system::error_code error) const
	{
        std::cerr << error << std::endl;
	}

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
};
}
}
#endif
