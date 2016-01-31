#ifndef RAPP_OBJECT_FACE
#define RAPP_OBJECT_FACE
#include "Includes.ihh"
namespace rapp {
namespace object {
/**
 * \class face
 * \brief class which should somehow encapsulate a face
 * \version 1
 * \date 13-Feburary-2015
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class face
{
public:
    /**
     * \brief Consruct using face coordinates (a rectangle)
     */
    face( 
          float top_left_x,
          float top_left_y,
          float top_left_z,
          float bottom_right_x,
          float bottom_right_y,
          float bottom_right_z
        )
    : top_left_x__(top_left_x),
      top_left_y__(top_left_y),
      top_left_z__(top_left_z),
      bottom_right_x__(bottom_right_x),
      bottom_right_y__(bottom_right_y),
      bottom_right_z__(bottom_right_z)
    {}
   
    /// Allow empty consructor
    face() = default;
    
    /// Copy constructor
    face(const face &) = default;
    
    /// Equality operator
    bool operator==(const face & rhs) const
    {
        return ( this->top_left_x__ == rhs.top_left_x__ &&
                 this->top_left_y__ == rhs.top_left_y__ &&
                 this->top_left_z__ == rhs.top_left_z__ &&
                 this->bottom_right_x__ == rhs.bottom_right_x__ &&
                 this->bottom_right_y__ == rhs.bottom_right_y__ &&
                 this->bottom_right_z__ == rhs.bottom_right_z__);
    }
    
private:
    float top_left_x__;
    float top_left_y__;
    float top_left_z__;
    float bottom_right_x__;
    float bottom_right_y__;
    float bottom_right_z__;
};
}
}
#endif
