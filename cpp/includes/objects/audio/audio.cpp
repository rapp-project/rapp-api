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


/// OGG Class specialisation

ogg::ogg(const std::string filepath) 
: audio(filepath){}

ogg::ogg(std::ifstream & bytestream) 
: audio(bytestream){}

std::string ogg::audio_source() const
{ return "nao_ogg";}


/// WAV Class specialisation for a single channel
nao_single_channel_wav::nao_single_channel_wav(const std::string filepath)
: audio (filepath){}

nao_single_channel_wav::nao_single_channel_wav(std::ifstream & bytestream)
: audio (bytestream){}

std::string nao_single_channel_wav::audio_source() const
{ return "nao_wav_1_ch"; }



/// WAV Class specialisation for quad channel
nao_quad_channel_wav::nao_quad_channel_wav(const std::string filepath)
: audio (filepath){}

nao_quad_channel_wav::nao_quad_channel_wav(std::ifstream & bytestream)
: audio (bytestream){}

std::string nao_quad_channel_wav::audio_source() const
{ return "nao_wav_4_ch";}


/// WAV Single channel 16Khz > Headset audio source
microphone_wav::microphone_wav(const std::string filepath)
: audio (filepath){}

microphone_wav::microphone_wav(std::ifstream & bytestream)
: audio (bytestream){}

microphone_wav::microphone_wav(std::vector<rapp::types::byte> bytearray)
: audio(bytearray)
{}

std::string microphone_wav::audio_source() const
{ return "headset";}

}
}
