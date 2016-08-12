#ifndef RAPP_ASIO_HTTP_HEADER
#define RAPP_ASIO_HTTP_HEADER
#include "includes.ihh"
namespace rapp{
namespace cloud{
/**
 * \class http_header
 * \version 0.7.0
 * \date August 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class http_header
{
public:
    /// \brief constructor of the http_header
    /// \brief set the \param uri \warning requires newline
    http_header(std::string uri)
    : uri_(uri)
    {
        boundary_ = rapp::misc::random_boundary();
        contenty_type_ = "Content-Type: multipart/form-data; boundary=" + boundary_;
        connection_ = "Connection: close\r\n";
        user_agent_ = "User-Agent: rapp_api/cpp/0.7.0\r\n";
    }

    /// \brief complete the rest of parameters that we need for the http_header and 
    /// return all of them in a string
    /// \param endpoint contains the data of the platform
    /// \param length is the size of the content
    std::string to_string(rapp::cloud::platform_info endpoint, unsigned int length) const 
    {
        std::string host = "Host: " + endpoint.address + ":" endpoint.port + "\r\n";
        std::string accept_token = "Accept-Token: " + endpoint.token + "\r\n";
        content_length_ = "Content-Length: " 
                          + boost::lexical_cast<std::string>(length) +"\r\n";

        return uri_ + host + user_agent_ + connection_ + accept_token           
               + content_length_ + content_type_ + "\r\n\r\n"; 
    }

    /// \brief get boundary
    std::string get_boundary() const
    {
        return boundary_;
    }
    

private:    
    /// Uri
	std::string uri_;
    /// User agent
	std::string user_agent_;
    /// for closing connection
	std::string connection_;
    /// Content-Length
	std::string content_length_;
    /// Content type
	std::string content_type_;
    /// Boundary
    std::string boundary_;
};
}
}
#endif
