#define BOOST_TEST_MODULE ServiceTest
#include <boost/test/unit_test.hpp>
#include <fstream>
#include "../includes/misc/json.hpp"
#include "../includes/cloud/service_controller/service_controller.hpp"
#include "../includes/cloud/available_services/available_services.hpp"
#include "../includes/cloud/cognitive_exercises/cognitive_exercises.hpp"
#include "../includes/cloud/geolocation/geolocation.hpp"
#include "../includes/cloud/navigation/path_planning/path_planning.hpp"
#include "../includes/cloud/news/news.hpp"
#include "../includes/cloud/ontology/ontology.hpp"
#include "../includes/cloud/speech/speech_recognition_google.hpp"
#include "../includes/cloud/speech/speech_recognition_sphinx4.hpp"
#include "../includes/cloud/speech/text_to_speech.hpp"
#include "../includes/cloud/vision/detection.hpp"
#include "../includes/cloud/vision/recognition.hpp"
#include "../includes/cloud/weather_report/weather_report.hpp"
#include "../includes/cloud/email/email.hpp"

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
    std::ifstream t("tests/data/json_classes_planned_path.json");
    std::string json_string;
    if (t.good()) {
        std::stringstream buffer;
        buffer << t.rdbuf();
        t.close();
        json_string = buffer.str();
    }
    else {
        throw std::runtime_error("failed to open ifsteam");
    }
    //plan_path_2d
    auto path_call = [] (rapp::object::planned_path pp) {
        std::chrono::nanoseconds tim2(1464949299093018853);
        auto time1 = rapp::object::time(tim2);
        auto header1 = rapp::object::msg_metadata(0 , time1, "map");
        auto quat1 = rapp::object::quaternion(0, 
                                            0, 
                                            0.17576372515799546, 
                                            0.9844323810798712);

        auto point1 = rapp::object::point(0.9999999776482582, 
                                         0.9999999776482582, 
                                         0);
        auto pose1 = rapp::object::pose(point1, quat1);
        auto ps_obj1 = rapp::object::pose_stamped(header1, pose1);
        BOOST_CHECK(pp.get_path().at(0) == ps_obj1);
        BOOST_CHECK_EQUAL(pp.get_plan(), 1);
    };
    std::chrono::nanoseconds tim(1464949299093018853);
    auto time0 = rapp::object::time(tim);
    auto header0 = rapp::object::msg_metadata(0 , time0, "map");
    auto quat = rapp::object::quaternion(0, 
                                        0, 
                                        0.17576372515799546, 
                                        0.9844323810798712);

    auto point = rapp::object::point(0.9999999776482582, 
                                     0.9999999776482582, 
                                     0);
    auto pose0 = rapp::object::pose(point, quat);
    rapp::object::pose_stamped start(header0, pose0);
    rapp::object::pose_stamped goal(header0, pose0);
    rapp::cloud::plan_path_2d pp2d("map", "robot", "algorithm", start, goal, path_call);
    pp2d.deserialise(json_string);
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

/*
 * \brief check news_explore
 * A callback is done to check that the desearilization
 * is correct comparing with a json file done manually.
 */
BOOST_AUTO_TEST_CASE(news_cloud_test)
{
    auto news_call = [] (std::vector<std::vector<std::string>> news) {
        BOOST_CHECK_EQUAL(news.at(0).at(0), "title");
        BOOST_CHECK_EQUAL(news.at(0).at(1), "content");
        BOOST_CHECK_EQUAL(news.at(0).at(2), "me");
        BOOST_CHECK_EQUAL(news.at(0).at(3), "today");
        BOOST_CHECK_EQUAL(news.at(0).at(4), "url");
    };
    rapp::cloud::news_explore ne("engine",std::vector<std::string>{{"key"}}, std::vector<std::string>{{"exclude"}}, "region", "topic", 1, news_call);
    auto j1 = R"(
              {
                "news_stories" : [{
                                    "title" : "title",
                                    "content" : "content",
                                    "publisher" : "me",
                                    "publishedDate" : "today",
                                    "url" : "url"
                                  }],
                "error" : ""
              })"_json;
    std::string j1_string = j1.dump(-1);
    ne.deserialise(j1_string);
}
/*
 * \brief check all the ontology classes
 * A callback is done to check that the desearilization
 * is correct comparing with a json file done manually 
 * \note: the name of the variables are the initial of
 *  the classes or words corresponding with json.
 */
