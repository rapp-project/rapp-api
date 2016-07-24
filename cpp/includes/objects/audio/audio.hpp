#ifndef RAPP_OBJECT_AUDIO
#define RAPP_OBJECT_AUDIO
#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \class audio
 * \brief class which wraps around raw bytes of an audiofile
 * \version 2
 * \date January-2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 *
 * TODO: instead of making `audio` polymorphic we can request as ctor param
 *		 the audio_source (instead of infering it)
 *		 and we can extract the extension, and use it as audio type (instead of hardcoding it)
 *		 thus reducing the number of classes and the usage of pointers.
 */
class audio
{
public:
    /// Construct from a file on disk
    audio(const std::string filepath)
    {
        std::ifstream bytestream(filepath, std::ios::in | std::ios::binary | std::ios::ate);
        if (!bytestream.is_open()) {
            throw std::runtime_error("could not open bytestream for "+filepath);
        }
        else {
            read_bytes(bytestream);
        }
    }

    /// \brief Construct using an open file stream
    /// \param bytestream will be **consumed** by the object
    audio(std::ifstream & bytestream)
    {
        read_bytes(bytestream);
    }

    /// \brief construct using an existing byte-array
    /// \param bytearray should contain the audio data
    audio(std::vector<rapp::types::byte> bytearray)
    : bytearray_(bytearray)
    {}

    /// Copy constructor
    audio(const audio &) = default;

    /// Get audio as array of bytes
    std::vector<rapp::types::byte> bytearray() const
    {
        return bytearray_;
    }

    /// Are audios same ?
    bool operator==(const audio & rhs) const
    {
        return typeid(*this) == typeid(rhs) &&
               (this->bytearray_ == rhs.bytearray_);
    }

    /// Assignment operator
    audio & operator=(const audio &) = default;

    /// Save audio to filepath
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

    virtual std::string audio_source() const
    { return ""; }

    virtual std::string extension() const
    { return ""; }

private:

    // Delete empty constructor    
    audio() = delete;

    // Copy the bytestream into the bytearray
    void read_bytes(std::ifstream & bytestream)
    {
        bytestream.seekg(0, std::ios_base::end);
        std::streampos fileSize = bytestream.tellg();
        bytearray_.resize(fileSize);
        bytestream.seekg(0, std::ios_base::beg);
        bytestream.read(&bytearray_[0], fileSize);
    }

    // Actual bytes of audio file
    std::vector<rapp::types::byte> bytearray_;
};
/// OGG Class specialisation
class ogg : public audio
{
public:

    ogg(const std::string filepath) 
    : audio(filepath){}

    ogg(std::ifstream & bytestream) 
    : audio(bytestream){}

    std::string audio_source() const
    { return "nao_ogg";}

    std::string extension() const
    { return ".ogg";}
};
/// WAV Class specialisation for a single channel
class nao_single_channel_wav : public audio
{
public:

    nao_single_channel_wav(const std::string filepath)
    : audio (filepath){}

    nao_single_channel_wav(std::ifstream & bytestream)
    : audio (bytestream){}

    std::string audio_source() const
    { return "nao_wav_1_ch"; }

    std::string extension() const
    { return ".wav"; }
};
/// WAV Class specialisation for quad channel
class nao_quad_channel_wav : public audio
{
public:

    nao_quad_channel_wav(const std::string filepath)
    : audio (filepath){}

    nao_quad_channel_wav(std::ifstream & bytestream)
    : audio (bytestream){}

    std::string audio_source() const
    { return "nao_wav_4_ch";}

    std::string extension() const
    { return ".wav";}
};
/// WAV Single channel 16Khz > Headset audio source
class microphone_wav : public audio
{
public:

    microphone_wav(const std::string filepath)
    : audio (filepath){}

    microphone_wav(std::ifstream & bytestream)
    : audio (bytestream){}

    microphone_wav(std::vector<rapp::types::byte> bytearray)
    : audio(bytearray)
    {}

    std::string audio_source() const
    { return "headset";}

    std::string extension() const
    { return ".wav";}
};
}
}
#endif
