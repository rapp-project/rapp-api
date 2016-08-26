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
    /// \brief Construct using face coordinates (a rectangle)
    face( 
          float top_left_x,
          float top_left_y,
          float bottom_right_x,
          float bottom_right_y
        );
  
    /// Allow empty constructor
    face() = default;
    
    /// Copy constructor
    face(const face &) = default;

    /// \brief constructor using `json for modern C++`
    face(const json::const_iterator & face_it);
   
    /// \brief method to pass the information to a json format
    json::object_t to_json() const;

    /// Equality operator
    bool operator==(const face & rhs) const;
    
    /// \brief method to get the top_left_x__ param
    float get_left_x() const;

    /// \brief method to get the top_left_y__ param
    float get_left_y() const;

    /// \brief method to get the bottom_right_x__ param
    float get_right_x() const;

    /// \brief method to get the bottom_right_y__param
    float get_right_y() const;

private:

    /// \brief method to find the up_left_point information from json data
    void up_left_point(const json::const_iterator & coord_it);

    /// \brief method to find the down_right_point information from json data
    void down_right_point(const json::const_iterator & coord_it);

    /// members
    float top_left_x__;
    float top_left_y__;
    float bottom_right_x__;
    float bottom_right_y__;
};
}
}
#endif
