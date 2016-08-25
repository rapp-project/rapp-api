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
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
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
        )
    : top_left_x__(top_left_x),
      top_left_y__(top_left_y),
      bottom_right_x__(bottom_right_x),
      bottom_right_y__(bottom_right_y)
    {}
   
    /// Allow empty constructor
    human() = default;
    
    /// Copy constructor
    human(const human &) = default;
    
    /// \brief constructor using `json for modern C++`
    human(const json::const_iterator & human_it)
    {
       if (human_it->find("up_left_point") == human_it->end()){
          throw std::runtime_error("no up left point param in human");
       }
       else {
          // Look for params x and y in up_left_point
          auto coord_it = human_it->find("up_left_point");
          
          if (coord_it->find("x") == coord_it->end()){
              throw std::runtime_error("no x param in up left point");  
          }
          else {
              top_left_x__ = coord_it->find("x")->get<float>();
          }
          
          if (coord_it->find("y") == coord_it->end()){
              throw std::runtime_error("no y param in up left point");
          }
          else {
              top_left_y__ = coord_it->find("y")->get<float>();
          }
       }

      if (human_it->find("down_right_point") == human_it->end()){
         throw std::runtime_error("no down right point param in human");
      }
      else {
          auto coord_it = human_it->find("down_right_point");
          
          if (coord_it->find("x") == coord_it->end()){
              throw std::runtime_error("no x param in down right point");  
          }
          else {
              bottom_right_x__ = coord_it->find("x")->get<float>();
          }

          if (coord_it->find("y") == coord_it->end()){
              throw std::runtime_error("no y param in down right point");  
          }
          else {
              bottom_right_y__ = coord_it->find("y")->get<float>();
          }
      }

    }

    /// \brief method to pass the information to json object
    json::object_t to_json() const
    {
        json::object_t value_up = {{"x", top_left_x__}, 
                                   {"y", top_left_y__}};

        json::object_t value_dowm = {{"x", bottom_right_x__}, 
                                     {"y", bottom_right_y__}};

        json::object_t both = {{"up_left_point", value_up}, 
                               {"bottom_right_point", value_dowm}};

        json::object_t human_json = {{"human", both}};

        return human_json;
    }

    /// Equality operator
    bool operator==(const human & rhs) const
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
