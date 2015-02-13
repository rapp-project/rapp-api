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
    
    // No empty consructor
    face ( ) = delete;
    
    /**
     * @brief Consruct using face coordinates (a rectangle)
     */
    face ( 
            float top_left_x,
            float top_left_y,
            float bot_right_x,
            float bot_right_y
         );
    
    /**
     * @brief Consruct using face coordinates (a rectangle) and an optional label
     */
    face ( 
            float top_left_x,
            float top_left_y,
            float bot_right_x,
            float bot_right_y,
            std::string label
         );
    
};


}
}
#endif