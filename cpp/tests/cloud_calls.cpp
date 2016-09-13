#define BOOST_TEST_MODULE ServiceTest
#include <boost/test/unit_test.hpp>
#include "../includes/misc/json.hpp"
#include "../includes/cloud/service_controller/service_controller.hpp"
#include "../includes/cloud/available_services/available_services.hpp"
#include "../includes/cloud/cognitive_exercises/cognitive_exercises.hpp"
#include "../includes/cloud/geolocation/geolocation.hpp"
#include "../includes/cloud/navigation/path_planning/path_planning.hpp"

BOOST_AUTO_TEST_SUITE (cloud_calls)

/*
 * \brief check rapp::cloud::available_services
 * A callback function is done to check that the 
 * desearialization is correct.
 * A json is done manually to be sure about results.
 */    
BOOST_AUTO_TEST_CASE(available_services_cloud_test)
{
    auto callback = [] (std::vector<std::pair<std::string, std::string>> service) {
        BOOST_CHECK_EQUAL(service.at(0).first, "name");
        BOOST_CHECK_EQUAL(service.at(0).second, "url");
    };
    rapp::cloud::available_services as1(callback);
    auto j1 = R"(
              {
                "services" : [{
                               "name" : "name",
                               "url" : "url"
                              }],
                "error" : ""
              }
              )"_json;
    std::string j1_string = j1.dump(-1);
    as1.deserialise(j1_string);
}
/*
 * \brief check all the cognitive_exercises classes
 * A callback is done to check that the desearilization
 * is correct comparing with a json file done manually.
 * \note: the name of the variables are the initial of
 *  the classes or words corresponding with json.
 */
BOOST_AUTO_TEST_CASE(cognitive_exercises_cloud_test)
{
    //Cognitive_test_selector class
    auto test_callback = [] (std::vector<std::string> q,
                             std::vector<std::vector<std::string>> pa,
                             std::vector<std::string> ca,
                             std::string ti,
                             std::string tt,
                             std::string ts)
    {
        BOOST_CHECK_EQUAL(q.at(0), "questions");
        BOOST_CHECK_EQUAL(pa.at(0).at(0), "possib_ans");
        BOOST_CHECK_EQUAL(ca.at(0), "correct_ans");
        BOOST_CHECK_EQUAL(ti, "test_instance");
        BOOST_CHECK_EQUAL(tt, "test_type");
        BOOST_CHECK_EQUAL(ts, "test_subtype");
    };
    rapp::cloud::cognitive_test_selector cts("ArithmeticCts", 
                                             "TransactionChangeCts", 
                                             "1", 
                                             "1", 
                                             test_callback);
    auto j1 = R"(
              {
                "questions" : ["questions"],
                "possib_ans" : [["possib_ans"]],
                "correct_ans" : ["correct_ans"],
                "test_instance" : "test_instance",
                "test_type" : "test_type",
                "test_subtype" : "test_subtype",
                "error" : ""
              }
              )"_json;
    std::string j1_string = j1.dump(-1);
    cts.deserialise(j1_string); 
    //cognitive_record_performance
    auto performance_callback = [] (std::string pe) {
        BOOST_CHECK_EQUAL(pe, "entry");
    };
    rapp::cloud::cognitive_record_performance rp("test", 1, performance_callback);
    auto j2 = R"(
              {
                "performance_entry" : "entry",
                "error" : ""
              }
              )"_json;
    std::string j2_string = j2.dump(-1);
    rp.deserialise(j2_string);
    //cognitive_get_history
    auto history_callback = [] (std::string r) {
        nlohmann::json j_test;
        j_test["error"] = "";
        BOOST_CHECK_EQUAL(r, j_test.dump(-1));
    };
    rapp::cloud::cognitive_get_history gh(0, 0, "test", history_callback);
    auto j3 = R"(
              {
                "error" : ""
              }
              )"_json;
    std::string j3_string = j3.dump(-1);
    gh.deserialise(j3_string);
    //cognitive_get_scores
    auto scores_callback = [] (std::vector<std::string> tc, std::vector<float> sc) {
        BOOST_CHECK_EQUAL(tc.at(0), "test_classes");
        BOOST_CHECK_EQUAL(sc.at(0), 0);
    };
    rapp::cloud::cognitive_get_scores gs(0, "test", scores_callback);
    auto j4 = R"(
              {
                "test_classes" : ["test_classes"],
                "scores" : [0],
                "error" : ""
              }
              )"_json;
    std::string j4_string = j4.dump(-1);
    gs.deserialise(j4_string);
}

