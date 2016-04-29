#ifndef RAPP_OBJECT_HUMAN
#define RAPP_OBJECT_HUMAN
#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \class human
 * \brief describes human coordinates
 * \version 0.6.0
 * \date April-2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class human
{
public:
    /// \brief Consruct using coordinates (a rectangle)
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
   
    /// Allow empty consructor
    human() = default;
    
    /// Copy constructor
    human(const human &) = default;
    
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
