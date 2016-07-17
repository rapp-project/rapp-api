#ifndef RAPP_OBJECT_PLANNED_PATH
#define RAPP_OBJECT_PLANNED_PATH
#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \struct planned_path
 * \brief encapsulate collision free path planning service response
 * \version 0.6.0
 * \date 10-May-2016
 * \author Wojciech Dudek <dudekwa@gmail.com>
 */
struct planned_path
{
    /**
     * \brief construct using path header, definition of success/error code, vector of path points
     * \param plan_found is success/error code
     * \param planning_error is error description
     * \param path is vector of path pose_stamped
     */
	planned_path( 
				   uint8_t plan_found,
				   std::string planning_error,
				   std::vector<pose_stamped> path
				)
    : header(header), plan_found(plan_found),
      planning_error(planning_error), path(path)
    {}
    
    /// \brief empty constructor
    planned_path() = default;
    
    /// \brief copy constructor
    planned_path(const rapp::object::planned_path &) = default;
    
	/// \brief equality operator
    bool operator==(const rapp::object::planned_path & rhs) const
    {
		return (this->header == rhs.header) &&
			   (this->plan_found == rhs.plan_found) &&
			   (this->planning_error == rhs.planning_error) &&
			   (this->path == rhs.path);
    }

	/// members
    uint8_t plan_found;
    std::string planning_error;
    std::vector<rapp::object::pose_stamped> path;
};
}
}
#endif
