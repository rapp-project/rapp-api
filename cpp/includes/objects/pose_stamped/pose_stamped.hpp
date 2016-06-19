#ifndef RAPP_OBJECT_POSE_STAMPED
#define RAPP_OBJECT_POSE_STAMPED
#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \struct pose_stamped
 * \brief encapsulate robot pose with message header component
 * \version 0.6.0
 * \date 10-May-2016
 * \author Wojciech Dudek <dudekwa@gmail.com>
 */
struct pose_stamped
{
    /**
     * \brief Consruct using robot pose and message header component
     * \param header defines pose metadata (sequence, frame_id, stamp)
     * \param pose is robot pose definition (position & orientation)
     */
	pose_stamped( 
				  rapp::object::header header,
				  rapp::object::pose pose
				)
    : header(header), pose(pose)
    {}
    
    /// \brief empty consructor
    pose_stamped() = default;
    
    /// \brief copy constructor
    pose_stamped(const rapp::object::pose_stamped &) = default;

    /// \brief Equality operator
    bool operator==(const rapp::object::pose_stamped & rhs) const
    {
		return (this->header == rhs.header) &&
			   (this->pose == rhs.pose);
    }

	/// \brief convert *this* into a boost tree
	boost::property_tree::ptree treefy() const
	{
		boost::property_tree::ptree tree;
        tree.add_child("header", header.treefy());
		tree.add_child("pose", pose.treefy());
		return tree;
	}

	/// members
	rapp::object::header header;
    rapp::object::pose pose;
};
}
}
#endif
