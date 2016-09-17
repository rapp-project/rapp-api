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

/*
 * current rapp-platform uses a malformed JSON with
 * objects broken into two arrays, thus we can't construct
 * from a single iterator
 *
qr_code::qr_code(const json::const_iterator & qr_it)
{
      //First, find qr_centres
      if (qr_it->find("x") == qr_it->end()) {
          throw std::runtime_error("no x param in qr_code");  
      }
      else {
          centre_x__ = qr_it->find("x")->get<float>();
      }
      
      if (qr_it->find("y") == qr_it->end()) {
          throw std::runtime_error("no y param in qr_code");
      }
      else {
          centre_y__ = qr_it->find("y")->get<float>();
      }
      //Second, find qr_messages
       if (qr_it->find("message") == qr_it->end()) {
          throw std::runtime_error("no message in qr_code");
      }
      else {
        message__ = qr_it->find("message")->get<float>();
      }
}
*/

json::object_t qr_code::to_json() const
{
    json::object_t qr {{"x", centre_x__}, 
                       {"y", centre_y__},
                       {"message", message__}};

    return qr;
}


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
