#ifndef RAPP_CLOUD_WEATHER_REPORT
#define RAPP_CLOUD_WEATHER_REPORT
/**
 * Copyright 2015 RAPP
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * #http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "includes.ihh"
namespace rapp {
namespace cloud {

/**
 * \brief get current weather report
 * \class weather_report_current
 * \version 0.7.0
 * \date September 2016
 * \author Maria Ramos Montero <m.ramos@ortelio.co.uk>
 */
class weather_report_current : public http_request
{
public:
    typedef std::function<void(std::string,
                               std::string,
                               std::string,
                               std::string,
                               std::string,
                               std::string,
                               std::string,
                               std::string,
                               std::string)> functor;

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
                            functor callback
                          );
    
    /**
     * \brief handle platform's JSON reply
     */
	void deserialise(std::string json) const;

private:
    /// 
    functor delegate_;
};

/**
 * \brief get weather forecast
 * \class weather_report_forecast
 * \version 0.7.0
 * \date September 2016
 * \author Maria Ramos Montero <m.ramos@ortelio.co.uk>
 */
class weather_report_forecast : public http_request
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
                            );
    /**
     * \brief handle platform's JSON reply
     */
	void deserialise(std::string json) const;
    
private:
    /// 
    std::function<void(std::string)> delegate_;
};
}
}
#endif
