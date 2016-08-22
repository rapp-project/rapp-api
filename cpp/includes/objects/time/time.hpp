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

    /// construct using rapidJSON
    time(const rapidjson::Value & stamp)
    {
        uint32_t sec_value;
        uint64_t nsec_value;
        /*
        for (auto itr = stamp.MemberBegin(); itr != stamp.MemberEnd(); ++itr) {
            if (strcmp(itr->name.GetString(), "secs") == 0) {
                sec_value = (uint32_t)itr->value.GetUint();
            }
            else if (strcmp(itr->name.GetString(), "nsecs") == 0) {
                nsec_value = (uint64_t)itr->value.GetUint64();
            }
        }
        */
        std::cout << "sec: " << sec_value << std::endl;
        std::cout << "nsec: " << nsec_value << std::endl;
        nsec_value = (uint64_t)sec_value << 32;
        timepoint_ = std::chrono::nanoseconds(nsec_value);
        std::cout << timepoint_.count() << std::endl;
    }
    
    /// \brief Equality operator
    bool operator==(const rapp::object::time & rhs) const
    {
		return (this->timepoint_ == rhs.timepoint_);
    }

	/// \brief get the actual timepoint
	std::chrono::nanoseconds timepoint() const
	{
		return timepoint_;
	}

	/// \brief return seconds elapsed since UNIX Epoch
	uint32_t sec() const
	{
		return std::chrono::duration_cast<std::chrono::seconds>(timepoint_).count();
	}

	/// \brief return nanoseconds elapsed since UNIX Epoch
	uint64_t nanosec() const
	{
		auto sec = std::chrono::duration_cast<std::chrono::seconds>(timepoint_);
		auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(timepoint_);
		return std::chrono::duration_cast<std::chrono::nanoseconds>(nsec - sec).count();
	}

    template <typename W>
    void Serialize(W & writer) const
    {
        writer.StartObject();
        writer.String("sec");
        writer.Uint(sec());
        writer.String("nsec");
        writer.Uint64(nanosec());
        writer.EndObject();
    }

private:
	/// members
	std::chrono::nanoseconds timepoint_;
};
}
}
#endif
