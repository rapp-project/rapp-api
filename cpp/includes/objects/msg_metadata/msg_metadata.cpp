#include "msg_metadata.hpp"
namespace rapp{
namespace object {

msg_metadata::msg_metadata(
                int seq,
                rapp::object::time stamp,
                std::string frameid
              )
: seq_(seq), stamp_(stamp), frameid_(frameid)
{}

msg_metadata::msg_metadata(const json::const_iterator & metadata)
{
    if(metadata->find("stamp") == metadata->end()) {
        throw std::runtime_error("no param stamp in msg_metadata");
    }
    else {
        const auto stamp_it = metadata->find("stamp");
        stamp_ = rapp::object::time(stamp_it);
    }
    
    if(metadata->find("frame_id") == metadata->end()) {
        throw std::runtime_error("no param frame_id in msg_metadata");
    }
    else {
        frameid_ = metadata->find("frame_id")->get<std::string>();
    }

    if(metadata->find("seq") == metadata->end()) {
        throw std::runtime_error("no param seq in msg_database");
    }
    else {
        seq_ = metadata->find("seq")->get<int>();
    }
}
   
json::object_t msg_metadata::to_json() const 
{
    json::object_t values = {{"stamp", stamp_.to_json()}, 
                             {"frame_id", frameid_}, 
                             {"seq", seq_}};
    return values;
}

rapp::object::time msg_metadata::get_time() const
{
    return stamp_;
}

int msg_metadata::get_seq() const
{
    return seq_;
}

std::string msg_metadata::get_frame() const
{
    return frameid_;
}

bool msg_metadata::operator==(const rapp::object::msg_metadata & rhs) const
{
    return (this->seq_ == rhs.seq_) &&
           (this->stamp_ == rhs.stamp_) &&
           (this->frameid_ == rhs.frameid_);
}

}
}
