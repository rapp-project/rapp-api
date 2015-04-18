#ifndef RAPP_OBJECT_ROBOT
#define RAPP_OBJECT_ROBOT
#include "Includes.ihh"

/**
 * @class robot
 * @brief Abstract Base Class which defines the interface for Robot capabilities
 * @version 0
 * @date 13-Feburary-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */

namespace rapp {
namespace object {

class robot
{
  public:
  
      /// Get Audio from robot's microphone
      virtual std::stream listen ( ) const = 0;
      
      /// Produce Audio from robot's speakers
      virtual void speak ( rapp::object::wav ) const = 0;
      
      /// And so on, We can do "Move", "Grab", "Email", "Skype" and so on
      
      
      /**
       * The idea here, is that I will create an Interface for all Robots (Humanoids, Service Bots, etc)
       * Finally, for each Specific Robot Model (e.g., NAO) we create one class that implements all that.
       * We can create intermediatte ABC's, or even non-ABC polymorphic classes, such as `Humanoid` which has legs and arms
       * or `ServiceBot` which only has one arm and tracked wheels.
       * 
       * This way, RAPP can function with Abstract Factories and Factory Patterns.
       * The RAPP::API becomes agnostic, and very high level, allowing rapid and fast development of RAPPS
       */
};


}
}
#endif