/*
 * \brief check geolocation
 * A callback is done to check that the desearilization
 * is correct comparing with a json file done manually.
 */
BOOST_AUTO_TEST_CASE(geolocation_cloud_test)
{
    auto geo_call = [] (std::string city,
                        std::string country,
                        std::string country_c,
                        float lat,
                        float longt,
                        std::string time,
                        std::string zip)     
    {
        BOOST_CHECK_EQUAL(city, "city");
        BOOST_CHECK_EQUAL(country, "country");
        BOOST_CHECK_EQUAL(country_c, "country_code");
        BOOST_CHECK_EQUAL(lat, 1);
        BOOST_CHECK_EQUAL(longt, 2);
        BOOST_CHECK_EQUAL(time, "timezone");
        BOOST_CHECK_EQUAL(zip, "zip");
    };
    rapp::cloud::geolocation geo("ipaddr", "engine", geo_call);
    auto j1 = R"(
              {
                "city" : "city",
                "country" : "country",
                "country_code" : "country_code",
                "latitude" : 1,
                "longtitude" : 2,
                "timezone" : "timezone",
                "zip" : "zip",
                "error" : ""
              }
              )"_json;
    std::string j1_string = j1.dump(-1);
    geo.deserialise(j1_string);

}
/*
 * \brief check all the navigation/path_planning classes
 * A callback is done to check that the desearilization
 * is correct comparing with a json file done manually 
 * or loading one.
 * \note: the name of the variables are the initial of
 *  the classes or words corresponding with json.
 */
BOOST_AUTO_TEST_CASE(navigation_cloud_test)
{
    //Load a json file into a string
    std::ifstream file("tests/data/json_classes_planned_path.json");
    std::string json_str((std::istreambuf_iterator<char>(file)),
                          std::istreambuf_iterator<char>());
    try {
         if (json_str.empty()) {
            throw std::runtime_error("empty JSON string");
        }
    }
    catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
    //plan_path_2d
    auto path_call = [] (rapp::object::planned_path pp) {
        std::chrono::nanoseconds t(1464949299093018853);
        auto time0 = rapp::object::time(t);
        auto header0 = rapp::object::msg_metadata(0 , time0, "map");
        auto quat =rapp::object::quaternion(0, 
                                            0, 
                                            0.17576372515799546, 
                                            0.9844323810798712);

        auto point = rapp::object::point(0.9999999776482582, 
                                         0.9999999776482582, 
                                         0);

        auto pose0 = rapp::object::pose( point, quat);
        auto ps_obj0 = rapp::object::pose_stamped(header0, pose0);
        BOOST_CHECK(pp.get_path().at(0) == ps_obj0);
        BOOST_CHECK_EQUAL(pp.get_plan(), 1);
    };
    rapp::object::pose_stamped start;
    rapp::object::pose_stamped goal;
    rapp::cloud::plan_path_2d pp2d("map", "robot", "algorithm", start, goal, path_call);
    pp2d.deserialise(json_str);
    //path_upload_map
    auto upload_call = [] (std::string error) {
        BOOST_CHECK_EQUAL(error, "");
    };
    rapp::object::picture png_file("tests/data/object_classes_map_1.png");
    rapp::object::yaml yaml_file("tests/data/object_classes_map_1.yaml");
    rapp::cloud::path_upload_map um(png_file, yaml_file, "map", upload_call);
    auto j1 = R"(
              {
                "error" : ""
              }
              )"_json;
    std::string j1_string = j1.dump(-1);
    um.deserialise(j1_string);
}
BOOST_AUTO_TEST_SUITE_END()
