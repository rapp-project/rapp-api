#ifndef RAPP_ASIO_HTTP_POST
#define RAPP_ASIO_HTTP_POST
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class http_post 
 * \brief use to store and pass POST data and realted info  
 * \version 0.7.0
 * \date August 2016
 * \author Maria Ramos<m.ramos@ortelio.co.uk>
 */
class http_post
{
public:

    http_post(std::string boundary)
    : boundary_(boundary)
    {}

    http_post() = default;

    /// \brief set the boundary to \param boundary
    void set_boundary(std::string boundary)
    {
        boundary_ = boundary;
    }

    /// \brief adding content to the POST data
    /// \param name of the variable
    /// \param content is the value unquote
    /// \param newline allows to add an extra line with "\r\n"
    void add_content(
                     std::string name, 
                     std::string content,
                     bool newline
                    )
    {
        data_ += "--" + boundary_ + "\r\n";
        data_ += "Content-Disposition: form-data; name=\""\ + name + "\"\r\n\r\n";
        data_ += content;  
        if (newline) {
            data_ += "\r\n";
        }
    }

    /// \brief adding content to the POST data
    /// \param name is the name of the string variable
    /// \param filename which want to use
    /// \param vector contains the data of the file in binary type  
    void add_content(
                      std::string name,
                      std::string filename,
                      std::vector<rapp::types::byte> bytes
                    )
        
    {
    
        data_ += "--" + boundary_ + "\r\n";
        data_ += "Content-Disposition: form-data; name=\""\ + name + "\"\";";
        data_ += " filename=\"" + filename + "\"\r\n";
        data_ += "Content-Transfer-Encoding: binary\r\n\r\n";
        data_.insert(data_.end(), bytes.begin(), bytes.end());
        data_ += "\r\n";
    }

    /// \brief call once, closes the POST field
    void end()
    {
        if (open_) {
            open_ = false;
            data_ += "--" + boundary + "--\r\n";
        }
    }

    bool is_open const
    {
        return open_;
    }

    /// \brief get the POST
    std::string to_string() const
    {
        return data_;
    }

    /// \brief get POST data `Content-Length`
    unsigned int size() const
    {
        return data_.size() * sizeof(std::string::value_type);
    }

private:
    /// POST data
    std::string data_;
    /// Boundary
    std::string boundary_;
    /// 
    std::atomic<bool> open_ = true;
};

}
}

#endif
