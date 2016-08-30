#ifndef RAPP_OBJECT_TIME
#define RAPP_OBJECT_TIME
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

namespace rapp {
namespace object {

/**
 * \struct time
 * \brief wraps around a time-stamp (UNIX Epoch)
 * \version 0.7.0
 * \date 19 August 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
class time
{
public:
    /**
     * \brief Consruct using second and nanosecond
     * \param sec is system second
     * \param nsec is system nanosecond
     */
    time(std::chrono::nanoseconds timepoint);

    /// Allow Empty Consructor
    time() = default;
    
    /// Copy Constructor
    time(const rapp::object::time &) = default;

    /// Construct using library "json for modern c++"
    time(const json::const_iterator & stamp);

    /// \brief method to pass all the data into a json object
    json::object_t to_json() const;
    
    /// \brief Equality operator
    bool operator==(const rapp::object::time & rhs) const;
    
    /// \brief return seconds elapsed since UNIX Epoch
	uint32_t seconds() const;

	/// \brief return nanoseconds elapsed since UNIX Epoch
	uint32_t nanoseconds() const;

private:

    uint32_t seconds_;
    uint32_t nanoseconds_;
};
}
}
#endif
