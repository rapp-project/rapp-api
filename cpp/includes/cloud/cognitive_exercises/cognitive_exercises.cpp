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
    json json_string = {{"test_type", test_type},
                        {"test_subtype", test_subtype},
                        {"test_diff", test_diff},
                        {"test_index", test_index}};

    ss = json_string.dump(4);
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
   
    auto json_f = json::parse(json);
     
    if (!json.empty()) {

        // Get "questions" from json
        const auto it = json_f.find("questions");
        if (it == json_f.end()){
            throw std::runtime_error("no questions in cognitive exercise");
        }
        else {
            questions = it->get<std::vector<std::string>>();
        }

        // Get "possib_ans" from json
        json::const_iterator it_pa = json_f.find("possib_ans");
        if (it_pa == json_f.end()){
            throw std::runtime_error("no possible answers in cognitive exercise");
        }
        else {
            possib_ans = it_pa->get<std::vector<std::string>>();
        }

        // Get "correct_ans" from json
        json::const_iterator it_ca = json_f.find("correct_ans");
        if (it_ca == json_f.end()){
            throw std::runtime_error("no correct answers in cognitive exercise");
        }
        else {
            correct_ans = it_ca->get<std::vector<std::string>>();
        }

        // Get "test_instance" from json 
        json::const_iterator it_ti = json_f.find("test_instance");
        if (it_ti == json_f.end()){
            throw std::runtime_error("no test instance in cognitive exercise");
        }
        else {
            test_instance = it_ti->get<std::string>();
        }
        
        // Get "test_type" from json
        json::const_iterator it_type = json_f.find("test_type");
        if (it_type == json_f.end()){
            throw std::runtime_error("no test type in cognitive exercise");
        }
        else {
            test_type = it_type->get<std::string>();
        }

        // Get "test_subtype" from json
        json::const_iterator it_sub = json_f.find("test_subtype");
        if (it_sub== json_f.end()){
            throw std::runtime_error("no test subtype in cognitive exercise");
        }
        else {
            test_subtype = it_sub->get<std::string>();
        }

        // Get error from json
        json::const_iterator it_error = json_f.find("error");
        if (it_error== json_f.end()){
            throw std::runtime_error("no error param in cognitive exercise");
        }
        else {
            std::string error = it_error->get<std::string>();
            if (!error.empty()) {
                std::cerr << "cognitive_test_selector JSON error: " << error <<std::endl;
            }
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
    auto json_f = json::parse(json);

    if (!json.empty()) {

        // Get "performance_entry" from json
        json::const_iterator it =json_f.find("performance_entry");
        if (it == json_f.end()){
            throw std::runtime_error("no performance entry in cognitive exercise");
        }
        else {
            performance_entry = it->get<std::string>();
        }

        // Get error from json
        json::const_iterator it_error = json_f.find("error");
        if (it_error== json_f.end()){
            throw std::runtime_error("no error param in cognitive exercise");
        }
        else {
            std::string error = it_error->get<std::string>();
            if (!error.empty()) {
                std::cerr << "cognitive_record_performance JSON error: " << error <<std::endl;
            }
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
    delegate_(std::move(json));
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
    
    auto json_f = json::parse(json);
    
    if (!json.empty()) {

        // Get "test_classes" from json
        json::const_iterator it =json_f.find("test_classes");
        if (it == json_f.end()){
            throw std::runtime_error("no test classes in cognitive exercise");
        }
        else {
            test_classes = it->get<std::vector<unsigned int>>();
        }

        // Get "scores" from json
        json::const_iterator it_sc =json_f.find("scores");
        if (it_sc == json_f.end()){
            throw std::runtime_error("no scores in cognitive exercise");
        }
        else {
            scores = it_sc->get<std::vector<float>>();
        }
        // Get error from json
        json::const_iterator it_error = json_f.find("error");
        if (it_error== json_f.end()){
            throw std::runtime_error("no error param in cognitive exercise");
        }
        else {
            std::string error = it_error->get<std::string>();
            if (!error.empty()) {
                std::cerr << "cognitive_get_scores JSON error: " << error <<std::endl;
            }
        }
    }
    else {
        throw std::runtime_error("json is empty");
    }

    delegate_(test_classes, scores);
}

}
}
