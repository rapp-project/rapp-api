#ifndef RAPP_OBJECT_POSE
#define RAPP_OBJECT_POSE
#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \struct pose
 * \brief encapsulates robot pose vectors (position & orientation)
 * \version 0.6.0
 * \date 10-May-2016
 * \author Wojciech Dudek <dudekwa@gmail.com>
 */
struct pose
{
    /**
     * \brief consruct using position and orientation components
     * \param position is vector of position coordinates
     * \param orientation is vector of orientation (quaternion) coordinates
     */
    pose(
           rapp::object::point position,
           rapp::object::quaternion orientation
		)
    : position(position), orientation(orientation)
    {}
    
    /// \brief allow empty consructor
    pose() = default;
    
    /// \brief copy constructor
    pose(const rapp::object::pose &) = default;
    
    /// \brief Equality operator
    bool operator==(const pose & rhs) const
    {
		return (this->position == rhs.position) &&
			   (this->orientation == rhs.orientation);
    }

	/// \brief convert *this* into a boost tree
	boost::property_tree::ptree treefy() const
	{
		boost::property_tree::ptree tree;
        tree.add_child("position", position.treefy());
		tree.add_child("orientation", orientation.treefy());
		return tree;
	}

	/// members
	rapp::object::point position;
	rapp::object::quaternion orientation;
};
}
}
#endif
