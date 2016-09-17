#ifndef RAPP_OBJECT_POSE
#define RAPP_OBJECT_POSE
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
#include <rapp/objects/quaternion.hpp>
#include <rapp/objects/point.hpp>

namespace rapp {
namespace object {
/**
 * \struct pose
 * \brief encapsulates robot pose vectors (position & orientation)
 * \version 0.7.0
 * \date 19 August 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
class pose
{
public:
    /**
     * \brief Construct using position and orientation components
     * \param position is vector of position coordinates
     * \param orientation is vector of orientation (quaternion) coordinates
     */
    pose(
           rapp::object::point position,
           rapp::object::quaternion orientation
		);
    
    /// \brief Allow empty consructor
    pose() = default;
    
    /// \brief Copy constructor
    pose(const rapp::object::pose &) = default;

	/// \brief Contruct using 'json for modern c++'
    pose(const json::const_iterator & pose);
    
    /// \brief Equality operator
    bool operator==(const pose & rhs) const;
    
    /// \brief Method to pass information to a json object
    json::object_t to_json() const;
   
    /// \brief Method to get position_ parameter
    rapp::object::point get_position() const;

    /// \brief Method to get orientation_ param
    rapp::object::quaternion get_orientation() const;

private:
   	/// members
	rapp::object::point position_;
	rapp::object::quaternion orientation_;
};
}
}
#endif
