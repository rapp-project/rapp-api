#ifndef RAPP_OBJECT_FACE
#define RAPP_OBJECT_FACE
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
 * \class face
 * \brief describes a face coordinate (cartesian)
 * \version 0.7.0
 * \date August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class face
{
public:
    /// \brief Consruct using face coordinates (a rectangle)
    face( 
          float top_left_x,
          float top_left_y,
          float bottom_right_x,
          float bottom_right_y
        )
    : top_left_x__(top_left_x),
      top_left_y__(top_left_y),
      bottom_right_x__(bottom_right_x),
      bottom_right_y__(bottom_right_y)
    {}
   
    /// Allow empty consructor
    face() = default;
    
    /// Copy constructor
    face(const face &) = default;

    /// \brief constuct using a rapid_json

    
    /// Equality operator
    bool operator==(const face & rhs) const
    {
        return ( this->top_left_x__ == rhs.top_left_x__ &&
                 this->top_left_y__ == rhs.top_left_y__ &&
                 this->bottom_right_x__ == rhs.bottom_right_x__ &&
                 this->bottom_right_y__ == rhs.bottom_right_y__);
    }
    
private:
    float top_left_x__;
    float top_left_y__;
    float bottom_right_x__;
    float bottom_right_y__;
};
}
}
#endif
