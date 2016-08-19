#ifndef RAPP_OBJECT_POSE
#define RAPP_OBJECT_POSE
#include "includes.ihh"
namespace rapp {
namespace object {

using namespace rapidjson;    
/**
 * \struct pose
 * \brief encapsulates robot pose vectors (position & orientation)
 * \version 0.7.0
 * \date 19 August 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
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

	/// \brief contruct using rapidJSON
    pose(const rapidjson::Value::ConstMemberIterator & iter)
    {
        auto it = iter->FindMember("position");
        this->position.point(it);
        
        auto it2 = iter->FindMember("orientation");
        this->orientation.quaternion(it2);
        
    }
    
    /// \brief Equality operator
    bool operator==(const pose & rhs) const
    {
		return (this->position == rhs.position) &&
			   (this->orientation == rhs.orientation);
    }

	/// \brief Serialization with rapidJSON
    template <typename W>
    void Serialize(W & writer) const
    {
        writer.StartObject();
        writer.String("position");
        position.Serialize(writer);

        writer.String("orientation");
        orientation.Serialize(writer);
        writer.EndObject();
    }
    
   	/// members
	rapp::object::point position;
	rapp::object::quaternion orientation;
};
}
}
#endif