BOOST_AUTO_TEST_CASE(ontology_cloud_test)
{
    //Class ontology_subclasses_of
    auto sub_call = [] (std::vector<std::string> classes) {
        BOOST_CHECK_EQUAL(classes.at(0), "results");
    };
    rapp::cloud::ontology_subclasses_of osub("class", true, sub_call);
    auto j1 = R"(
              {
                "results" : ["results"],
                "error" : ""
              })"_json;
    std::string j1_string = j1.dump(-1);
    osub.deserialise(j1_string);
    //Class ontology_is_superclass_of
    rapp::cloud::ontology_superclasses_of osup("class", true, sub_call);
    osup.deserialise(j1_string);
    //Class ontology_is_subsuperclass_of
    auto subsup_call = [] (bool result) {
        BOOST_CHECK_EQUAL(result, true);
    };
    rapp::cloud::ontology_is_subsuperclass_of osubsup("parent", "child", true, subsup_call);
    auto j2 = R"(
              {
                "result" : true,
                "error" : ""
              })"_json;
    std::string j2_string = j2.dump(-1);
    osubsup.deserialise(j2_string);
}

/*
 * \brief check most of the speech classes 
 * (not set_noise_profile)
 * A callback is done to check that the desearilization
 * is correct comparing with a json file done manually. 
 * \note: the name of the variables are the initial of
 *  the classes or words corresponding with json.
 */
BOOST_AUTO_TEST_CASE(speech_cloud_test)
{
    //Class speech_recognition_google
    auto google_call = [] (std::vector<std::string> words, std::vector<std::vector<std::string>> alternatives) {
        BOOST_CHECK_EQUAL(words.at(0), "words");
        BOOST_CHECK_EQUAL(alternatives.at(0).at(0), "alternative");
    };
    rapp::object::audio audio1("tests/data/object_classes_audio_4.ogg");
    rapp::cloud::speech_recognition_google srg(audio1.bytearray(), rapp::types::nao_ogg, "en", google_call);
    auto j1 = R"(
              {
                "words" : ["words"],
                "alternatives" : [["alternative"]],
                "error" : ""
              })"_json;
    std::string j1_string = j1.dump(-1);
    srg.deserialise(j1_string);
    //Class speech_recognition_sphinx4
    auto sphinx_call = [] (std::vector<std::string> words) {
        BOOST_CHECK_EQUAL(words.at(0), "words");
    };
    rapp::object::audio audio2("tests/data/yes-no.wav");
    rapp::cloud::speech_recognition_sphinx4 srs(  audio2.bytearray(),
                                                  rapp::types::headset,
                                                  "en",
                                                  std::vector<std::string>({{}}),
                                                  std::vector<std::string>({{}}),
                                                  std::vector<std::string>({{}}),
                                                  sphinx_call
                                                );
    auto j2 = R"(
              {
                "words" : ["words"],
                "error" : ""
              })"_json;
    std::string j2_string = j2.dump(-1);
    srs.deserialise(j2_string);
    //Class text_to_speech
    auto text_to_speech_call_1 = [] (rapp::object::audio test1) {
        rapp::object::audio test2(test1);
        BOOST_CHECK(test1 == test2);
    };
    rapp::cloud::text_to_speech tts("Hello", "en", text_to_speech_call_1);
    auto j3 = R"(
              {
                "payload" : "UklGRua2AABXQVZFZm10IBAAAAABAAEAgD4AAAB9AAACABAAZGF0YcK2AAABAAAA//8BAAAAAAAAAAAA",
                "error": ""
              })"_json;
    std::string j3_string = j3.dump(-1);
    tts.deserialise(j3_string);
}

/*
 * \brief check all the vision classes (detection and 
 * recognition).
 * A callback is done to check that the desearilization
 * is correct comparing with a json file done manually 
 * \note: the name of the variables are the initial of
 *  the classes or words corresponding with json.
 */
