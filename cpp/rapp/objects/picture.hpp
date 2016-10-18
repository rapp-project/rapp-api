#ifndef RAPP_OBJECT_PICTURE
#define RAPP_OBJECT_PICTURE
#include "includes.ihh"
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
#include <rapp/objects/globals.hpp>

namespace rapp {
namespace object {
/**
 * \class picture
 * \brief class which wraps around raw bytes of a picture
 * \version 0.7.0
 * \date August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class picture
{
public:
    /// \brief Construct from a file-path
    picture(const std::string filepath);
        
    /// \brief Construct using an open file stream
    picture(std::ifstream & bytestream);

    /// \brief Constructor using the raw bytes of a file
    picture(std::vector<rapp::types::byte> data);

    /// \brief Copy constructor
    picture(const picture &) = default;
    
    /// \brief Assignment operator
    picture & operator=(const picture &) = default;

    /// \brief Picture equality
    bool operator==(const picture & rhs) const;

    /// \brief Not picture equality
    bool operator!=(const picture & rhs) const;

    /// \brief Get picture as array of bytes
    std::vector<rapp::types::byte> bytearray() const;

    /// \brief Get image type (JPG/PNG supported)
    std::string type() const;

    /// \brief Save picture to filepath
    bool save(const std::string filepath);

private:
	typedef char byte;

    /// \brief Delete empty constructor    
    picture() = delete;

    /// \brief Parse the bytestream into the bytearray
    void opencb_(std::ifstream & bytestream);
        
    /// Members
    std::vector<rapp::types::byte> bytearray_;
    std::string imgtype_;
};
}
}
#endif
