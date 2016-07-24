#ifndef RAPP_OBJECT_POINT
#define RAPP_OBJECT_POINT
#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \struct point
 * \brief encapsulate point position vector
 * \version 0.6.0
 * \date July-24-2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
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

	/// \brief construct from a boost JSON ptree::value_type
	point(const boost::property_tree::ptree::value_type json)
	{
		for (auto it = json.second.begin(); it != json.second.end(); ++it) {
			if (it->first == "x") {
				this->x = it->second.get_value<uint32_t>();
			}
			else if (it->first == "y") {
				this->y = it->second.get_value<uint32_t>();
			}
			else if (it->first == "z") {
				this->z = it->second.get_value<uint32_t>();
			}
		}
	}
    
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
