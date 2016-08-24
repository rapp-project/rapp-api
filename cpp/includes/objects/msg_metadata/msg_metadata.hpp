#ifndef RAPP_OBJECT_MSG_METADATA
#define RAPP_OBJECT_MSG_METADATA
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

	/// \brief construct using rapidJSON
    msg_metada(const rapidjson::Value::ConstMemberIterator & iter)
    {
    
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

private:
	/// members
	int seq_ = 0;
	rapp::object::time stamp_;
    std::string frameid_ = "/map";
};
}
}
#endif
