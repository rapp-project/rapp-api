#ifndef RAPP_OBJECT_FACE
#define RAPP_OBJECT_FACE
#include "Includes.ihh"

/**
 * @class face
 * @brief class which should somehow encapsulate a face
 * @version 1
 * @date 13-Feburary-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */

namespace rapp {
namespace object {

class face
{
  public:
    
    /**
     * @brief Consruct using face coordinates (a rectangle)
     */
    face ( 
            float top_left_x,
            float top_left_y,
            float bottom_right_x,
            float bottom_right_y
          )
    : top_left_x__( top_left_x ),
      top_left_y__( top_left_y ),
      bottom_right_x__( bottom_right_x ),
      bottom_right_y__( bottom_right_y )
    { }
    
    /**
     * @brief Consruct using face coordinates (a rectangle) and an optional label
     * @note label could be anything
    face ( 
            float top_left_x,
            float top_left_y,
            float bot_right_x,
            float bot_right_y,
            std::string label
         );
    */
    
    // Allow empty consructor
    face ( ) = default;
    
    /// Copy constructor
    face ( const face & ) = default;
    
    /// Assignment Constructor
    //face operator= ( const face & ) = default;
    
    /// Equality operator
    bool operator== ( const face & rhs ) const
    {
        return ( this->top_left_x__ == rhs.top_left_x__ &&
                 this->top_left_y__ == rhs.top_left_y__ &&
                 this->bottom_right_x__ == rhs.bottom_right_x__ &&
                 this->bottom_right_y__ == rhs.bottom_right_y__ );
    }
    
  private:
      
    float top_left_x__ = -1.;
    float top_left_y__ = -1.;
    float bottom_right_x__ = -1.;
    float bottom_right_y__ = -1.;
};


}
}
#endif