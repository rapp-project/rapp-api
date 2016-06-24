#ifndef RAPP_OBJECT_HEADER
#define RAPP_OBJECT_HEADER
#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \struct header
 * \brief encapsulates metadata of another class (e.g. pose)
 * \version 0.6.0
 * \date 10-May-2016
 * \author Wojciech Dudek <dudekwa@gmail.com>
 * TODO: rename to `metadata` header is misleading and used in asio.
 */
struct header
{
    /**
     * \brief Consruct using sequence nr, time stamp and frameid
     * \param seq defines data sequence
     * \param stamp is message data generation time stamp
     * \param frameid is data coordination frame
     */
    header(
            int seq,
            time stamp,
            std::string frameid
          )
    : seq(seq), stamp(stamp), frameid(frameid)
    {}
    
    /// \brief allow Empty Consructor
    header() = default;
    
    /// \brief default copy Conatructor
    header(const rapp::object::header &) = default;

    /** 
     * \brief equality operator
     * \note compare all components
     */
    bool operator==(const rapp::object::header & rhs) const
    {
		return (this->seq == rhs.seq) &&
			   (this->stamp == rhs.stamp) &&
			   (this->frameid == rhs.frameid);
    }

	/// \brief convert *this* into a boost tree
	boost::property_tree::ptree treefy() const
	{
		boost::property_tree::ptree tree;
        tree.put("seq", seq);
        tree.put("frameid", frameid);
		tree.add_child("stamp", stamp.treefy());
		return tree;
	}

	/// members
	int seq = 0;
	rapp::object::time stamp;
    const std::string frameid = "/map";
};
}
}
#endif
