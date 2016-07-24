#ifndef RAPP_OBJECT_TIME
#define RAPP_OBJECT_TIME
#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \struct time
 * \brief wraps around a time-stamp (UNIX Epoch)
 * \version 0.6.0
 * \date 24-7-2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
struct time
{
    /**
     * \brief Consruct using second and nanosecond
     * \param sec is system second
     * \param nsec is system nanosecond
     */
    time(std::chrono::nanoseconds timepoint)
	: timepoint_(timepoint)
    {}
    
    /// Allow Empty Consructor
    time() = default;
    
    /// Copy Conatructor
    time(const rapp::object::time &) = default;
    
    /// \brief Equality operator
    bool operator==(const rapp::object::time & rhs) const
    {
		return (this->timepoint_ == rhs.timepoint_);
    }

	/// \brief return seconds elapsed since UNIX Epoch
	uint32_t sec() const
	{
		return std::chrono::duration_cast<std::chrono::seconds>(timepoint_).count();
	}

	/// \brief return nanoseconds elapsed since UNIX Epoch
	uint64_t nanosec() const
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(timepoint_).count();
	}

	/// \brief convert *this* into a boost tree
	boost::property_tree::ptree treefy() const
	{
		boost::property_tree::ptree tree;
        tree.put("sec", std::chrono::duration_cast<std::chrono::seconds>(timepoint_).count());
        tree.put("nsec", std::chrono::duration_cast<std::chrono::nanoseconds>(timepoint_).count());
		return tree;
	}

private:
	/// members
	std::chrono::nanoseconds timepoint_;
};
}
}
#endif
