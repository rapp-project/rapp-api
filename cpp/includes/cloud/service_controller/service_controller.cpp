#include "service_controller.hpp"
namespace rapp 
{
namespace cloud 
{

service_controller::service_controller(const std::string address, const std::string port)
: io_service_(), query_(address, port), resolver_(io_service_)
{}

boost::asio::io_service & service_controller::queue()
{
    return io_service_;
}

void service_controller::run_job(const std::shared_ptr<asio_socket> job)
{
    assert(job);
    job->schedule(query_, resolver_, io_service_);
    io_service_.run();
    std::lock_guard<std::mutex> lock(mutex_);
    io_service_.reset();
}

void service_controller::run_jobs(std::vector<std::shared_ptr<asio_socket>> jobs)
{
    // WARNING : if synchronicity gives us problems here, 
	// then allocate a new io_service, and use it within scope
    for (const auto & job : jobs) {
        assert(job);
        job->schedule(query_, resolver_, io_service_);
    }
    io_service_.run();
    std::lock_guard<std::mutex> lock(mutex_);
    io_service_.reset();
}
}
}
