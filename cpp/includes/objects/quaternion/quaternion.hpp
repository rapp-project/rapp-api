#ifndef RAPP_OBJECT_QUATERNION
#define RAPP_OBJECT_QUATERNION
#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \struct quaternion
 * \brief class which encapsulate quaternion vector
 * \version 0.6.0
 * \date 10-May-2016
 * \author Wojciech Dudek <dudekwa@gmail.com>
 */
struct quaternion
{
    /**
     * \brief Consruct using code coordinates (x,y,z,w)
     * \param x is quaternion x component
     * \param y is quaternion y component
     * \param z is quaternion z component
     * \param w is quaternion w component
     */
	quaternion(float x, float y, float z, float w)
    : x(x), y(y), z(z), w(w)
    {}
    
    /// \brief empty consructor
    quaternion() = default;
    
    /// \briefcopy constructor
    quaternion(const rapp::object::quaternion &) = default;
    
    /// \brief equality operator
    bool operator==(const rapp::object::quaternion & rhs) const
    {
		return (this->x == rhs.x) &&
			   (this->y == rhs.y) && 
			   (this->z == rhs.z) &&
			   (this->w == rhs.w);
    }

	/// \brief convert *this* into a boost tree
	boost::property_tree::ptree treefy() const
	{
		boost::property_tree::ptree tree;
        tree.put("x", x);
        tree.put("y", y);
		tree.put("z", y);
		tree.put("w", z);
		return tree;
	}

	/// members
	float x = 0;
    float y = 0;
    float z = 0;
    float w = 1;
};
}
}
#endif
