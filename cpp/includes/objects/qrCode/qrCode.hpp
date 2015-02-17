#ifndef RAPP_OBJECT_QRCODE
#define RAPP_OBJECT_QRCODE
#include "Includes.ihh"

namespace rapp {
namespace object {

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
    
    /**
     * @brief Consruct using code coordinates (a rectangle) and a label (URL, email, string, etc)
     * @param centre_x is coordinate
     * @param centre_y is coordinate
     * @param label is message embedded in QR
     */
    qrCode ( 
              float centre_x,
              float centre_y,
              std::string label
            )
    : centre_x__ ( centre_x ),
      centre_y__ ( centre_y )
    { }
    
    /// Allow Empty Consructor
    qrCode ( ) = default;
    
    /// Copy Conatructor
    qrCode ( const qrCode & ) = default;
    
    /// Assignment Constructor
    //qrCode operator= ( const qrCode & ) = default;
    
    /** 
     * @brief Equality operator
     * @note only the message is compared (insensitive case), not the coordinates!
     */
    bool operator== ( const qrCode & rhs ) const
    {
        return boost::iequals ( this->message__, rhs.message__ );
    }

    /**
     *@brief Get the qr Label
     */
    std::string label ( ) const
    {
	return message__;
    }
    
  private:
      
      float centre_x__ = -1;
      
      float centre_y__ = -1;
      
      std::string message__ ;
      
};
}
}
#endif
