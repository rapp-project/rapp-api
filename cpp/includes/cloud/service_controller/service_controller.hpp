#ifndef RAPP_SERVICE_CONTROLLER
#define RAPP_SERVICE_CONTROLLER
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class service_controller
 * \brief Main class that controllers RAPP Services
 * \version 
 * \date January-2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 * 
 * This class controls services (be it on cloud or robot). A service is a callable function
 * which offers some type of functionality to the callee.
 * Whilst most services reside on the cloud (rapp::services::cloud) some may reside on the robot (rapp::services::robot)
 * The service controller is used for either clour or robot, as it essentially controlls the socket connections.
 * This is low-level stuff, and is of little concern to external developers, and is to be used only by
 * developers who wish to create or extend services.
 */
class service_controller
{
public:

	/// no empty constructor
	service_controller();

    /**
     * \brief Run one service job
     * \param client is the actual object pointer that will be executed in a single operation
     * \note upon completion, the object's handler will be invoked
     * \note upon completion - scheduler is reset
     */
    void run_job(const std::shared_ptr<asio_socket> job);

    /**
     * \brief Run a group of jobs in a batch
     * \param jobs is vector of constant pointers to client services
     * \note upon completion, the each object's handler will be invoked
     * \warning upon completion, the queue schedule will be reset.
     */
    void run_jobs(const std::vector<std::shared_ptr<asio_socket>> & jobs);

    /// \brief stop the service controller
    void stop();

private:
    /// resolution, query and io service
    boost::asio::ip::tcp::resolver::query query_;
    boost::asio::io_service io_;
    boost::asio::ip::tcp::resolver resol_;
};
}
}
#endif
