#ifndef RAPP_OBJECT_QUATERNION
#define RAPP_OBJECT_QUATERNION
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
 * \struct quaternion
 * \brief class which encapsulate quaternion vector
 * \version 0.7.0
 * \date 19 August 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
class quaternion
{
public:
    /**
     * \brief Consruct using code coordinates (x,y,z,w)
     * \param x is quaternion x component
     * \param y is quaternion y component
     * \param z is quaternion z component
     * \param w is quaternion w (NOTE: angle theta?)
     */
	quaternion(double x, double y, double z, double w);
    
    /// \brief empty consructor
    quaternion() = default;
    
    /// \brief copy constructor
    quaternion(const rapp::object::quaternion &) = default;

	/// construct using library "json for modern c++"
    quaternion(const json::const_iterator & orientation);
    
    json::object_t to_json() const;
       
    /// \brief equalit-> operator
    bool operator==(const rapp::object::quaternion & rhs) const;
	
    /// members
    double x = 0;
    double y = 0;
    double z = 0;
    double w = 1;
};
}
}
#endif
