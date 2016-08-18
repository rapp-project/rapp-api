#ifndef RAPP_CLOUD_UTILS
#define RAPP_CLOUD_UTILS


#include <boost/property_tree/ptree.hpp>

namespace rapp {

namespace pt = boost::property_tree;

struct s
{
    typedef std::string internal_type;
    typedef std::string external_type;

    boost::optional<std::string> get_value(const std::string &v) { return  v.substr(1, v.size() - 2) ; }
    boost::optional<std::string> put_value(const std::string &v) { return std::string("\"") + v + std::string("\""); }
};
} // namespace rapp

#endif /* RAPP_CLOUD_UTILS */
