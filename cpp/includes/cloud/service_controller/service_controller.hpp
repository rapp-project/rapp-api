#ifndef RAPP_SERVICE_CONTROLLER
#define RAPP_SERVICE_CONTROLLER
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class service_controller
 * \brief Main class that controllers RAPP Services
 * \version 0.6.0
 * \date July-2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 *
 * TODO: rename to `cloud_endpoint` or `cloud_control`
 * TODO (0.7.0) enable custom error handler 
 *				enable setting time-out parameter
 */
class service_controller
{
public:

    /// \brief construct a service controller using a rapp::cloud::platform_info object
	service_controller(rapp::cloud::platform_info info)
	: cloud_(info), query_(info.address, info.port), io_(), resol_(io_)
	{}

	/// \brief construct a service controller using
	/// \param info the cloud platform
	/// \param error_handler the error callback which receives boost asio errors
	service_controller(
						rapp::cloud::platform_info info,
						std::function<void(boost::system::error_code error)> error_handler
					  )
	: cloud_(info), query_(info.address, info.port), io_(), resol_(io_), error_(error_handler) 
	{}

    /// \brief make_call will instantly run an asynchronous cloud job
    template <typename T, typename... Args>
    void make_call(Args... args)
    {
        std::function<void(boost::system::errc)> def_cb = std::bind(&service_controller::default_error_handler,
                                                                    this,
                                                                    std::placeholders::_1);
        std::shared_ptr<T> ptr = std::make_shared<T>(args...);
        std::shared_ptr<asio_http> asio = std::make_shared<asio_http>(std::bind(&T::deserialise, 
                                                                                ptr.get(), 
                                                                                std::placeholders::_1),
                                                                      def_cb, 
                                                                      io_, 
                                                                      ptr->fill_buffer(cloud_)); 
        run_job(asio);
    }

    /**
     * \brief run one cloud job
     * \param job is the cloud call
	 * \note subsequent calls will block in a FIFO queue
     */
    void run_call(std::shared_ptr<T> job)
	{
		assert(job);
		job->begin(query_, resol_);
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
        std::cerr << error.what() << std::endl;
	}

private:
	// cloud params
    rapp::cloud::platform_info cloud_;
    // resolution, query and io service
    boost::asio::ip::tcp::resolver::query query_;
	// service IO for TCP/IP control
    boost::asio::io_service io_;
	// address resolver
    boost::asio::ip::tcp::resolver resol_;
	// error handler
	std::function<void(boost::system::error_code)> error_;
};
}
}
#endif
