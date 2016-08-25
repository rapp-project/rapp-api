#ifndef RAPP_OBJECT_PLANNED_PATH
#define RAPP_OBJECT_PLANNED_PATH
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
 * \struct planned_path
 * \brief encapsulate collision free path planning service response
 * \version 0.6.0
 * \date 10-May-2016
 * \author Wojciech Dudek <dudekwa@gmail.com>
 */
class planned_path
{
public:
    /**
     * \brief construct using path header, definition of success/error code, vector of path points
     * \param plan_found is success/error code
     * \param planning_error is error description
     * \param path is vector of path pose_stamped
     */
	planned_path( 
				   uint8_t plan_found,
				   std::string planning_error,
				   std::vector<pose_stamped> path 
				);

    /// \brief empty constructor
    planned_path() = default;
    
    /// \brief copy constructor
    planned_path(const rapp::object::planned_path &) = default;
    
    /// \brief constructor using `json for modern C++`
    planned_path(const json & arg);
    
    /// \brief method to pass the information to a json object
    json to_json() const;
   
	/// \brief equality operator
    bool operator==(const rapp::object::planned_path & rhs) const;

    /// \brief method to get param plan_found_
    uint8_t get_plan() const;

    /// \brief method to get param planning_error
    std::string get_error() const;

    /// \brief method to get param path_
    std::vector<rapp::object::pose_stamped> get_path() const;

private:
	/// members
    uint8_t plan_found_;
    std::string planning_error_;
    std::vector<rapp::object::pose_stamped> path_;
};
}
}
#endif
