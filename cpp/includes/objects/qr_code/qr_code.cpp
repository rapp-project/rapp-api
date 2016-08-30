#include "qr_code.hpp"
namespace rapp {
namespace object {

qr_code::qr_code( 
          float centre_x,
          float centre_y,
          std::string label
       )
: centre_x__(centre_x),
  centre_y__(centre_y),
  message__(label)
{}

bool qr_code::operator==(const qr_code & rhs) const
{
    return boost::iequals(this->message__, rhs.message__);
}

std::string qr_code::label() const
{
    return message__;
}

}
}
