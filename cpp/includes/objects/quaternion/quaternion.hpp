#ifndef RAPP_OBJECT_QUATERNION
#define RAPP_OBJECT_QUATERNION
#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \struct quaternion
 * \brief class which encapsulate quaternion vector
 * \version 0.6.0
 * \date July-24-2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
struct quaternion
{
    /**
     * \brief Consruct using code coordinates (x,y,z,w)
     * \param x is quaternion x component
     * \param y is quaternion y component
     * \param z is quaternion z component
     * \param w is quaternion w (NOTE: angle theta?)
     */
	quaternion(float x, float y, float z, float w)
    : x(x), y(y), z(z), w(w)
    {}
    
    /// \brief empty consructor
    quaternion() = default;
    
    /// \brief copy constructor
    quaternion(const rapp::object::quaternion &) = default;

	/// \brief construct from a boost JSON ptree::value_type
	quaternion(const boost::property_tree::ptree::value_type json)
	{
		for (auto it = json.second.begin(); it != json.second.end(); ++it) {
			if (it->first == "x") {
				this->x = it->second.get_value<uint32_t>();
			}
			else if (it->first == "y") {
				this->y = it->second.get_value<uint32_t>();
			}
			else if (it->first == "z") {
				this->y = it->second.get_value<uint32_t>();
			}
			else if (it->first == "w") {
				this->y = it->second.get_value<uint32_t>();
			}
		}
	}

    quaternion(const boost::property_tree::ptree & pt) {
        x = pt.get<float>("x");
        y = pt.get<float>("y");
        z = pt.get<float>("z");
        w = pt.get<float>("w");
    }
    
    /// \brief equalit-> operator
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
		tree.put("z", z);
		tree.put("w", w);
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
