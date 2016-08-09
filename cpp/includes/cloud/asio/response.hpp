#ifndef RAPP_ASIO_RESPONSE
#define RAPP_ASIO_RESPONSE
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class asio_response
 * \version 0.7.0
 * \date August 2016 
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 * \brief class for taking the body of the streambuf , in other case
 * \ it throw an error 

 */
class response
{
public:

    ///
    response() = default;

    ///
    response(const response &) = default;

    ///
    response(std::string arg)
    {
        std::istringstream ss(arg);
        ss >> response_;
    }

    bool operator==(const response & rhs) const = default;

    /// \brief get the content leangth streambuf response
    /// \return content-length or -1 for not found
    std::size_t has_content_length() const
    {
        const auto head = response::to_string();
        static const boost::regex reg("Content-Length:\\s[-0-9]+", boost::regex::icase);
        boost::match_results<std::string::const_iterator> results;
        std::size_t length = -1;
        // search for matching regex
        if (boost::regex_search(response, results, reg)) {
            if (results.size() > 0) {
                std::string key = results[0];
                key.erase(std::remove(key.begin(), key.end(), '\n'), key.end());
                // find the `: `
                std::string hay = ": ";
                std::size_t i = key.find(hay);
                if (i != std::string::npos) {
                    length = boost::lexical_cast<std::size_t>(key.substr(i+hay.size(),
                                                                         std::string::npos));
                }
            }
        }
        return length;
     }

    /// \brief remove/strip the HTTP header and \return the body
    std::string strip_http_header(const std::string & data) const
    {
        // find the "\r\n\r\n" double return after the header
        std::size_t i = data.find("\r\n\r\n");
        if (i != std::string::npos) {
            return data.substr(i+4, std::string::npos);
        }
        else {
            throw std::runtime_error("no double return after header");
        }
    }

    /// \brief conversion from streambuf to string
    std::string to_string() const  
    {
        std::string buffer((std::istreambuf_iterator<char>(&response_)), 
                            std::istreambuf_iterator<char>());
        return buffer;
    }


protected:

    ///Response Container
    boost::asio::streambuf response_;
};
}
}

#endif
