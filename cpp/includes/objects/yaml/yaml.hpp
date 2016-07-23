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

	/// \brief a yaml key/value mapping
	template <typename T, typename C>
	struct mapping
	{
		std::string key;
		T value;
		std::vector<C> children;
	}

	/// construct with a filename
    yaml() = default;

	/// construct with a filename and raw yaml string
	yaml(std::string data)
	: data_(data)
	{}

	/// \brief add a mapping
	void add_key_value(const mapping)
	{
		// TODO: add entry
	}
    
    /// copy constructor
    yaml(const rapp::object::yaml &) = default;
    
    /// \brief equality operator
    bool operator==(const rapp::object::yaml & rhs) const
    {
		return (this->data_ == rhs.data_);
    }

	/// \brief convert *this* into a boost tree
	boost::property_tree::ptree treefy() const
	{
		boost::property_tree::ptree tree;
		// TODO: translate the YAML into a boost tree?
        return tree;
	}

private:
	/// raw yaml text
	std::string data_;
	/// list of mappings
	std::vector<mapping> items;
};
}
}
#endif
