#ifndef RAPP_OBJECT_POINT
#define RAPP_OBJECT_POINT
#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \struct point
 * \brief encapsulate point position vector
 * \version 0.6.0
 * \date 10-May-2016
 * \author Wojciech Dudek <dudekwa@gmail.com>
 *
 * NOTE: shouldn't this be called "coordinate" or "cartesian"
 *       "point" is not a clear description
 */
struct point
{
    /**
     * \brief Consruct using code coordinates (x,y,z)
     * \param x is x coordinate
     * \param y is y coordinate
     * \param z is z coordinate
     */
    point(float x, float y, float z)
    : x(x), y(y), z(z)
    {}
    
    /// \brief Allow Empty Consructor
    point() = default;
    
    /// \brief Copy Conatructor
    point(const rapp::object::point &) = default;
    
    /// \brief Equality operator
    bool operator==(const rapp::object::point & rhs) const
    {
		return (this->x == rhs.x) &&
			   (this->y == rhs.y) &&
			   (this->z == rhs.z);
    }

	/// \brief convert *this* into a boost tree
	boost::property_tree::ptree treefy() const
	{
		boost::property_tree::ptree tree;
        tree.put("x", x);
        tree.put("y", y);
		tree.put("z", z);
		return tree;
	}

	/// members
	float x = 0;
    float y = 0;
    float z = 0;
};
}
}
#endif
