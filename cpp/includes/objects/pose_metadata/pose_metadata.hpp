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

	/// \brief construct using rapidJSON
    pose_metada(const rapidjson::Value::ConstMemberIterator & iter)
    {
        auto it = iter->FindMember("seq");
        if (it != iter->MemberEnd()) {
            if (it->value.IsInt())
            {
                this->seq_ = it->value.GetInt();
            }
            else
                throw std::runtime_error("member `seq` not a int");    
        }
        else 
            throw std::runtime_error("param has no `seq` value");

        auto it = iter->FindMember("frame_id");
        if (it != iter->MemberEnd()) {
            if (it->value.IsString())
            {
                this->frameid_ = it->value.GetString();
            }
            else
                throw std::runtime_error("member `frame_id` not a string");    
        }
        else 
            throw std::runtime_error("param has no `frame_id` value");
        
        auto it = iter->FindMember("stamp");
        this->stamp_ = time(it);
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

	
    /// \brief Serialization using rapidJSON
    template <typename W>
    void Serialize(W & writer) const
    {
        writer.StartObject();
        writer.String("seq");
        writer.Int(seq_);
        writer.String("frame_id");
        writer.String(frameid_);
        writer.String("stamp");
        stamp_.Serialize(writer);   
    }

	/// members
	int seq_ = 0;
	rapp::object::time stamp_;
    std::string frameid_ = "/map";
};
}
}
#endif
