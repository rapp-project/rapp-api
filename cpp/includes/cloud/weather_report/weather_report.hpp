#ifndef RAPP_CLOUD_WEATHER_REPORT
#define RAPP_CLOUD_WEATHER_REPORT
#include "includes.ihh"
namespace rapp {
namespace cloud {

/**
 * \brief get current weather report
 * \class weather_report_current
 * \version 0.6.0
 * \date May 2016
 */
class weather_report_current : public asio_http
{
public:
    /**
     * \param city: location for the weather report query
     * \param weather_reporter: the weather API to use
     * \param metric: the return value type
     * \param token: the rapp auth token
     * \param callback: receives a JSON reply 
     */
    weather_report_current(
                            const std::string city,
                            const std::string weather_reporter,
                            const unsigned int metric,
                            std::function<void(std::string)> callback
                          )
    : asio_http(), delegate_(callback)
    {
        boost::property_tree::ptree tree;
        tree.put("city", city);
        tree.put("weather_reporter", weather_reporter);
        tree.put("metric", boost::lexical_cast<std::string>(metric));
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        post_ = ss.str();

		// set the HTTP header URI pramble and the Content-Type
        head_preamble_.uri = "POST /hop/weather_report_current HTTP/1.1\r\n";
        head_preamble_.content_type = "Content-Type: application/x-www-form-urlencoded\r\n";

        callback_ = std::bind(&weather_report_current::handle_reply, this, std::placeholders::_1);
    }
private:
    /**
     * \brief handle platform's JSON reply
     */
	void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        delegate_(std::move(json));
    }
    /// 
    std::function<void(std::string)> delegate_;
};

/**
 * \brief get weather forecast
 * \class weather_report_forecast
 * \version 0.6.0
 * \date May 2016
 */
class weather_report_forecast : public asio_http
{
public:
    /**
     * \param city: location of the weather forecast query
     * \param weather_reporter: weather API being queried
     * \param metric return value units
     * \param token: the rapp auth token
     * \param callback: receives a JSON reply
     */
     weather_report_forecast(
                              const std::string city,
                              const std::string weather_reporter,
                              const unsigned int metric,
                              std::function<void(std::string)> callback
                            )
    : asio_http(), delegate_(callback)
    {
        boost::property_tree::ptree tree;
        tree.put("city", city);
        tree.put("weather_reporter", weather_reporter);
        tree.put("metric", boost::lexical_cast<std::string>(metric));

		std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

		std::string boundary = rapp::misc::random_boundary();
        post_  = "--" + boundary + "\r\n"
               + "Content-Disposition: form-data; name=\"json\"\r\n\r\n";

		// JSON PDT value unquote
		post_ += misc::json_unquote_pdt_value<unsigned int>()(ss.str(), metric);

		// set the HTTP header URI pramble and the Content-Type
        head_preamble_.uri = "POST /hop/weather_report_forecast HTTP/1.1\r\n";
        head_preamble_.content_type = "Content-Type: multipart/form-data; boundary=" + boundary;

        callback_ = std::bind(&weather_report_forecast::handle_reply, this, std::placeholders::_1);
    }
private:
    /**
     * \brief handle platform's JSON reply
     */
	void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        delegate_(std::move(json));
    }
    /// 
    std::function<void(std::string)> delegate_;
};
}
}
#endif