BOOST_AUTO_TEST_CASE(vision_cloud_test)
{
    //Class face_detection
    auto face_call = [] (std::vector<rapp::object::face> faces) {
        BOOST_CHECK_EQUAL(faces.at(0).get_left_x(), 1);
        BOOST_CHECK_EQUAL(faces.at(0).get_left_y(), 2);   
        BOOST_CHECK_EQUAL(faces.at(0).get_right_x(), 3);
        BOOST_CHECK_EQUAL(faces.at(0).get_right_y(), 4);

    };
    auto pic = rapp::object::picture("tests/data/object_classes_picture_1.png");
    rapp::cloud::face_detection fd(pic, false, face_call); 
    auto j1 = R"(
              {
                "faces":[{ 
                            "up_left_point":{
                                                "x": 1, 
                                                "y": 2
                            }, 
                            "down_right_point":{
                                                "x": 3, 
                                                "y": 4
                            } 
                 }],
                 "error" : ""
               })"_json;
    std::string j1_string = j1.dump(-1);
    fd.deserialise(j1_string);
    //Class door_angle_detection
    auto door_call = [] (double angle) {
        BOOST_CHECK_EQUAL(angle, 5);
    };
    rapp::cloud::door_angle_detection dad(pic, door_call);
    auto j2 = R"(
              {
                "door_angle" : 5,
                "error" : ""
              })"_json;
    std::string j2_string = j2.dump(-1);
    dad.deserialise(j2_string);
    //Class light_detection
    auto light_call = [] (int level) {
       BOOST_CHECK_EQUAL(level, 500);
    };
    rapp::cloud::light_detection ld(pic, light_call);
    auto j3 = R"(
              {
                "light_level" : 500,
                "error" : ""
              })"_json;
    std::string j3_string = j3.dump(-1);
    ld.deserialise(j3_string); 
    //Class human_detection
    auto human_call = [] (std::vector<rapp::object::human> humans) {
        BOOST_CHECK_EQUAL(humans.at(0).get_left_x(), 1);
        BOOST_CHECK_EQUAL(humans.at(0).get_left_y(), 2);   
        BOOST_CHECK_EQUAL(humans.at(0).get_right_x(), 3);
        BOOST_CHECK_EQUAL(humans.at(0).get_right_y(), 4);

    };
    rapp::cloud::human_detection hd(pic,human_call);
    auto j4 = R"(
              {
                  "humans":[{ 
                              "up_left_point":{
                                                  "x": 1, 
                                                  "y": 2
                              }, 
                              "down_right_point":{
                                                  "x": 3, 
                                                  "y": 4
                              } 
                  }],
                  "error" : ""
              })"_json;
    std::string j4_string = j4.dump(-1);
    hd.deserialise(j4_string);
    //Class qr_detection
    auto qr_call = [] (std::vector<rapp::object::qr_code> qrs) {
        BOOST_CHECK_EQUAL(qrs.at(0).label(), "label");
        rapp::object::qr_code qr2(1 ,2, "label");
        BOOST_CHECK(qrs.at(0) == qr2);
    };
    rapp::cloud::qr_detection qd(pic, qr_call);
    auto j5 = R"(
              {
                "qr_centers":[{ 
                                "x": 1, 
                                "y": 2
                              }], 
                "qr_messages":["label"],
                "error" : ""
              })"_json;
    std::string j5_string = j5.dump(-1);
    qd.deserialise(j5_string);
    //Class object_recognition
    auto object_call = [] (std::string object) {
        BOOST_CHECK_EQUAL(object, "something");
    };
    rapp::cloud::object_recognition objr(pic, object_call);
    auto j6 = R"(
              {
                "object_class" : "something",
                "error" : ""
              })"_json;
    std::string j6_string = j6.dump(-1);
    objr.deserialise(j6_string);

}

/*
 * \brief check all the weather_report classes
 * A callback is done to check that the desearilization
 * is correct comparing with a json file done manually 
 * \note: the name of the variables are the initial of
 *  the classes or words corresponding with json.
 */
