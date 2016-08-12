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
 * 
 * The user defined error callback may receive the following errors:
 *    - boost::system::errc::bad_message if the header is not followed by a double return carriage
 *    - boost::system::errc::no_message if the platform does not respond with any data
 *    - boost::system::errc::protocol_not_supported if the reply does not conform to HTTP 1.1
 *    - boost::system::errc::protocol_error if HTTP header does not respond with 200 status code
 */

typedef boost::system::error_code error_code;

class response
{
public:
    

    /// \brief constructor by passing an error callback
    response(std::function<void(error_code error)> callback)
    : callback_(callback)
    {}

    ///\brief constructor by passing an string
    response(std::string arg)
    {
        std::istringstream ss(arg);
        ss >> buffer_;
    }

    /// \brief get the content length streambuf response
    /// \return content-length or -1 for not found
    std::size_t has_content_length() const
    {
        const std::string head = response::to_string();
        static const boost::regex reg("Content-Length:\\s[-0-9]+", boost::regex::icase);
        boost::match_results<std::string::const_iterator> results;
        std::size_t length = -1;
        // search for matching regex
        if (boost::regex_search(head, results, reg)) {
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
            std::cerr << "no double return after header\r\n";
            error_cb_(boost::systemm::errc::bad_message);
        }
    }

    /// \brief conversion from streambuf to string
    std::string to_string() const  
    {
        std::string buffer((std::istreambuf_iterator<char>(&buffer_)), 
                            std::istreambuf_iterator<char>());
        return buffer;
    }
 
    /// \brief check if http response is 200
    /// \param error handler will receive error if response is invalid
    bool check_http_header() const
    {
        std::istream buffer_stream(&buffer_);
        std::string http_version;
        buffer_stream >> http_version;
        unsigned int status_code;
        buffer_stream >> status_code;
        std::string status_message;
        std::getline(buffer_stream, status_message);
        // did not receive a reply
        if (!buffer_stream) {
            error_cb_(boost::system::errc::no_message);
            return false;
        }
        // reply is not HTTP Protocol
        else if (http_version.substr(0, 5) != "HTTP/") {
            error_cb_(boost::system::errc::protocol_not_supported);
            return false; 
        }
        // HTTP reply is not 200
        else if (status_code != 200) {
            error_cb_(boost::system::errc::protocol_error);
            std::cerr << status_code << std::endl;
            return false;
        }
        return true;
    }
      
   /// \brief take data from the response and save it in JSON
   bool take_data(std::function<void(std::string)> callback)
   {
        assert(callback);
         // get string received in response streambuf
        std::string data = to_string();
        // Check there is a Content-Length and Remove HTTP header from string response.
        // strip the header & append data to response
        if (!flag_) {
            // verify there is `Content-Length`
            if (has_content_length() > 0) {
                std::string tmp = data;
                data = strip_http_header(tmp);
            }
            else {
                error_cb_(boost::systemm::errc::bad_message);
               // throw std::runtime_error("no `Content-Length` in header response");
            }
            flag_ = true;
        }
        // append response and count bytes
        json_ += data;
        bytes_transferred_ += response.size();

        // have received the data correctly
        if (bytes_transferred_ >= content_length_) {
            callback(json_); 
            return true;
        }
        return false;
   }

   /// \brief clean the variables
   void reset()
   {

        json_.clear();
        content_length_ = 0;
        bytes_transferred_ = 0;
        flag_ = false;

   }

protected:
    ///Response Container
    boost::asio::streambuf buffer_;
    /// JSON reply from platform
    std::string json_;

private:
    /// error callback_
    std::function<void(error_code error)> error_cb_;
    /// amount of bytes received
    unsigned int bytes_transferred_;
    /// still reading data into streambuf
    std::atomic<bool> read_flag_;
};
}
}

#endif
