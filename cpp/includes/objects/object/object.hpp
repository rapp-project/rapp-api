#ifndef RAPP_OBJECT_OBJECT
#define RAPP_OBJECT_OBJECT
#include "includes.ihh"
namespace rapp {
namespace object {
        
/**
 * \class object
 * \brief describes an object detected on picture
 * \version 0.6.0
 * \date May 2016
 * \author Maciej Stefańczyk <m.stefancyk@elka.pw.edu.pl>
 */
class object
{
public:
    /// \brief Consruct using object properties
    object( 
          const std::string & name_,
          const point center_,
          float score_
        )
    : name__(name_), center__(center_), score__(score_)
    {}
   
    /// Allow empty consructor
    object() = default;
    
    /// Copy constructor
    object(const object &) = default;
    
    /// Equality operator
    bool operator==(const object & rhs) const
    {
        return ( this->name__ == rhs.name__ );
    }

    point center() const {
        return center__;
    }
    
    std::string name() const {
        return name__;
    }
    
    float score() const {
        return score__;
    }
    
private:
    std::string name__;
    point center__;
    float score__;
};
}
}
#endif /* RAPP_OBJECT_OBJECT */