BOOST_AUTO_TEST_CASE(weather_cloud_test) 
{
    //Class weather_report_current
    auto report_call = [] (std::vector<std::string> weather) {
        BOOST_CHECK_EQUAL(weather.at(0), "date"); 
        BOOST_CHECK_EQUAL(weather.at(1), "temp");
        BOOST_CHECK_EQUAL(weather.at(2), "description");
        BOOST_CHECK_EQUAL(weather.at(3), "humidity");
        BOOST_CHECK_EQUAL(weather.at(4), "visible");
        BOOST_CHECK_EQUAL(weather.at(5), "pressure");
        BOOST_CHECK_EQUAL(weather.at(6), "speed");
        BOOST_CHECK_EQUAL(weather.at(7), "25C");
        BOOST_CHECK_EQUAL(weather.at(8), "direction");
    };
    rapp::cloud::weather_report_current wrc("Madrid", "reporter", 1, report_call);
    auto j1 = R"(
              {
                "date" : "date",
                "temperature" : "temp",
                "weather_description" : "description",
                "humidity" : "humidity",
                "visibility" : "visible",
                "pressure" : "pressure",
                "wind_speed" : "speed",
                "wind_temperature" : "25C",
                "wind_direction" : "direction"
              }
              )"_json;
    std::string j1_string = j1.dump(-1);
    wrc.deserialise(j1_string);
    //Class weather_report_forecast
    auto forecast_call = [] (std::vector<std::vector<std::string>> forecasts) {
        BOOST_CHECK_EQUAL(forecasts.at(0).at(0), "40C"); 
        BOOST_CHECK_EQUAL(forecasts.at(0).at(1), "30C");
        BOOST_CHECK_EQUAL(forecasts.at(0).at(2), "hot");
        BOOST_CHECK_EQUAL(forecasts.at(0).at(3), "today");
    };
    rapp::cloud::weather_report_forecast wrf("Madrid", "reporter", 1, forecast_call);
    auto j2 = R"(
              {
                "forecast" : [{ 
                                "high_temp" : "40C",
                                "low_temp" : "30C",
                                "description" : "hot",
                                "date" : "today"
                }],
                "error" : ""
              })"_json;
    std::string j2_string = j2.dump(-1);
    wrf.deserialise(j2_string);
}

/*
 * \brief check all the email classes 
 * A callback is done to check that the desearilization
 * is correct comparing with a json file done manually 
 * \note: the name of the variables are the initial of
 *  the classes or words corresponding with json.
 */BOOST_AUTO_TEST_CASE(email_cloud_test)
{
    //Class email_fetch
    auto fetch_call = [] (std::vector<std::tuple<std::string, 
                                                 std::vector<std::string>,
                                                 std::string,
                                                 std::string,
                                                 std::vector<std::string>>> emails)
    {
        BOOST_CHECK_EQUAL(std::get<0>(emails.at(0)), "me");
        BOOST_CHECK_EQUAL(std::get<1>(emails.at(0)).at(0), "you");
        BOOST_CHECK_EQUAL(std::get<2>(emails.at(0)), "body");
        BOOST_CHECK_EQUAL(std::get<3>(emails.at(0)), "today");
        BOOST_CHECK_EQUAL(std::get<4>(emails.at(0)).at(0), "nothing");
    };
    rapp::cloud::email_fetch ef("mail", "", "imap", "1", "ALL", 0, 0, 2, fetch_call);
    auto j1 = R"(
              {
                "emails" : [{
                              "sender" : "me",
                              "receivers" : ["you"],
                              "body" : "body",
                              "date" : "today",
                              "attachments" : ["nothing"]
                }],
                "error" : ""
              })"_json;
    std::string j1_string = j1.dump(-1);
    ef.deserialise(j1_string);
    //Class email_send
    auto send_call = [] (std::string error) {
        BOOST_CHECK_EQUAL(error, "");
    };
    rapp::cloud::email_send es("mail", "", "smtp", "1",std::vector<std::string>({{}}), "b", "t", send_call);
    auto j2 = R"(
              {
                "error" : ""
              })"_json;
    std::string j2_string = j2.dump(-1);
    es.deserialise(j2_string);
}
BOOST_AUTO_TEST_SUITE_END()
