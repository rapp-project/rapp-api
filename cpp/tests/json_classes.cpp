#define BOOST_TEST_MODULE JSONTest

#include <iostream>
#include <fstream>
#include <boost/test/unit_test.hpp>
#include "json.hpp"
#include "../includes/objects/time/time.hpp"
#include "../includes/objects/point/point.hpp"
#include "../includes/objects/quaternion/quaternion.hpp"
#include "../includes/objects/pose/pose.hpp"

/// \brief function to read a json file and it is converted 
//  \into a string param
std::string read_json_file(const std::string file)
{
    if (file.empty()){
        throw std::runtime_error("empty file param");
    }
    std::ifstream t(file);
    try {
        std::string str((std::istreambuf_iterator<char>(t)),
                         std::istreambuf_iterator<char>());
        if (str.empty()) {
            throw std::runtime_error("empty JSON string");
        }
        return str;
    }
    catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
}

BOOST_AUTO_TEST_SUITE(json_classes_test)

/**
 * check rapp::object::time for json (de)serialisation
 * first load from json file and parse
 * then test with hardcoded values from JSON
 * and finally test serialisation produces the same JSON
 */
BOOST_AUTO_TEST_CASE(time_json_test)
{
    std::string string = read_json_file("time_class.json");
    BOOST_CHECK(!string.empty());

    auto json = nlohmann::json::parse(string); 
    const auto stamp = json.find("stamp");
    BOOST_CHECK(stamp != json.end());

    rapp::object::time time_obj = rapp::object::time(stamp);
    BOOST_CHECK_EQUAL(time_obj.seconds(), 1464949299);
    BOOST_CHECK_EQUAL(time_obj.nanoseconds(), 93018853);
    
    auto out = time_obj.to_json();
    BOOST_CHECK(json == out);
}

/**
 * check rapp::object::time for json (de)serialisation
 * first load from json file and parse
 * then test with hardcoded values from JSON
 * and finally test serialisation produces the same JSON
 */

BOOST_AUTO_TEST_CASE(point_json_test)
{
    std::string string = read_json_file("point_class.json");
    BOOST_CHECK(!string.empty());

    auto json = nlohmann::json::parse(string);
    const auto position = json.find("position");
    BOOST_CHECK(position != json.end());

    rapp::object::point point_obj = rapp::object::point(position);
    BOOST_CHECK_EQUAL(point_obj.x, 0.9999999776482582);
    BOOST_CHECK_EQUAL(point_obj.y, 0.9999999776482582);
    BOOST_CHECK_EQUAL(point_obj.z, 0.0);

    nlohmann::json::object_t out = {{ "position", point_obj.to_json() }};
    BOOST_CHECK(json == out);
}

/**
 * check rapp::object::time for json (de)serialisation
 * first load from json file and parse
 * then test with hardcoded values from JSON
 * and finally test serialisation produces the same JSON
 */
BOOST_AUTO_TEST_CASE(quaternion_json_test)
{
    std::string string = read_json_file("quaternion_class.json");
    BOOST_CHECK(!string.empty());

    auto json = nlohmann::json::parse(string);
    const auto orientation = json.find("orientation");
    BOOST_CHECK(orientation != json.end());
    
    rapp::object::quaternion quat_obj = rapp::object::quaternion(orientation);
    BOOST_CHECK_EQUAL(quat_obj.x, 0.0);
    BOOST_CHECK_EQUAL(quat_obj.y, 0.0);
    BOOST_CHECK_EQUAL(quat_obj.z, 0.3062984133859556);
    BOOST_CHECK_EQUAL(quat_obj.w, 0.9519355450644997);

    nlohmann::json::object_t out = {{ "orientation", quat_obj.to_json()}};
    BOOST_CHECK(json == out);
}

// TODO: pose_stamped
// TODO: msg_metadata
BOOST_AUTO_TEST_CASE(pose_json_test)
{
    std::string string = read_json_file("pose_class.json");
    BOOST_CHECK(!string.empty());

    auto json = nlohmann::json::parse(string);
    const auto pose_it = json.find("pose");
    BOOST_CHECK(pose_it != json.end());

    rapp::object::pose pose_obj = rapp::object::pose(pose_it);
    auto quat_obj = pose_obj.get_orientation();
    BOOST_CHECK_EQUAL(quat_obj.x, 0);
    BOOST_CHECK_EQUAL(quat_obj.z, 0.17576372515799546);
    BOOST_CHECK_EQUAL(quat_obj.w, 0.9844323810798712);

    auto point_obj = pose_obj.get_position();
    BOOST_CHECK_EQUAL(point_obj.x, 0.9999999776482582);
    BOOST_CHECK_EQUAL(point_obj.y, 0.9999999776482582);
    BOOST_CHECK_EQUAL(point_obj.z, 0);

    nlohmann::json::object_t out = {{ "pose" ,pose_obj.to_json()}};
    BOOST_CHECK(json == out);

}


BOOST_AUTO_TEST_SUITE_END()
