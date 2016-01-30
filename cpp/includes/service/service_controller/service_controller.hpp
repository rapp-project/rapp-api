#ifndef RAPP_SERVICE_CONTROLLER
#define RAPP_SERVICE_CONTROLLER
#include "includes.ihh"
namespace rapp {
namespace services {
/**
 * @class service_controller
 * @brief Main class that controllers RAPP Services
 * @version 2
 * @date 20-April-2014
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
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
    /**
     * default constructor
     */
    service_controller();

    /// The Service Queue
    boost::asio::io_service & queue();

    /**
     * @brief Run one service job
     * @param client is the actual object pointer that will be executed in a single operation
     * @note upon completion, the object's handler will be invoked
     * @note this method will block, until job is finished
     */
    void run_job(const std::shared_ptr<asio_socket> job);

    /**
     * @brief Run a group of jobs in a batch
     * @param jobs is vector of constant pointers to client services
     * @note upon completion, the each object's handler will be invoked
     * @warning upon completion, the queue schedule will be reset.
     */
    void run_jobs(std::vector<std::shared_ptr<asio_socket>> jobs);

private:
    /// Cloud Server Address
    const std::string server_;
    /// Username token
    const std::string username_;
    // NOTE: isnt this a duplicate from globals::auth_token ?
    const std::string auth_base64_ = "cmFwcGRldjpyYXBwZGV2";
    /// Authentication token
    const std::string password_;
    /// IO service
    boost::asio::io_service io_service_;
    /// Endpoint Resolver
    boost::asio::ip::tcp::resolver::query query_;
    /// Resolution for TCP
    boost::asio::ip::tcp::resolver resolver_;
    /// Work queue
    std::shared_ptr<boost::asio::io_service::work> work_;
    /// Service Mutex
    std::mutex mutex_;
};
}
}
#endif
