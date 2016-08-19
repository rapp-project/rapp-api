#ifndef RAPP_OBJECT_TIME
#define RAPP_OBJECT_TIME
#include "includes.ihh"
namespace rapp {
namespace object {

using namespace rapidjson;    
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
    time(const rapidjson::Value::ConstMemberIterator & iter)
    {
        uint32_t sec_value;
        auto it = iter->FindMember("sec");
        if (it != iter->MemberEnd()) {
            if (it->value.IsUint()) {
                sec_value = it->value.GetUint();
            }
            else 
                throw std::runtime_error("member `sec` not a uint");
        }
        else 
            throw std::runtime_error("param has no `sec` member");

        uint64_t nsec_value;
        it = iter->FindMember("nsec");
        if (it != iter->MemberEnd()) {
            if (it->value.IsUint64()) {
                nsec_value = it->value.GetUint64();
            }
            else 
                throw std::runtime_error("member `nsec` not a uint64");
        }
        else {
            throw std::runtime_error("param has no `nsec` member");
        }
        // TODO: construct a timepoint using the values we got
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
