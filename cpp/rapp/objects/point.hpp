#ifndef RAPP_OBJECT_POINT
#define RAPP_OBJECT_POINT
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
 * \struct point
 * \brief encapsulate point position vector
 * \version 0.7.0
 * \date 19 August 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
class point
{
public:
    /**
     * \brief Construct using code coordinates (x,y,z)
     * \param x is x coordinate
     * \param y is y coordinate
     * \param z is z coordinate
     */
    point(double x, double y, double z);
    
    /// \brief Allow Empty Constructor
    point() = default;
    
    /// \brief Copy Constructor
    point(const rapp::object::point &) = default;

    /// \brief Construct using library "json for modern c++"
    point(const json::const_iterator & position);
   
    /// \brief method to pass the information to a json object
    json::object_t to_json() const;
   
    /// \brief Equality operator
    bool operator==(const rapp::object::point & rhs) const;
  
    /// members
	double x = 0;
    double y = 0;
    double z = 0;
};
}
}
#endif
