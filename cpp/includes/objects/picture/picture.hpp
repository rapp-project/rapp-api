#ifndef RAPP_OBJECT_PICTURE
#define RAPP_OBJECT_PICTURE
#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * @class picture
 * @brief class which wraps around raw bytes of a picture
 * @version 3
 * @date January 2016
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class picture
{
public:

    /// Construct from a file-path
    picture(const std::string filepath)
    {
        std::ifstream bytestream(filepath, 
                                 std::ios::in | std::ios::binary | std::ios::ate);
        if (!bytestream.is_open())
            throw std::runtime_error("could not open bytestream for "+filepath);
        else 
            opencb_(bytestream);
    }

    /// Construct using an open file stream
    picture(std::ifstream & bytestream)
    {
        opencb_(bytestream);
    }

    /// Copy constructor
    picture(const picture &) = default;
    
    /// Assignment operator
    picture & operator=(const picture &) = default;

    /// Are pictures same ?
    bool operator==(const picture & rhs) const
    {
        return (this->bytearray_ == rhs.bytearray_);
    }

    /// Get picture as array of bytes
    std::vector<rapp::types::byte> bytearray() const
    {
        return bytearray_;
    }

    /// try and get image type (JPG/PNG supported)
    std::string type() const
    {
        return imgtype_;
    }

    /// Save picture to filepath
    bool save(const std::string filepath)
    {
        std::ofstream os(filepath, std::ios::out | std::ofstream::binary);
        if (os.is_open())
        {
            std::copy(bytearray_.begin(), bytearray_.end(), 
                      std::ostreambuf_iterator<rapp::types::byte>(os));
            os.close();
            return true;
        }
        else
            return false;
    }

private:

    // Delete empty constructor    
    picture() = delete;

    // Parse the bytestream into the bytearray
    void opencb_(std::ifstream & bytestream)
    {
        // copy byte by byte
        bytestream.seekg(0, std::ios_base::end);
        std::streampos fileSize = bytestream.tellg();
        bytearray_.resize(fileSize);
        bytestream.seekg(0, std::ios_base::beg);
        bytestream.read(&bytearray_[0], fileSize);

        // Check Magic Number to find picture format
        if ((unsigned int)bytearray_[0] == 0xFFFFFF89 
            && (unsigned int)bytearray_[1] == 0x00000050)
            imgtype_ = "png";
        if ((unsigned int)bytearray_[0] == 0xFFFFFFFF 
            && (unsigned int)bytearray_[1] == 0xFFFFFFD8)
            imgtype_ = "jpg";
    }

    std::vector<rapp::types::byte> bytearray_;
    std::string imgtype_;
};
}
}
#endif
