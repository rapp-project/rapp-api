#include "service_controller.hpp"

namespace rapp {
namespace cloud {

service_controller::service_controller(rapp::cloud::platform info)
: info_(info), 
  query_(info.address, info.port), 
  io_(), 
  resol_(io_),
  timeout_(1)
{
    derr_cb_ = std::bind(&service_controller::default_error_handler, 
                         this, 
                         std::placeholders::_1);
}

service_controller::service_controller(
                                        rapp::cloud::platform info,
                                        std::function<void(boost::system::error_code error)> error_handler
                                      )
: info_(info), 
  query_(info.address, info.port), 
  io_(), 
  resol_(io_), 
  error_(error_handler),
  timeout_(1)
{}

void service_controller::set_timeout(unsigned long int timeout)
{
    timeout_ = timeout;
}

void service_controller::stop()
{
    io_.stop();
}

void service_controller::default_error_handler(boost::system::error_code error) const
{
#if (!NDEBUG)
    std::cerr << "[error-message]: " << error.message() 
              << " [error-value]: " << error.value() << std::endl;
#endif
}

}
}
