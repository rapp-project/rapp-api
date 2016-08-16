#ifndef RAPP_CLOUD_WEATHER_REPORT
#define RAPP_CLOUD_WEATHER_REPORT
#include "includes.ihh"
namespace rapp {
namespace cloud {

/**
 * \brief get current weather report
 * \class weather_report_current
 * \version 0.7.0
 * \date 15 August 2016
 */
class weather_report_current : public caller, public http_request
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
    : http_header("POST /hop/weather_report_current HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()), 
      delegate_(callback)
    {
        boost::property_tree::ptree tree;
        tree.put("city", city);
        tree.put("weather_reporter", weather_reporter);
        tree.put("metric", boost::lexical_cast<std::string>(metric));
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        
        std::string json = ss.str();
        http_post::add_content("json", json, false); 
        http_post::end();
        //The previous code only sent the string json
        //without boundaries
        //post_ = ss.str();

    }
    /**
     * \brief handle platform's JSON reply
     */
	void deserialise(std::string json) const
    {
        std::stringstream ss(json);
        delegate_(std::move(json));
    }

    /**
    * \brief method to fill the buffer with http_post and http_header information
    * \param info is the data of the platform    
    */
    boost::asio::streambuf fill_buffer(rapp::cloud::platform info)
    {
           return std::move(http_request::fill_buffer(info));
    }

private:
    /// 
    std::function<void(std::string)> delegate_;
};

/**
 * \brief get weather forecast
 * \class weather_report_forecast
 * \version 0.7.0
 * \date 15 August 2016
 */
class weather_report_forecast : public caller, public http_request
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
    : http_header("POST /hop/weather_report_forecast HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()), 
      delegate_(callback)
    {
        boost::property_tree::ptree tree;
        tree.put("city", city);
        tree.put("weather_reporter", weather_reporter);
        tree.put("metric", boost::lexical_cast<std::string>(metric));

		std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

		// JSON PDT value unquote
        std::string json = misc::json_unquote_pdt_value<unsigned int>()(ss.str(), metric);
        http_post::add_content("json", json, false); 
        http_post::end();
    
    }
    /**
     * \brief handle platform's JSON reply
     */
	void deserialise(std::string json) const
    {
        std::stringstream ss(json);
        delegate_(std::move(json));
    }

    /**
    * \brief method to fill the buffer with http_post and http_header information
    * \param info is the data of the platform    
    */
    boost::asio::streambuf fill_buffer(rapp::cloud::platform info)
    {
           return std::move(http_request::fill_buffer(info));
    }

private:
    /// 
    std::function<void(std::string)> delegate_;
};
}
}
#endif
