#ifndef RAPP_CLOUD_FETCH_PERSONAL_DATA
#define RAPP_CLOUD_FETCH_PERSONAL_DATA
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class fetch_personal_data
 * \brief Get all personal data for a specific user
 * \version 1
 * \date 18-April-2015
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class fetch_personal_data : public rapp::services::asio_service_http
{
public:
    
    /**
     * \brief Constructor for obtained personal (JSON) data for a specific user
     * \param user is the string username as stored in the database
     * \param callback is the functor that will received the obtained data
     * \note this is asynchronous, not serial, execution time may vary
     */
    fetch_personal_data(
                          const std::string user,
                          std::function < void( const std::string ) > callback
                       )
    : rapp::services::asio_service_http(), delegate__(callback)
    {
        // Form the POST string - simple argument
        post_ = "user="+user+"\r\n";
        // Craft the full URI
        const std::string uri = "/hop/fetch_personal_data/";
        // Form the Header
        header_ = "POST " + uri + " HTTP/1.1\r\n";
        header_ += "Host: " + std::string( rapp::cloud::address ) + "\r\n";
        header_ += "Content-Type: application/x-www-form-urlencoded\r\n";
        header_ += "Content-Length: " + boost::lexical_cast<std::string>(post_.length()) + "\r\n";
        header_ += "Connection: close\r\n\r\n";
        // bind the base class callback, to our handle_reply
        callback_ = std::bind(&fetchPersonalData::handle_reply, this, std::placeholders::_1);
    }
    
private:
      
    /// Get reply and send it directly to delegate
    /// \note we do not do any parsing at all here 
    void handle_reply(std::string json)
    {
        delegate__(json);
    }
    
    /// The callback called upon completion of receiving the detected faces
    std::function<void(const std::string)> delegate__;
};
}
}
#endif
