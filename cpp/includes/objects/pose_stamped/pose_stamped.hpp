#ifndef RAPP_OBJECT_POSE_STAMPED
#define RAPP_OBJECT_POSE_STAMPED
#include "includes.ihh"
namespace rapp {
namespace object {

/**
 * \struct pose_stamped
 * \brief encapsulate robot pose with message header component
 * \version 0.7.0
 * \date 19 August 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class pose_stamped
{
public:
    /**
     * \brief Consruct using robot pose and message header component
     * \param header defines pose metadata (sequence, frame_id, stamp)
     * \param pose is robot pose definition (position & orientation)
     */
	pose_stamped( 
				  const rapp::object::msg_metadata header,
				  const rapp::object::pose pose
				)
    : header_(header), pose_(pose)
    {}
    
    /// \brief empty consructor
    pose_stamped() = default;
    
    /// \brief copy constructor
    pose_stamped(const rapp::object::pose_stamped &) = default;

    /// \brief construct using rapidJSON
    pose_stamped( const json::const_iterator & stamped)
    {
        if(stamped->find("pose") == stamped->end()) {
            throw std::runtime_error("no param pose in pose_stamped");
        }
        else {
            const auto pose_it = stamped->find("pose");
            pose_ = rapp::object::pose(pose_it);
        }
        if(stamped->find("header") == stamped->end()) {
            throw std::runtime_error("no param header in pose_stamped");
        }
        else {
            const auto header_it = stamped->find("header");
            header_ = rapp::object::msg_metadata(header_it);
        }
    }

    json::object_t to_json() const
    {
        json::object_t values = {{"pose", pose_.to_json()}, 
                                 {"header", header_.to_json()}};
        return values;
    }

    rapp::object::msg_metadata get_header() const
    {
       return header_;
    }

    rapp::object::pose get_pose() const
    {
        return pose_;
    } 
    /// \brief Equality operator
    bool operator==(const rapp::object::pose_stamped & rhs) const
    {
		return (this->header_ == rhs.get_header()) &&
			   (this->pose_ == rhs.get_pose());
    }


private:
    /// members
	rapp::object::msg_metadata header_;
    rapp::object::pose pose_;
};
}
}
#endif
