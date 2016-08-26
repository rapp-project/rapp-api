#include "picture.hpp"
namespace rapp {
namespace object {

picture::picture(const std::string filepath)
{
    std::ifstream bytestream(filepath, std::ios::in | std::ios::binary | std::ios::ate);
    if (!bytestream.is_open()) {
        throw std::runtime_error("could not open bytestream for "+filepath);
    }
    else { 
        opencb_(bytestream);
    }
}

picture::picture(std::ifstream & bytestream)
{
    opencb_(bytestream);
}

bool picture::operator==(const picture & rhs) const
{
    return (this->bytearray_ == rhs.bytearray_);
}

bool picture::operator!=(const picture & rhs) const
{
    return (this->bytearray_ != rhs.bytearray_);
}

std::vector<rapp::types::byte> picture::bytearray() const
{
    return bytearray_;
}

std::string picture::type() const
{
    return imgtype_;
}

bool picture::save(const std::string filepath)
{
    std::ofstream os(filepath, std::ios::out | std::ofstream::binary);
    if (os.is_open()) {
        std::copy(bytearray_.begin(), bytearray_.end(), 
                  std::ostreambuf_iterator<rapp::types::byte>(os));
        os.close();
        return true;
    }
    else {
        return false;
    }
}

void picture::opencb_(std::ifstream & bytestream)
{
    // copy byte by byte
    bytestream.seekg(0, std::ios_base::end);
    std::streampos fileSize = bytestream.tellg();
    bytearray_.resize(fileSize);
    bytestream.seekg(0, std::ios_base::beg);
    bytestream.read(&bytearray_[0], fileSize);
    // Check Magic Number to find picture format
    if ((unsigned int)bytearray_[0] == 0xFFFFFF89 && (unsigned int)bytearray_[1] == 0x00000050) {
        imgtype_ = "png";
    }
    if ((unsigned int)bytearray_[0] == 0xFFFFFFFF && (unsigned int)bytearray_[1] == 0xFFFFFFD8) {
        imgtype_ = "jpg";
    }
}

}
}
