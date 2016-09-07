#include "weather_report.hpp"
namespace rapp {
namespace cloud {

weather_report_current::weather_report_current(
                                                const std::string city,
                                                const std::string weather_reporter,
                                                const unsigned int metric,
                                                std::function<void(std::vector<std::string>)> callback
                                              )
: http_request("POST /hop/weather_report_current HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    json json_doc = {{"city", city},
                     {"weather_reporter", weather_reporter},
                     {"metric", metric}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}
/**
 * \brief handle platform's JSON reply
 */
void weather_report_current::deserialise(std::string json) const
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

    //There is no "error" in JSON
 
    /*auto error = misc::get_json_value<std::string>("error", json_f);
    if (!error.empty()) {
        std::cerr << "error JSON: " << error <<std::endl;
    }
    else {*/
        std::vector<std::string> weather ={ json_f["date"],
                                            json_f["temperature"],
                                            json_f["weather_description"],
                                            json_f["humidity"],
                                            json_f["visibility"],
                                            json_f["pressure"],
                                            json_f["wind_speed"],
                                            json_f["wind_temperature"],
                                            json_f["wind_direction"] };
        delegate_(weather);
    //}
}

weather_report_forecast::weather_report_forecast(
                                                  const std::string city,
                                                  const std::string weather_reporter,
                                                  const unsigned int metric,
                                                  std::function<void(std::vector<std::vector<std::string>>)> callback
                                                )
: http_request("POST /hop/weather_report_forecast HTTP/1.1\r\n"), 
  delegate_(callback)
{

    http_request::make_multipart_form();
    json json_doc = {{"city", city},
                     {"weather_reporter", weather_reporter},
                     {"metric", metric}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();

}
/**
 * \brief handle platform's JSON reply
 */
void weather_report_forecast::deserialise(std::string json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    std::vector<std::vector<std::string>> forecasts;
    nlohmann::json json_f;
    try {
        json_f = json::parse(json);
    }
    catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
    auto error = misc::get_json_value<std::string>("error", json_f);
    if (!error.empty()) {
        std::cerr << "error JSON: " << error <<std::endl;
    }
    else {
        for (auto obj : json_f["forecast"]) {
            std::vector<std::string> forecast = {misc::get_json_value<std::string>("high_temp", obj), 
                                                 misc::get_json_value<std::string>("low_temp", obj), 
                                                 misc::get_json_value<std::string>("description", obj), 
                                                 misc::get_json_value<std::string>("date", obj)};
            forecasts.push_back(forecast);
        }
        delegate_(forecasts);
    }
}

}
}
