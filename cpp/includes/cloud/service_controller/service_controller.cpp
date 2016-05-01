#include "service_controller.hpp"
namespace rapp 
{
namespace cloud 
{

service_controller::service_controller()
: query_(address, port)
{}

void service_controller::run_job(const std::shared_ptr<asio_socket> job)
{
    assert(job);
    if (!job) {
        throw std::runtime_error("null param `job`");
    }
    boost::asio::io_service io;
    boost::asio::ip::tcp::resolver resolver(io);

    /*
    boost::asio::deadline_timer timer(io, boost::posix_time::seconds(3));
    timer.async_wait(boost::bind(&asio_socket::schedule,
                                 job,
                                 boost::ref(query_),
                                 boost::ref(resolver),
                                 boost::ref(io),
                                 boost::placeholders::_1));
    */
    job->schedule(query_, resolver, io);
    io.run();
}

void service_controller::run_jobs(std::vector<std::shared_ptr<asio_socket>> jobs)
{
    boost::asio::io_service io;
    boost::asio::ip::tcp::resolver resolver(io);

    for (const std::shared_ptr<asio_socket> job : jobs) {
        assert(job);
        if (!job) {
            throw std::runtime_error("null job in vector `jobs`");
        }
        job->schedule(query_, resolver, io);
    }
    io.run();
}
}
}
