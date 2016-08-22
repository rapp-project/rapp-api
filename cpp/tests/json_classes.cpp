#define BOOST_TEST_MODULE JSONTest

#include <iostream>
#include <fstream>
#include <boost/test/unit_test.hpp>
#include "rapidjson/document.h"
#include "../includes/objects/time/time.hpp"

/// \brief
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

/// \brief load from JSON, save to JSON
BOOST_AUTO_TEST_CASE(time_json_test)
{
    //JSON
    std::string json = read_json_file("time_class.json");
    BOOST_CHECK(!json.empty());

    rapidjson::Document d;
    d.Parse(json.c_str()); 

    const auto & stamp = d["stamp"];
    rapp::object::time time_obj = rapp::object::time(stamp);
    BOOST_CHECK_EQUAL(time_obj.sec(), 1464949299);
    BOOST_CHECK_EQUAL(time_obj.nanosec(), 93018853);
    

    //Serialize
    /*
    rapidjson::StringBuffer s_buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s_buffer);
    obj_time1.Serialize(writer);
    std::string serialize_result = s_buffer.GetString();
    BOOST_CHECK_EQUAL(json, serialize_result);
    */

}
BOOST_AUTO_TEST_SUITE_END()
