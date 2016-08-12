#ifndef RAPP_ASIO_REQUEST
#define RAPP_ASIO_REQUEST
#include "include.ihh"
namespace rapp{
namespace cloud{

/**
 * \class request
 * \brief
 * \version 0.7.0
 * \date August 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class request
{
public:

    request() = default;
    
    request(
            const rapp::cloud::http_header header, 
            const rapp::cloud::http_post post
           )
    : header_(header), post_(post)
    {}

    /// \brief fill the socket streambuf with the request header and post data
    /// \param request is a reference to the socket streambuf being modified
    /// \param info is the platform endpoint (address, port, etc)
    /// \note this method will modify the header by setting the HOST, PORT and TOKEN
    boost::asio::streambuf fill_buffer(rapp::cloud::platform_info info) 
    {
        boost::asio::streambuf buffer;
        std::ostream request_stream(&buffer);
        request_stream << header_.to_string(info, post_.size()) 
		    		   << post_.to_string();
        return std::move(buffer);
    }

protected:

    rapp::cloud::http_header header_;
    rapp::cloud::http_post   post_;
};
}
}
#endif
