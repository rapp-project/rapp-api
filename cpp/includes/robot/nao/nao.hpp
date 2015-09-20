#ifndef RAPP_ROBOT_NAO
#define RAPP_ROBOT_NAO
#include "Includes.ihh"
namespace rapp {
namespace robot {
/**
 * @class nao
 * @brief Implementation Class for Aldearan's NAO robot
 * @version 1
 * @date 20-September-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class nao 
    : public proto, 
      //public communication, 
      public navigation, 
      public vision
{
  public:

    /// Constructor ?
    nao ( ) = default;

    std::string ruid() const;

    std::string model() const;

    // If you want communication, inhert from rapp::robot::communication
    // and then implement all virtual functions for NAO

    // from ABC rapp::robot::navigation
    void moveTo ( 
                  float x,
                  float y,
                  float z
                );

    void moveVel (
                   float x,
                   float y,
                   float z
                 );

    void move Head (
                     float yaw,
                     float pitch
                   );

    void moveStop ( );

    void moveJoint ( 
                     std::string joint,
                     float angle
                   );

    void removeStiffness ( std::string joint );
                        
    void takePredefinedPosture ( std::string pose );

    void visOdom ( );

    void lookAtPoint (
                        float x,
                        float y,
                        float z
                     );

    // from ABC rapp::robot::vision
    std::shared_pointr<rapp::object::picture> captureImage ( 
                                                              std::string cameraId, 
                                                              int cameraResolution 
                                                           ) const; 

    // You have to create a nao.cpp file
    // where all those methods are implemented
    // Try to keep dependencies to a minimal level.
    // If you need direct ROS interaction we need to discuss this.
    // as RAPP-API is ROS Independant (when it comes to linking)
  
  private:

    // If you need private members, or protected - go ahead and put them
    // here
};
}
}
#endif
