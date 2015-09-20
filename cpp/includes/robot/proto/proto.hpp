#ifndef RAPP_ROBOT_PROTO
#define RAPP_ROBOT_PROTO
#include "Includes.ihh"
namespace rapp {
namespace robot {
/**
 * @class proto
 * @brief Abstract Base Class (ABC) Interface Prototype for all Robots
 * @version 1
 * @date 20-September-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class proto
{
  public:
  
      /// Get Robot's Unique ID
      virtual std::string ruid () const = 0;
      
      /// Get Robot's Model
      virtual std::string model () const = 0;
      
      /// Get or Set Robot's (Function) any kind of getter/setter
      /// Then, implement it in the class that defines that robot.
      
      /// Extra Functionality can be found in other classes: Communication, Navigation, Vision.
      /// Use multiple-polymorphic inheritance in order to define your robot's behaviour and functionality
      /// We will Compile a SEPERATE Library for specific Robots (not librapp.so) 
};
}
}
#endif
