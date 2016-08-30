#include "time.hpp"
namespace rapp {
namespace object {

time::time(std::chrono::nanoseconds timepoint)
{
    auto sec = std::chrono::duration_cast<std::chrono::seconds>(timepoint);
    auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(timepoint);
    seconds_ = sec.count();
    nanoseconds_ = std::chrono::duration_cast<std::chrono::nanoseconds>(nsec - sec).count();
}

time::time(const json::const_iterator & stamp)
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

json::object_t time::to_json() const
{
    json::object_t values = {{"secs", seconds_}, {"nsecs", nanoseconds_}};
    return values;
}

bool time::operator==(const rapp::object::time & rhs) const
{
    return (this->seconds_ == rhs.seconds_)
            && (this->nanoseconds_ == rhs.nanoseconds_);
}

uint32_t time::seconds() const
{
    return seconds_;
}

uint32_t time::nanoseconds() const
{
    return nanoseconds_;
}

}
}
