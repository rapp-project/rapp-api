#include "cognitive_exercises.hpp"
namespace rapp {
namespace cloud {

//Class Cognitive_test_selector
cognitive_test_selector::cognitive_test_selector(
                        const std::string test_type,
                        const std::string test_subtype,
                        const std::string test_diff,
                        const std::string test_index,
                        functor callback
                       )
:http_request("POST /hop/cognitive_test_selector HTTP/1.1\r\n"), 
 delegate_(callback)
{
    std::string ss;
    json json_doc = {{"test_type", test_type},
                        {"test_subtype", test_subtype},
                        {"test_diff", test_diff},
                        {"test_index", test_index}};

    ss = json_doc.dump(4);
    http_request::add_content("json", ss, false);

}

/**
 * \brief handle platform's JSON reply
 */
void cognitive_test_selector::deserialise(std::string json) const
{
    //std::stringstream ss(json);
    std::vector<std::string> questions;
    std::vector<std::string> possib_ans;
    std::vector<std::string> correct_ans;
    std::string test_instance;
    std::string test_type;
    std::string test_subtype;

    std::string current_class = "cognitive_test_selector";
   
    auto json_f = json::parse(json);
     
    if (!json.empty()) {

        // Get "questions" from json
        rapp::misc::get_value_from_json(current_class, "questions", json_f, questions);

        // Get "possib_ans" from json
        rapp::misc::get_value_from_json(current_class, "possib_ans", json_f, possib_ans);

        // Get "correct_ans" from json
        rapp::misc::get_value_from_json(current_class, "correct_ans", json_f, correct_ans);

        // Get "test_instance" from json 
        rapp::misc::get_value_from_json(current_class, "test_instance", json_f, test_instance);
        
        // Get "test_type" from json
        rapp::misc::get_value_from_json(current_class, "test_type", json_f, test_type);
        
        // Get "test_subtype" from json
        rapp::misc::get_value_from_json(current_class, "test_subtype", json_f, test_subtype);

        // Get error from json
        std::string error;
        rapp::misc::get_value_from_json(current_class, "error", json_f, error);
        if (!error.empty()) {
            std::cerr << "cognitive_test_selector JSON error: " << error <<std::endl;
        }
    }
    else {
        throw std::runtime_error("json is empty");
    }

    delegate_(questions,
              possib_ans,
              correct_ans,
              test_instance,
              test_type,
              test_subtype);
}

/// Class cognitive_record_performance
cognitive_record_performance::cognitive_record_performance(
                                                            const std::string test_instance,
                                                            const float score,
                                                            std::function<void(std::string)> callback
                                                          )
: http_request("POST /hop/cognitive_record_performance HTTP/1.1\r\n"),
  delegate_(callback)
{
    std::string ss;
    json json_string = {{"test_instance", test_instance}, {"score", score}};
    ss = json_string.dump(4);
    http_request::add_content("json", ss, false);
    http_request::close();

}

void cognitive_record_performance::deserialise(std::string json) const
{
    std::string performance_entry;
    std::string current_class = "cognitive_record_performance";

    auto json_f = json::parse(json);

    if (!json.empty()) {

        // Get "performance_entry" from json
        rapp::misc::get_value_from_json(current_class, "performance_entry", json_f, performance_entry);

        // Get error from json
        std::string error;
        rapp::misc::get_value_from_json(current_class, "error", json_f, error);
        if (!error.empty()) {
            std::cerr << "cognitive_record_performance JSON error: " << error <<std::endl;
        }
    }
    else {
        throw std::runtime_error("json is empty");
    }
    delegate_(performance_entry);
}

/// Class cognitive_get_history
cognitive_get_history::cognitive_get_history(
                        unsigned int from_time,
                        unsigned int to_time,
                        const std::string test_type,
                        std::function<void(std::string)> callback
                     )
: http_request("POST /hop/cognitive_get_history HTTP/1.1\r\n"), 
  delegate_(callback)
{
    std::string ss;
    json json_string = {{"from_time", from_time}, 
                        {"to_time", to_time}, 
                        {"test_type", test_type}};

    ss = json_string.dump(4);
    http_request::add_content("json", ss, false);
    http_request::close();

}

void cognitive_get_history::deserialise(std::string json) const
{
    std::string records;
    std::string current_class = "cognitive_get_history";

    auto json_f = json::parse(json);

    //Get "results" from json
    rapp::misc::get_value_from_json(current_class, "records", json_f, records);

    // Get error from json
    std::string error;
    rapp::misc::get_value_from_json(current_class, "error", json_f, error);
    if (!error.empty()) {
        std::cerr << "cognitive_get_history JSON error: " << error <<std::endl;
    }

    delegate_(records);
}

/// Class cognitive_get_scores
cognitive_get_scores::cognitive_get_scores(
                      unsigned int up_to_time,
                      const std::string test_type,
                      std::function<void(std::vector<unsigned int>, std::vector<float>)> callback
                    )
: http_request("POST /hop/cognitive_get_scores HTTP/1.1\r\n"), 
  delegate_(callback)
{
    std::string ss;
    json json_string = {{"up_to_time", up_to_time}, 
                        {"test_type", test_type}};

    ss = json_string.dump(4);
    http_request::add_content("json", ss, false);
    http_request::close();

}

void cognitive_get_scores::deserialise(std::string json) const
{
    std::vector<unsigned int> test_classes;
    std::vector<float> scores;
    std::string current_class = "cognitive_get_scores";
    
    auto json_f = json::parse(json);
    
    if (!json.empty()) {

        // Get "test_current_classes" from json
        rapp::misc::get_value_from_json(current_class, "test_classes", json_f, test_classes);

        // Get "scores" from json
        rapp::misc::get_value_from_json(current_class, "scores", json_f, scores);

        // Get error from json
        std::string error;
        rapp::misc::get_value_from_json(current_class, "error", json_f, error);

        if (!error.empty()) {
            std::cerr << "cognitive_get_scores JSON error: " << error <<std::endl;
        }
    }
    else {
        throw std::runtime_error("json is empty");
    }

    delegate_(test_classes, scores);
}

}
}
