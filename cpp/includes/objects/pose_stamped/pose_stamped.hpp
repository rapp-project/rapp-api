#ifndef RAPP_OBJECT_POSE_STAMPED
#define RAPP_OBJECT_POSE_STAMPED
#include "includes.ihh"
namespace rapp {
namespace object {

using namespace rapidjson;    
/**
 * \struct pose_stamped
 * \brief encapsulate robot pose with message header component
 * \version 0.7.0
 * \date 19 August 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
struct pose_stamped
{
    /**
     * \brief Consruct using robot pose and message header component
     * \param header defines pose metadata (sequence, frame_id, stamp)
     * \param pose is robot pose definition (position & orientation)
     */
	pose_stamped( 
				  const rapp::object::pose_metadata header,
				  const rapp::object::pose pose
				)
    : header(header), pose(pose)
    {}
    
    /// \brief empty consructor
    pose_stamped() = default;
    
    /// \brief copy constructor
    pose_stamped(const rapp::object::pose_stamped &) = default;

    /// \brief construct using rapidJSON
    pose_stamped( const rapidjson::Value::ConstMemberIterator & iter)
    {
        auto it = iter->FindMember("header");
        this->header.pose_metadata(it);

        auto it2 = iter->FindMember("pose");
        this->pose.pose(it2);
    }

    
    /// \brief Equality operator
    bool operator==(const rapp::object::pose_stamped & rhs) const
    {
		return (this->header == rhs.header) &&
			   (this->pose == rhs.pose);
    }

	/// \brief Serialization with rapidJSON
    template <typename W>
    void Serialize(W & writer) const
    {
        writer.StartObject();
        writer.String("header");
        header.Serialize(writer);

        writer.String("pose");
        pose.Serialize(writer);
        writer.EndObject();
    }

	/// members
	rapp::object::pose_metadata header;
    rapp::object::pose pose;
};
}
}
#endif
