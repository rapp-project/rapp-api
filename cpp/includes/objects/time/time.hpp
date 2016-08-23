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
    time(std::chrono::nanoseconds timepoint)
    {
        auto sec = std::chrono::duration_cast<std::chrono::seconds>(timepoint);
        auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(timepoint);
        seconds_ = sec.count();
        nanoseconds_ = std::chrono::duration_cast<std::chrono::nanoseconds>(nsec - sec).count();
    }
    
    /// Allow Empty Consructor
    time() = default;
    
    /// Copy Conatructor
    time(const rapp::object::time &) = default;

    /// construct using library "json for modern c++"
    time(const json::const_iterator & stamp)
    {
        if (stamp->find("secs") == stamp->end()) {
            throw std::runtime_error("no sec in stamp");
        }
        else {
            seconds_ = stamp->find("secs")->get<uint32_t>();
        }
        if (stamp->find("nsecs") == stamp->end()) {
            throw std::runtime_error("no nsec in stamp");
        }
        else {
            nanoseconds_ = stamp->find("nsecs")->get<uint32_t>();
        }
    }

    json::object_t to_json() const
    {
        json::object_t values = {{"secs", seconds_}, {"nsecs", nanoseconds_}};
        json::object_t obj    = {{"stamp" , values}};
        return obj;
    }
    
    /// \brief Equality operator
    bool operator==(const rapp::object::time & rhs) const
    {
		return (this->seconds_ == rhs.seconds_)
                && (this->nanoseconds_ == rhs.nanoseconds_);
    }

	/// \brief return seconds elapsed since UNIX Epoch
	uint32_t seconds() const
	{
		return seconds_;
	}

	/// \brief return nanoseconds elapsed since UNIX Epoch
	uint32_t nanoseconds() const
	{
		return nanoseconds_;
	}

private:

    uint32_t seconds_;
    uint32_t nanoseconds_;
};
}
}
#endif
