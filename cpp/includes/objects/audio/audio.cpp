#include "audio.hpp"
namespace rapp {
namespace object {

audio::audio(const std::string filepath)
{
    std::ifstream bytestream(filepath, std::ios::in | std::ios::binary | std::ios::ate);
    if (!bytestream.is_open()) {
        throw std::runtime_error("could not open bytestream for "+filepath);
    }
    else {
        read_bytes(bytestream);
    }
}

audio::audio(std::ifstream & bytestream)
{
    read_bytes(bytestream);
}

audio::audio(std::vector<rapp::types::byte> bytearray)
: bytearray_(bytearray)
{}

std::vector<rapp::types::byte> audio::bytearray() const
{
    return bytearray_;
}

bool audio::operator==(const audio & rhs) const
{
    return typeid(*this) == typeid(rhs) &&
           (this->bytearray_ == rhs.bytearray_);
}

bool audio::operator!=(const audio & rhs) const
{
    return (this->bytearray_ != rhs.bytearray_);

}

bool audio::save(const std::string filepath)
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

std::string audio::audio_source() const
{ return ""; }


void audio::read_bytes(std::ifstream & bytestream)
{
    bytestream.seekg(0, std::ios_base::end);
    std::streampos fileSize = bytestream.tellg();
    bytearray_.resize(fileSize);
    bytestream.seekg(0, std::ios_base::beg);
    bytestream.read(&bytearray_[0], fileSize);
}

}
}
