#ifndef RAPP_OBJECT_POSE
#define RAPP_OBJECT_POSE
#include "includes.ihh"
namespace rapp {
namespace object {

/**
 * \struct pose
 * \brief encapsulates robot pose vectors (position & orientation)
 * \version 0.7.0
 * \date 19 August 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
class pose
{
public:
    /**
     * \brief consruct using position and orientation components
     * \param position is vector of position coordinates
     * \param orientation is vector of orientation (quaternion) coordinates
     */
    pose(
           rapp::object::point position,
           rapp::object::quaternion orientation
		);
    
    /// \brief allow empty consructor
    pose() = default;
    
    /// \brief copy constructor
    pose(const rapp::object::pose &) = default;

	/// \brief contruct using rapidJSON
    pose(const json::const_iterator & pose);
    
    /// \brief Equality operator
    bool operator==(const pose & rhs) const;
    
    json::object_t to_json() const;
   
    rapp::object::point get_position() const;

    rapp::object::quaternion get_orientation() const;

private:
   	/// members
	rapp::object::point position_;
	rapp::object::quaternion orientation_;
};
}
}
#endif
