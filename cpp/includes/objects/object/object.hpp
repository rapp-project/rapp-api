#ifndef RAPP_OBJECT_OBJECT
#define RAPP_OBJECT_OBJECT
#include "Includes.ihh"

/**
 * @class object
 * @brief class which should somehow encapsulate an object
 * @version 1
 * @date 02-July-2015
 * @author Maciej Stefańczyk <stefanczyk.maciek@gmail.com>
 */

namespace rapp {
namespace object {

class object
{
  public:
    
    /**
     * @brief Consruct using object name and recognition score
     */
    object ( std::string name, float score )
    : 
    name__( name ),
    score__( score )
    { }
    
    
    // Allow empty consructor
    object ( ) = default;
    
    /// Copy constructor
    object ( const object & ) = default;
    
    /// Equality operator
    bool operator== ( const object & rhs ) const
    {
        return ( this->name__ == rhs.name__ &&
                 this->score__ == rhs.score__ );
    }
    
    const std::string & name() const {return name__;}
    
  private:
    
    std::string name__ = "Unknown";
    float score__ = -1.;
};


}
}
#endif
