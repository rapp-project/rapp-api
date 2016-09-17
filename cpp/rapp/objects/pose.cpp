#include "pose.hpp"
namespace rapp{
namespace object {

pose::pose(
           rapp::object::point position,
           rapp::object::quaternion orientation
          )
: position_(position), orientation_(orientation)
{}

pose::pose(const json::const_iterator & pose)
{
    if (pose->find("position") == pose->end()){
       throw std::runtime_error("no position member in pose");
    }
    else {
        const auto position = pose->find("position"); //---
        position_ = rapp::object::point(position);
    }

    if (pose->find("orientation") == pose->end()){
       throw std::runtime_error("no orientation member in pose"); 
    }
    else {
        const auto orientation = pose->find("orientation");
        orientation_ = rapp::object::quaternion(orientation);
    }
          
}

bool pose::operator==(const pose & rhs) const
{
    return (this->position_ == rhs.get_position()) &&
           (this->orientation_ == rhs.get_orientation());
}

json::object_t pose::to_json() const
{
    json::object_t obj = {{"position", position_.to_json()}, {"orientation",orientation_.to_json()}};
    return obj;
}    

rapp::object::point pose::get_position() const
{
    return position_;
} 

rapp::object::quaternion pose::get_orientation() const
{
    return orientation_;
}

}
}
