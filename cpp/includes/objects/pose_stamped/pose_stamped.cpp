#include "pose_stamped.hpp"
namespace rapp {
namespace object {

pose_stamped::pose_stamped( 
                              const rapp::object::msg_metadata header,
                              const rapp::object::pose pose
                          )
: header_(header), pose_(pose)
{}

pose_stamped::pose_stamped(const json::const_iterator & stamped)
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

json::object_t pose_stamped::to_json() const 
{
    json::object_t values = {{"pose", pose_.to_json()}, 
                             {"header", header_.to_json()}};
    return values;
}

rapp::object::msg_metadata pose_stamped::get_header() const 
{
   return header_;
}

rapp::object::pose pose_stamped::get_pose() const 
{
    return pose_;
} 

bool pose_stamped::operator==(const rapp::object::pose_stamped & rhs) const
{
    return (this->header_ == rhs.get_header()) &&
           (this->pose_ == rhs.get_pose());
}


}
}

