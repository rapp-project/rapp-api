#ifndef RAPP_OBJECT_TIME
#define RAPP_OBJECT_TIME
#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \class time
 * \brief ??
 * \version 0.6.0
 * \date 10-May-2016
 * \author Wojciech Dudek <dudekwa@gmail.com>
 *
 * NOTE: this struct is not needed, we can use std::chrono or boost::posix_time
 *       furthemore, what is the logic behind using both seconds and nanoseconds?
 *       if this is a timestamp, then simply a unix timestamp with millisecond resolution
 *       should suffice.
 *       Last but not least, how do we construct this?
 *       using c++11, all we need is: std::chrono::system_clock::time_point
 *       which can be cast to nanoseconds, milliseconds, seconds, etc.
 *
 * TODO: suggest we provide a simple wrapper around std::chrono
 *       which enables json parsing/serialization
 */
struct time
{
    /**
     * \brief Consruct using second and nanosecond
     * \param sec is system second
     * \param nsec is system nanosecond
     */
    time(int32_t sec, int32_t nsec)
    : sec(sec), nsec(nsec)
    {}
    
    /// Allow Empty Consructor
    /// \WARNING shouldn't this use system calls to set sec and nsec?
    time() = default;
    
    /// Copy Conatructor
    time(const rapp::object::time &) = default;
    
    /// \brief Equality operator
    bool operator==(const rapp::object::time & rhs) const
    {
		return (this->sec == rhs.sec) &&
			   (this->nsec == rhs.nsec);
    }

	/// \brief convert *this* into a boost tree
	boost::property_tree::ptree treefy() const
	{
		boost::property_tree::ptree tree;
        tree.put("sec", sec);
        tree.put("nsec", nsec);
		return tree;
	}

	/// members
	uint32_t sec = 0;
    uint32_t nsec = 0;
};
}
}
#endif
