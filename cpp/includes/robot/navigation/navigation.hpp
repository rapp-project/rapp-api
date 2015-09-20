#ifndef RAPP_ROBOT_NAVI
#define RAPP_ROBOT_NAVI
#include "Includes.ihh"
namespace rapp {
namespace robot {
/**
 * @class navigation
 * @brief Abstract Base Class (ABC) Interface for Navigation
 * @version 1
 * @date 20-September-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class navigation
{
  public:

    /// TODO: Describe each parameter and explain what it is.

    virtual void moveTo (float x, float y, float theta ) = 0;

    virtual void moveVel (float x, float y, float theta ) = 0;;

    virtual void moveHead (float yaw,float pitch ) = 0;;

    virtual void moveStop () = 0;;

    virtual void moveJoint ( std::string joint, float angle ) = 0;;
     
    virtual void removeStiffness ( std::string joint ) const = 0;;

    /// NOTE: parameter pose could be a class of its own,
    ///       because it encapsulates some kind of Robot State.
    virtual void takePredefinedPosture ( std::string pose ) = 0;;

    virtual void visOdom () = 0;;

    virtual void lookAtPoint ( float x, float y, float z ) = 0;;
};
}
}
#endif
