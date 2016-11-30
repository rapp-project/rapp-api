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

namespace utils {

// Add a list
template<typename T>
pt::ptree put_vector(const std::vector<T> vec) {
    pt::ptree ret_node;
    for (auto &val: vec)
    {
        // Create an unnamed node containing the value
        pt::ptree tmp_node;
        tmp_node.put("", val);
    
        // Add this node to the list.
        ret_node.push_back(std::make_pair("", tmp_node));
    }
    return ret_node;
}

template<>
pt::ptree put_vector<std::string>(const std::vector<std::string> vec) {
    pt::ptree ret_node;
    for (auto &val: vec)
    {
        // Create an unnamed node containing the value
        pt::ptree tmp_node;
        tmp_node.put("", val, s());
    
        // Add this node to the list.
        ret_node.push_back(std::make_pair("", tmp_node));
    }
    return ret_node;
}

};

#endif /* RAPP_CLOUD_UTILS */
