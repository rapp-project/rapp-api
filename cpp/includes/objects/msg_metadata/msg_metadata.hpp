#ifndef RAPP_OBJECT_HEADER
#define RAPP_OBJECT_HEADER
#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \class msg_metadata
 * \brief encapsulates metadata of another class (e.g. pose)
 * \version 0.6.0
 * \date 24-July-2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
struct msg_metadata
{
    /**
     * \brief Consruct using sequence nr, time stamp and frameid
     * \param seq defines data sequence
     * \param stamp is message data generation time stamp
     * \param frameid is data coordination frame
     */
    msg_metadata(
					int seq,
					rapp::object::time stamp,
					std::string frameid
				  )
    : seq_(seq), stamp_(stamp), frameid_(frameid)
    {}
    
    /// \brief disable Empty Consructor
    msg_metadata() = default;
    
    /// \brief default copy Conatructor
    msg_metadata(const rapp::object::msg_metadata &) = default;

	/// \brief load from a boost property JSON tree
	msg_metadata(const boost::property_tree::ptree & pt)
	{
<<<<<<< HEAD:cpp/includes/objects/msg_metadata/msg_metadata.hpp
		seq_ = pt.get<int>("seq");
		frameid_ = pt.get<std::string>("frame_id");
		int sec = pt.get<int>("stamp.secs");
		int nsec = pt.get<int>("stamp.nsecs");
		stamp_ = rapp::object::time(std::chrono::seconds(sec) + std::chrono::nanoseconds(nsec));
=======
		for (const auto it : json->second) {
			if (it.first == "seq") {
				this->seq_ = it.second.get_value<int>();
			}
			else if (it.first == "frame_id") {
			    this->frameid_ = it.second.get_value<std::string>();
			}
			else if (it.first == "stamp") {
                uint32_t sec_value;
                uint64_t nsec_value;
				for (auto it2 = it.second.begin(); it2 != it.second.end(); ++it2) {
                    if (it2->first == "sec") {
                        sec_value = it2->second.get_value<uint32_t>();
                    }
                    else if (it2->first == "nsec") {
                        nsec_value = it2->second.get_value<uint64_t>();
                    }
				}
                uint64_t total = ((uint64_t) sec_value << 32 | nsec_value);
                std::chrono::nanoseconds nsec(total);
			    this->stamp_ = rapp::object::time(nsec);
			}
		}
>>>>>>> cpp:cpp/includes/objects/pose_metadata/pose_metadata.hpp
	}

    /** 
     * \brief equality operator
     * \note compare all components
     */
    bool operator==(const rapp::object::msg_metadata & rhs) const
    {
		return (this->seq_ == rhs.seq_) &&
			   (this->stamp_ == rhs.stamp_) &&
			   (this->frameid_ == rhs.frameid_);
    }

	/// \brief convert *this* into a boost tree
	boost::property_tree::ptree treefy() const
	{
		boost::property_tree::ptree tree;
        tree.put("seq", seq_);
        tree.put("frame_id", frameid_, s());
		tree.add_child("stamp", stamp_.treefy());
		return tree;
	}

	/// members
	int seq_ = 0;
	rapp::object::time stamp_;
    std::string frameid_ = "/map";
};
}
}
#endif
