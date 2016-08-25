#ifndef RAPP_OBJECT_POSE_STAMPED
#define RAPP_OBJECT_POSE_STAMPED
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
 * \struct pose_stamped
 * \brief encapsulate robot pose with message header component
 * \version 0.7.0
 * \date 19 August 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class pose_stamped
{
public:
    /**
     * \brief Consruct using robot pose and message header component
     * \param header defines pose metadata (sequence, frame_id, stamp)
     * \param pose is robot pose definition (position & orientation)
     */
	pose_stamped( 
				  const rapp::object::msg_metadata header,
				  const rapp::object::pose pose
				);
    
    /// \brief empty consructor
    pose_stamped() = default;
    
    /// \brief copy constructor
    pose_stamped(const rapp::object::pose_stamped &) = default;

    /// \brief construct using `json for modern c++`
    pose_stamped(const json::const_iterator & stamped);

    /// \brief method to pass the information into a json object
    json::object_t to_json() const;

    /// \brief method to get the param header_
    rapp::object::msg_metadata get_header() const; 

    /// \brief method to get the param pose_
    rapp::object::pose get_pose() const;

    /// \brief Equality operator
    bool operator==(const rapp::object::pose_stamped & rhs) const;

private:
    /// members
	rapp::object::msg_metadata header_;
    rapp::object::pose pose_;
};
}
}
#endif
