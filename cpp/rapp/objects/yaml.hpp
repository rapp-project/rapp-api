#ifndef RAPP_OBJECT_YAML
#define RAPP_OBJECT_YAML
#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \class yaml
 * \brief a minimal YAML wrapper
 * \version 0.6.0
 * \date 10-May-2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>  
*/
class yaml
{
public:
	
	/// construct with a filename
    yaml() = default;

	/// construct with a filename and raw yaml string
	yaml(std::string data)
	: data_(data)
	{}

    /// copy constructor
    yaml(const rapp::object::yaml &) = default;
    
    /// \brief equality operator
    bool operator==(const rapp::object::yaml & rhs) const
    {
		return (this->data_ == rhs.data_);
    }

	/// get as std::string 
	// TODO: serialize mapping items to a single std::string
	// Boost may be useful here.
	std::string get_string() const
	{
		return data_;
	}

private:
	/// raw yaml text
	std::string data_;
};
}
}
#endif
