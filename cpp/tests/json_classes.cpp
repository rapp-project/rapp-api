#define BOOST_TEST_MODULE JSONTest

#include <iostream>
#include <fstream>
#include <boost/test/unit_test.hpp>
#include "json.hpp"
#include "../includes/objects/time/time.hpp"
#include "../includes/objects/point/point.hpp"
#include "../includes/objects/quaternion/quaternion.hpp"
#include "../includes/objects/pose/pose.hpp"
#include "../includes/objects/msg_metadata/msg_metadata.hpp"
#include "../includes/objects/pose_stamped/pose_stamped.hpp"
#include "../includes/objects/planned_path/planned_path.hpp"
#include "../includes/objects/human/human.hpp"
#include "../includes/objects/face/face.hpp"

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
        
    nlohmann::json::object_t out = {{"stamp", time_obj.to_json()}};
    BOOST_CHECK(json == out);
}

/**
 * check rapp::object::point for json (de)serialisation
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
 * check rapp::object::quaternion for json (de)serialisation
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

/**
 * check rapp::object::pose for json (de)serialisation
 * first load from json file and parse
 * then test with hardcoded values from JSON
 * and finally test serialisation produces the same JSON
 */

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

/**
 * check rapp::object::msg_metadata for json (de)serialisation
 * first load from json file and parse
 * then test with hardcoded values from JSON
 * and finally test serialisation produces the same JSON
 */

BOOST_AUTO_TEST_CASE(msg_metadata_json_test)
{
    std::string string = read_json_file("msg_metadata_class.json");
    BOOST_CHECK(!string.empty());

    auto json = nlohmann::json::parse(string);
    const auto header_it = json.find("header");
    BOOST_CHECK(header_it != json.end());

    auto msg0 = rapp::object::msg_metadata(header_it);
    rapp::object::time time1 = msg0.get_time();
    BOOST_CHECK_EQUAL(time1.seconds(),1464949299);
    BOOST_CHECK_EQUAL(time1.nanoseconds(),93018853);

    BOOST_CHECK_EQUAL(msg0.get_seq(), 0);
    BOOST_CHECK_EQUAL(msg0.get_frame(), "map"); 

    nlohmann::json out = {{"header", msg0.to_json()}};
    BOOST_CHECK(json == out);
}

/**
 * check rapp::object::pose_stamped for json (de)serialisation
 * first load from json file and parse
 * then test with hardcoded values from JSON
 * and finally test serialisation produces the same JSON
 */

BOOST_AUTO_TEST_CASE(pose_stamped_json_test)
{
    std::string string = read_json_file("pose_stamped.json");
    BOOST_CHECK(!string.empty());

    auto json = nlohmann::json::parse(string);
    const auto stamped_it = json.find("path");
    BOOST_CHECK(stamped_it != json.end());

    auto ps_obj0 = rapp::object::pose_stamped(stamped_it);
    auto quat =rapp::object::quaternion(0, 
                                        0, 
                                        0.17576372515799546, 
                                        0.9844323810798712);

    auto point = rapp::object::point(0.9999999776482582, 
                                     0.9999999776482582, 
                                     0);

    const auto pose0 = ps_obj0.get_pose();
    auto quat1 = pose0.get_orientation();
    BOOST_CHECK(quat == quat1);
    
    auto point1 = pose0.get_position();
    BOOST_CHECK(point == point1);

    auto header1 = ps_obj0.get_header();
    auto frameid1= header1.get_frame();
    auto seq1 = header1.get_seq();
    auto time1 = header1.get_time();
    BOOST_CHECK_EQUAL(frameid1, "map");
    BOOST_CHECK_EQUAL(seq1, 0);
    BOOST_CHECK_EQUAL(time1.seconds(),1464949299);
    BOOST_CHECK_EQUAL(time1.nanoseconds(),93018853);

    nlohmann::json out = {{"path", ps_obj0.to_json()}};
    BOOST_CHECK(json == out);

}

/**
 * check rapp::object::planned_path for json (de)serialisation
 * first load from json file and parse
 * then test with hardcoded values from JSON
 * and finally test serialisation produces the same JSON
 */

BOOST_AUTO_TEST_CASE(planned_path_json_test)
{
    std::string string = read_json_file("planned_path.json");
    BOOST_CHECK(!string.empty());

    const auto json = nlohmann::json::parse(string);
    auto pp_obj = rapp::object::planned_path(json);

    const auto json_back = pp_obj.to_json();
    BOOST_CHECK(json == json_back);

}

/**
 * check rapp::object::human for json (de)serialisation
 * first load from json file and parse
 * then test with hardcoded values from JSON
 * and finally test serialisation produces the same JSON
 */

BOOST_AUTO_TEST_CASE(human_json_test)
{
    std::string string = read_json_file("human_class.json");
    BOOST_CHECK(!string.empty());

    const auto json = nlohmann::json::parse(string);
    const auto human_it = json.find("human");
    BOOST_CHECK(human_it != json.end());

    auto human_obj = rapp::object::human(human_it);
    nlohmann::json out = {{"human", human_obj.to_json()}};
    BOOST_CHECK(json == out);
}

/**
 * check rapp::object::face for json (de)serialisation
 * first load from json file and parse
 * then test with hardcoded values from JSON
 * and finally test serialisation produces the same JSON
 */

BOOST_AUTO_TEST_CASE(face_json_test)
{
    std::string string = read_json_file("face_class.json");
    BOOST_CHECK(!string.empty());

    const auto json = nlohmann::json::parse(string);
    const auto face_it = json.find("faces");
    BOOST_CHECK(face_it != json.end());

    auto face_obj = rapp::object::face(face_it);
    nlohmann::json out = {{"faces", face_obj.to_json()}};
    BOOST_CHECK(json == out);
}

BOOST_AUTO_TEST_SUITE_END()
