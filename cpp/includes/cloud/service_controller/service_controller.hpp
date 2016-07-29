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
 * TODO: rename to `cloud_endpoint` or `cloud_control`
 * TODO: parametrize with ENUM so that we chose between `asio_http` and `asio_https`
 *
 * NOTE: running async jobs (e.g., `run_job_async` requires use of `io_service.poll()`
 */
class service_controller
{
public:

    /// \brief construct a service controller using a rapp::cloud::platform_info object
	service_controller(rapp::cloud::platform_info info)
	: cloud_(info), query_(info.address, info.port), io_(), resol_(io_)
	{}

    /// \brief make_call will instantly run an asynchronous cloud job
    template <typename T, typename... Args>
    void make_call(Args... args)
    {
		// this is sequentially blocked until the job has finished
		this->run_job(std::make_shared<T>(args...));
    }

    /// \brief make_job will create a cloud job which you must run using `run_job` or `run_jobs`
    template <typename T, typename... Args>
    std::unique_ptr<T> make_job(Args... args)
    {
        return std::move(std::unique_ptr<T>(new T(args...)));
    }

    /**
     * \brief run one service job
     * \param client is the actual object pointer that will be executed in a single operation
     */
    void run_job(const std::shared_ptr<asio_socket> job)
	{
		// will block until this job is complete, then we reset the work queue
		// in order to make it async, we need individual/scoped io_service objects.
		// if that is feasible!
		assert(job);
		job->schedule(query_, resol_, io_, cloud_);
		io_.run();
		io_.reset();
	}

    /**
     * \brief run a group of jobs in a batch
     * \param jobs is vector of constant pointers to client services
     * \note upon completion, the each object's handler will be invoked
     * \warning upon completion, the queue schedule will be reset.
     */
    void run_jobs(const std::vector<std::shared_ptr<asio_socket>> & jobs)
	{
		for (const std::shared_ptr<asio_socket> & job : jobs) {
			assert(job);
			job->schedule(query_, resol_, io_, cloud_);
		}
		// will block until all jobs posted are complete, then we reset the work queue
		io_.run();
		io_.reset();
	}

    /// \brief stop the service controller
    void stop()
	{
		io_.stop();
	}

private:
	/// cloud params
    rapp::cloud::platform_info cloud_;
    /// resolution, query and io service
    boost::asio::ip::tcp::resolver::query query_;
    boost::asio::io_service io_;
    boost::asio::ip::tcp::resolver resol_;
};
}
}
#endif
