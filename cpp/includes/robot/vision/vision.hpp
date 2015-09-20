#ifndef RAPP_ROBOT_VISION
#define RAPP_ROBOT_VISION
#include "Includes.ihh"
namespace rapp {
namespace robot {
/**
 * @class vision
 * @brief Abstract Base Class (ABC) Interface for Vision
 * @version 1
 * @date 20-September-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class vision
{
  public:

    // NOTE: PLEASE do NOT include Headers in the namespace or Class Header.
    //       Any header you want, add into `Includes.ihh` your internal include header
    //       PLEASE also note that we need to be very careful of dependencies
    //       imported into the RAPP Project
    //       This is an ABC - do NOT import OpenCV here, do that in your
    //       implementation class, using the internal include header

    /// NOTE: What about format?
    virtual std::shared_pointr<rapp::object::picture> captureImage ( 
                                                                      std::string cameraId, 
                                                                      int cameraResolution 
                                                                   ) const = 0; 
    
};
}
}
#endif
