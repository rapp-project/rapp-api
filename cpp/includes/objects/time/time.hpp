#ifndef RAPP_OBJECT_TIME
#define RAPP_OBJECT_TIME
namespace rapp {
namespace object {
/**
 * \class time
 * \brief ??
 * \version 0.6.0
 * \date 10-May-2016
 * \author Wojciech Dudek <dudekwa@gmail.com>
 */
struct time
{
    /**
     * \brief Consruct using second and nanosecond
     * \param sec is system second
     * \param nsec is system nanosecond
     */
    time(int32_t sec, int32_t nsec)
    : sec(sec), nsec(nsec)
    {}
    
    /// Allow Empty Consructor
    time() = default;
    
    /// Copy Conatructor
    time(const rapp::object::time &) = default;
    
    /// \brief Equality operator
    bool operator==(const rapp::object::time & rhs) const
    {
		return (this->sec == rhs.sec) &&
			   (this->nsec == rhs.nsec);
    }

	/// \brief convert *this* into a boost tree
	boost::property_tree::ptree treefy() const
	{
		boost::property_tree::ptree tree;
        tree.put("sec", sec);
        tree.put("nsec", nsec);
		return tree;
	}

	/// members
	uint32_t sec = 0;
    uint32_t nsec = 0;
};
}
}
#endif
