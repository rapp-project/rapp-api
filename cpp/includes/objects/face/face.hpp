#ifndef RAPP_OBJECT_FACE
#define RAPP_OBJECT_FACE
#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \class face
 * \brief describes a face coordinate (cartesian)
 * \version 0.6.0
 * \date April 2016
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
    
    /// Equality operator
    bool operator==(const face & rhs) const
    {
        return ( this->top_left_x__ == rhs.top_left_x__ &&
                 this->top_left_y__ == rhs.top_left_y__ &&
                 this->bottom_right_x__ == rhs.bottom_right_x__ &&
                 this->bottom_right_y__ == rhs.bottom_right_y__);
    }

    float cx() const {
        return (top_left_x__ + bottom_right_x__) / 2;
    }

    float cy() const {
        return (top_left_y__ + bottom_right_y__) / 2;
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
