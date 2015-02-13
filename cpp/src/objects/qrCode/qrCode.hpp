#ifndef RAPP_OBJECT_QRCODE
#define RAPP_OBJECT_QRCODE
#include "Includes.ihh"

namespace rapp {
namespace objects {

/**
 * @class qrCode
 * @brief class which should encapsulate a QR code
 * @version 1
 * @date 13-February-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */

class qrCode
{
  public:
    
    qrCode ( ) = delete;
    
    /**
     * @brief Consruct using code coordinates (a rectangle) and a label (URL, email, string, etc)
     */
    qrCode ( 
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