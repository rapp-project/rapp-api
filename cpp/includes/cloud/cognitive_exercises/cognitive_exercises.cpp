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
    http_request::make_multipart_form();
    json json_doc = {{"test_type", test_type},
                     {"test_subtype", test_subtype},
                     {"test_diff", test_diff},
                     {"test_index", test_index}};
    http_request::add_content("json", json_doc.dump(-1), true);
}

/**
 * \brief handle platform's JSON reply
 */
void cognitive_test_selector::deserialise(std::string json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    try {
        json_f = json::parse(json);
    }
    catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
    auto error = misc::get_json_value<std::string>("error", json_f);
    if (!error.empty()) {
        std::cerr << "ontology_superclasses_of JSON: " << error <<std::endl;
    }
    else {
        delegate_(json_f["questions"],
                  json_f["possib_ans"],
                  json_f["correct_ans"],
                  json_f["test_intance"],
                  json_f["test_type"],
                  json_f["test_subtype"]);
    }
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
    http_request::make_multipart_form();
    json json_doc = {{"test_instance", test_instance}, 
                     {"score", score}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

void cognitive_record_performance::deserialise(std::string json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    try {
        json_f = json::parse(json);
    }
    catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
    auto error = misc::get_json_value<std::string>("error", json_f);
    if (!error.empty()) {
        std::cerr << "ontology_superclasses_of JSON: " << error <<std::endl;
    }
    else {
        delegate_(json_f["performance_entry"]);
    }
}

/// Class cognitive_get_history
cognitive_get_history::cognitive_get_history(
                                                unsigned int from_time,
                                                unsigned int to_time,
                                                const std::string test_type,
                                                std::function<void(const nlohmann::json::const_iterator &)> callback
                                             )
: http_request("POST /hop/cognitive_get_history HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    json json_doc = {{"from_time", from_time}, 
                     {"to_time", to_time}, 
                     {"test_type", test_type}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

void cognitive_get_history::deserialise(std::string json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    try {
        json_f = json::parse(json);
    }
    catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
    auto error = misc::get_json_value<std::string>("error", json_f);
    if (!error.empty()) {
        std::cerr << "ontology_superclasses_of JSON: " << error <<std::endl;
    }
    else {
        delegate_(json_f.find("records"));
    }
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
    http_request::make_multipart_form();
    json json_doc = {{"up_to_time", up_to_time}, 
                     {"test_type", test_type}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

void cognitive_get_scores::deserialise(std::string json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    try {
        json_f = json::parse(json);
    }
    catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
    auto error = misc::get_json_value<std::string>("error", json_f);
    if (!error.empty()) {
        std::cerr << "cognitive_get_scores JSON: " << error <<std::endl;
    }
    else {
        delegate_(json_f["test_classes"],
                  json_f["scores"]);
    }
}

}
}
