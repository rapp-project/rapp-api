#ifndef RAPP_OBJECT_HEADER
#define RAPP_OBJECT_HEADER
#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \class pose_metadata
 * \brief encapsulates metadata of another class (e.g. pose)
 * \version 0.6.0
 * \date 24-July-2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
struct pose_metadata
{
    /**
     * \brief Consruct using sequence nr, time stamp and frameid
     * \param seq defines data sequence
     * \param stamp is message data generation time stamp
     * \param frameid is data coordination frame
     */
    pose_metadata(
					int seq,
					rapp::object::time stamp,
					std::string frameid
				  )
    : seq_(seq), stamp_(stamp), frameid_(frameid)
    {}
    
    /// \brief disable Empty Consructor
    pose_metadata() = default;
    
    /// \brief default copy Conatructor
    pose_metadata(const rapp::object::pose_metadata &) = default;

	/// \brief load from a boost property JSON tree
	pose_metadata(boost::property_tree::ptree::const_iterator json)
	{
		for (const auto it : json->second) {
			if (it.first == "seq") {
				this->seq_ = it.second.get_value<int>();
			}
			else if (it.first == "frame_id") {
			    this->frameid_ = it.second.get_value<std::string>();
			}
			else if (it.first == "stamp") {
				for (auto it2 = it.second.begin(); it2 != it.second.end(); ++it2) {
					if (it2->first == "nsecs") {
						std::chrono::nanoseconds nsec(it2->second.get_value<uint64_t>());
						this->stamp_ = rapp::object::time(nsec);
					}
				}
			}
		}
	}

    /** 
     * \brief equality operator
     * \note compare all components
     */
    bool operator==(const rapp::object::pose_metadata & rhs) const
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
        tree.put("frameid", frameid_);
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
