#ifndef RAPP_OBJECT_AUDIO
#define RAPP_OBJECT_AUDIO
/**
 * Copyright 2015 RAPP
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * #http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \class audio
 * \brief class which wraps around raw bytes of an audiofile
 * \version 0.7.0
 * \date 26 August 2016
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
    /// \brief Construct from a file on disk
    audio(const std::string filepath);

    /// \brief Construct using an open file stream
    /// \param bytestream will be **consumed** by the object
    audio(std::ifstream & bytestream);

    /// \brief Construct using an existing byte-array
    /// \param bytearray should contain the audio data
    audio(std::vector<rapp::types::byte> bytearray);

    /// \brief Copy constructor
    audio(const audio &) = default;

    /// \brief Get audio as array of bytes
    std::vector<rapp::types::byte> bytearray() const;

    /// \brief Are audios same ?
    bool operator==(const audio & rhs) const;

    /// \brief Audios are not the same
    bool operator!=(const audio & rhs) const;

    /// \brief Assignment operator
    audio & operator=(const audio &) = default;

    /// \brief Save audio to filepath
    bool save(const std::string filepath);

    /// \brief Get the audio source
    std::string audio_source() const;

private:

    /// \brief Delete empty constructor    
    audio() = delete;

    /// \brief Copy the bytestream into the bytearray
    void read_bytes(std::ifstream & bytestream);

    /// \brief Actual bytes of audio file
    std::vector<rapp::types::byte> bytearray_;
};

/// OGG Class specialisation
class ogg : public audio
{
public:

    /// \brief Constructor from a file on disk
    ogg(const std::string filepath);  

    /// \brief Construct using an open file stream
    /// \param bytestream will be **consumed** by the object
    ogg(std::ifstream & bytestream);

    /// \brief Get the audio source
    std::string audio_source() const;

};

/// WAV Class specialisation for a single channel
class nao_single_channel_wav : public audio
{
public:

    /// \brief Construct from a file
    nao_single_channel_wav(const std::string filepath);

    /// \brief Construct using an open file stream
    /// \param bytestream will be **consumed** by the object
    nao_single_channel_wav(std::ifstream & bytestream);

    /// \brief Get audio source
    std::string audio_source() const;

};
/// WAV Class specialisation for quad channel
class nao_quad_channel_wav : public audio
{
public:

    /// \brief Construct from a file
    nao_quad_channel_wav(const std::string filepath);

    /// \brief Construct using an open file stream
    /// \param bytestream will be **consumed** by the object
    nao_quad_channel_wav(std::ifstream & bytestream);

    /// \brief Get the audio source
    std::string audio_source() const;

};
/// WAV Single channel 16Khz > Headset audio source
class microphone_wav : public audio
{
public:

    /// \brief Construct from a file
    microphone_wav(const std::string filepath);

    /// \brief Construct using an open file stream
    /// \param bytestream will be **consumed** by the object
    microphone_wav(std::ifstream & bytestream);

    /// \brief Construct using raw data
    /// \param bytearray is a vector of binary data
    microphone_wav(std::vector<rapp::types::byte> bytearray);

    /// \brief Get the audio source
    std::string audio_source() const;

};
}
}
#endif
