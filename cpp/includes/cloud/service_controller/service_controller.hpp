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
        // create the cloud class
		auto obj = T(args...);
        boost::asio::streambuf request;
        obj.fill_buffer(boost::ref(request), info_);
        
        // bind the callback fo class T::deserialize for response processing
        auto callback = [&](std::string rhs) {
            obj.deserialise(rhs);
        };

        // create an asio_socket and run the request
        auto asio = std::make_unique<asio_http>(callback, derr_cb_, io_, request); 
        assert(asio);

        // start
		asio->begin(query_, resol_);
		io_.run();
		io_.reset();
    }

    /// \brief create an arbitrary number of cloud calls using a variadic template
    /// \see https://ideone.com/Fq242E
    template <typename... Args>
    void make_calls(Args... args)
    {
        // pack the variadic arguments in a tuple
        auto t = std::tuple<Args...>(args...);
        unsigned int size = std::tuple_size<decltype(t)>::value;

        // each variadic object will run the code below
        auto execute = [&](auto & obj){ 

            // fill buffer and get callback
            boost::asio::streambuf request;
            obj.fill_buffer(boost::ref(request), info_);

            // once asio finished, it should call the cloud call ::deserialise() method
            // won't the reference of `obj` go out of scope?
            // even more so, if I copy by value I will call the implicit deleted ctor?
            auto callback = [=](std::string rhs) {
                obj.deserialise(rhs);
            };

            // create an asio_socket and run the request
            auto asio = std::make_unique<asio_http>(callback, derr_cb_, io_, request); 
            assert(asio);

            asio->begin(query_, resol_);
        };

        // iterate the cloud calls running them in a batch
        for (int i = 0; i < size; i++) {
            rapp::misc::visit_at(t, i, execute);
        }

        // run all calls, then reset asio queue
        io_.run();
		io_.reset();
    }

    /// \brief make a cloud object
    /// \type T defines the cloud class
    /// \type Args is the variadic arguments of the class constructor
    template <typename T, typename... Args>
    T make_class(Args ...args)
    {
        return T(args...);
    }

    /// \brief stop the service controller
    void stop()
	{
		io_.stop();
	}

protected:
    
	/// \brief handle asio errors
	void default_error_handler(boost::system::error_code error) const
	{
        std::cerr << error.message() << std::endl;
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
