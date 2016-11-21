#ifndef RAPP_ASIO_SOCKET_
#define RAPP_ASIO_SOCKET_
#include "includes.ihh"
namespace rapp {
namespace cloud {
///
/// api.rapp.cloud - 
constexpr char address[] = "localhost";
/// api.rapp.cloud - HOP server port
constexpr char port[] = "9001";    


/**
 * \brief Abstract Base ASIO Socket class
 * Use for passing around to the service controller, various types of cloud handlers.
 * This Interface is needed so that different handlers can be passed to the scheduler transparently.
 * \class asio_socket
 * \version 2
 * \date 26-April-2015
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class asio_socket
{
public:
    /** 
     * schedule this object as a job for ASIO execution
     * \param query defines the actual URL/URI
     * \param resolver is the URL/URI resolver reference
     * \param io_service is the service queue on which this job will be scheduled to run
     */
    virtual void schedule(
                             boost::asio::ip::tcp::resolver::query & ,
                             boost::asio::ip::tcp::resolver & ,
                             boost::asio::io_service &
                         ) = 0;
    /** 
     * schedule this object as a job for ASIO execution
     * \param query defines the actual URL/URI
     * \param resolver is the URL/URI resolver reference
     * \param io_service is the service queue on which this job will be scheduled to run
     * \param error is the received time-out error when scheduling *this* job
     */
    /*
    virtual void schedule(
                             boost::asio::ip::tcp::resolver::query & ,
                             boost::asio::ip::tcp::resolver & ,
                             boost::asio::io_service &,
                             const boost::system::error_code &
                         ) = 0;
     */
};
}
}
#endif
