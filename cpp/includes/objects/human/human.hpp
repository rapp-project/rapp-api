#ifndef RAPP_OBJECT_HUMAN
#define RAPP_OBJECT_HUMAN
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
 * \class human
 * \brief describes human coordinates
 * \version 0.7.0
 * \date 25 August-2016
 * \author Maria Ramos  <m.ramos@ortelio.co.uk>
 */
class human
{
public:
    /// \brief Construct using coordinates (a rectangle)
    human( 
          float top_left_x,
          float top_left_y,
          float bottom_right_x,
          float bottom_right_y
        );
   
    /// Allow empty constructor
    human() = default;
    
    /// Copy constructor
    human(const human &) = default;
    
    /// \brief constructor using `json for modern C++`
    human(const json::const_iterator & human_it);

    /// \brief method to pass the information to json object
    json::object_t to_json() const;

    /// Equality operator
    bool operator==(const human & rhs) const;
   
    /// \brief method to get top_left_x__ param
    float get_left_x() const;

    /// \brief method to get top_left_y__ param
    float get_left_y() const;

    /// \brief method to get bottom_right_x__ param
    float get_right_x() const;

    /// \brief method to get bottom_right_y__ param
    float get_right_y() const;


private:

    /// \brief method to find component up_left_point in json data
    void up_left_point(const json::const_iterator & coord_it);

    /// \brief method to find component down_right_point in json data
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
