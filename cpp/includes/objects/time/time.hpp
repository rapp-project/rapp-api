#ifndef RAPP_OBJECT_TIME
#define RAPP_OBJECT_TIME
#include "includes.ihh"
namespace rapp {
namespace object {

/**
 * \struct time
 * \brief wraps around a time-stamp (UNIX Epoch)
 * \version 0.7.0
 * \date 19 August 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
class time
{
public:
    /**
     * \brief Consruct using second and nanosecond
     * \param sec is system second
     * \param nsec is system nanosecond
     */
    time(std::chrono::nanoseconds timepoint);

    /// Allow Empty Consructor
    time() = default;
    
    /// Copy Conatructor
    time(const rapp::object::time &) = default;

    /// construct using library "json for modern c++"
    time(const json::const_iterator & stamp);

    json::object_t to_json() const;
    
    /// \brief Equality operator
    bool operator==(const rapp::object::time & rhs) const;
    
    /// \brief return seconds elapsed since UNIX Epoch
	uint32_t seconds() const;

	/// \brief return nanoseconds elapsed since UNIX Epoch
	uint32_t nanoseconds() const;

private:

    uint32_t seconds_;
    uint32_t nanoseconds_;
};
}
}
#endif
