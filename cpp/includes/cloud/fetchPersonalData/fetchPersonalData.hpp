#ifndef RAPP_SERVICE_CLOUD_FETCH_PERSONAL_DATA
#define RAPP_SERVICE_CLOUD_FETCH_PERSONAL_DATA
#include "Includes.ihh"

namespace rapp {
namespace cloud {

/**
 * @class fetchPersonalData
 * @brief Get all personal data for a specific user
 * @version 1
 * @date 18-April-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */

class fetchPersonalData : public rapp::services::asio_service_http
{
  public:
    
    /**
     * @brief Constructor for obtained personal (JSON) data for a specific user
     * @param user is the string username as stored in the database
     * @param callback is the functor that will received the obtained data
     * @note this is asynchronous, not serial, execution time may vary
     */
    fetchPersonalData (
                        const std::string user,
                        std::function < void( const std::string ) > callback
                      )
    : rapp::services::asio_service_http (), delegate__ ( callback )
    {
        // Form the POST string - simple argument
        post_ = "user="+user+"\r\n";
        
        // Craft the full URI
        std::string uri = "/hop/fetch_personal_data/";
        
        // Form the Header
        header_ = "POST " + uri + " HTTP/1.1\r\n";
        header_ += "Host: " + std::string( hostname ) + "\r\n";
        header_ += "Content-Type: application/x-www-form-urlencoded\r\n";
        header_ += "Content-Length: " + boost::lexical_cast<std::string>( post_.length() ) + "\r\n";
        header_ += "Connection: close\r\n\r\n";
        
        // bind the base class callback, to our handle_reply
        callback_ = std::bind ( &fetchPersonalData::handle_reply, this, std::placeholders::_1 );
    }
    
  private:
      
    /// Parse @param buffer received from the socket, into a vector of faces
    /// @note we do not do any parsing at all here - we assume the JSON will be handled by the caller
    void handle_reply ( boost::asio::streambuf & buffer )
    {
        std::string reply ( ( std::istreambuf_iterator<char>( &buffer ) ), std::istreambuf_iterator<char>() );
        delegate__ ( reply );
    }
    
    /// The callback called upon completion of receiving the detected faces
    std::function < void( const std::string ) > delegate__;
};
}
}
#endif