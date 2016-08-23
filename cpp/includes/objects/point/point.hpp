#ifndef RAPP_OBJECT_POINT
#define RAPP_OBJECT_POINT
#include "includes.ihh"
namespace rapp {
namespace object {

/**
 * \struct point
 * \brief encapsulate point position vector
 * \version 0.7.0
 * \date 19 August 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
class point
{

public:
    /**
     * \brief Consruct using code coordinates (x,y,z)
     * \param x is x coordinate
     * \param y is y coordinate
     * \param z is z coordinate
     */
    point(double x, double y, double z);
    
    /// \brief Allow Empty Consructor
    point() = default;
    
    /// \brief Copy Conatructor
    point(const rapp::object::point &) = default;

    /// construct using library "json for modern c++"
    point(const json::const_iterator & position);
   
    json::object_t to_json() const;
   
    /// \brief Equality operator
    bool operator==(const rapp::object::point & rhs) const;
  
    /// members
	double x = 0;
    double y = 0;
    double z = 0;
};
}
}
#endif
