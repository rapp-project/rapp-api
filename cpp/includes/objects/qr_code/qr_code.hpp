#ifndef RAPP_OBJECT_QRCODE
#define RAPP_OBJECT_QRCODE
#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \class qrCode
 * \brief class which should encapsulate a QR code
 * \version 0.7.0
 * \date 25 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class qr_code
{
public:
    /**
     * \brief Construct using code coordinates (a rectangle) and a label (URL, email, string, etc)
     * \param centre_x is coordinate
     * \param centre_y is coordinate
     * \param label is message embedded in QR
     */
    qr_code( 
              float centre_x,
              float centre_y,
              std::string label
           )
    : centre_x__(centre_x),
      centre_y__(centre_y),
      message__(label)
    {}
    
    /// Allow Empty Constructor
    qr_code() = default;
    
    /// Copy Constructor
    qr_code(const qr_code &) = default;
    
    /** 
     * Equality operator
     * \note the message is case insensitvely compared
     */
    bool operator==(const qr_code & rhs) const
    {
        return boost::iequals(this->message__, rhs.message__);
    }

    /// \brief Get the qr Label
    std::string label() const
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
