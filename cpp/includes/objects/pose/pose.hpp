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
    : position_(position), orientation_(orientation)
    {}
    
    /// \brief allow empty consructor
    pose() = default;
    
    /// \brief copy constructor
    pose(const rapp::object::pose &) = default;

	/// \brief contruct using rapidJSON
    pose(const json::const_iterator & pose)
    {
        if (pose->find("position") == pose->end()){
           throw std::runtime_error("no position member in pose");
        }
        else {
            const position = pose->find("position"); //---
            position_ = rapp::object::point(position);
        }

        if (pose->find("orientation") == pose->end()){
           throw std::runtime_error("no orientation member in pose"); 
        }
        else {
            const orientation = pose->find("orientation");
            orientation_ = rapp::object::quaternion(orientation);
        }
              
    }
    
    /// \brief Equality operator
    bool operator==(const pose & rhs) const
    {
		return (this->position == rhs.position) &&
			   (this->orientation == rhs.orientation);
    }

    json::object_t to_json() const
    {
        json::object_t pos = position_.to_json();
        json::object_t ori = orientation_.to_json();
        json::object_t obj = {{"pose", pos, ori}};
        return obj;
    }    
    
   	/// members
	rapp::object::point position_;
	rapp::object::quaternion orientation_;
};
}
}
#endif
