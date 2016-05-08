#include "service_controller.hpp"
namespace rapp {
namespace cloud {

service_controller::service_controller()
: query_(address, port), io_(), resol_(io_)
{}

void service_controller::run_job(const std::shared_ptr<asio_socket> job)
{
    assert(job);
    job->schedule(query_, resol_, io_);
    // will block until this job is complete
    // then we reset the work queue
    io_.run();
    io_.reset();
}

void service_controller::run_jobs(const std::vector<std::shared_ptr<asio_socket>> & jobs)
{
    //boost::asio::io_service io;
    //boost::asio::ip::tcp::resolver resol(io);
    for (const std::shared_ptr<asio_socket> & job : jobs) {
        assert(job);
        job->schedule(query_, resol_, io_);
    }
    // will block until all jobs posted are complete
    // then we reset the work queue
    io_.run();
    io_.reset();
}

void service_controller::stop()
{
    io_.stop();
}

}
}
