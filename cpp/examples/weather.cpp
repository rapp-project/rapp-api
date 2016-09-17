/*
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
#include <rapp/cloud/service_controller.hpp>
#include <rapp/cloud/weather_report.hpp>
/*
 * \brief Example to take the weather report of a city 
 */
int main()
{
   /*
    * Construct the platform info setting the hostname/IP, port and authentication token
    * Then proceed to create a cloud controller.
    * We'll use this object to create cloud calls to the platform.
    */
    rapp::cloud::platform info = {"rapp.ee.auth.gr", "9001", "rapp_token"}; 
    rapp::cloud::service_controller ctrl(info);

    /*
     * Example of weather_report_current
     *
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a vector of string and we show all 
     * the parameters about weather
     */
     auto callback = [&](std::vector<std::string> weather) {
        std::cout << "Date: " << weather.at(0) << std::endl;
        std::cout << "Temperature: " << weather.at(1) << std::endl;
        std::cout << "Description: " << weather.at(2) << std::endl;
        std::cout << "Humidity: " << weather.at(3) << std::endl;
        std::cout << "Visibility: " << weather.at(4) << std::endl;
        std::cout << "Pressure: " << weather.at(5) << std::endl;
        std::cout << "Wind speed: " << weather.at(6) << std::endl;
        std::cout << "Wind Temperature: " << weather.at(7) << std::endl;
        std::cout << "Wind Direction: " << weather.at(8) << std::endl;
     };

    /*
     * We make a call to weather_report_current to get the information
     * about the weather in the city that we want
     * For more information \see rapp::cloud::weather_report_current
     */
    ctrl.make_call<rapp::cloud::weather_report_current>("Athens", "", 1, callback);
   
    /*
     * Example of weather_report_forecast
     *
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a vector of string and we show all 
     * the parameters about weather forecast
     */
     auto call_forecast = [&](std::vector<std::vector<std::string>> forecasts) {
        for (auto vector_forecast : forecasts) {
            std::cout << "High Temp: " << vector_forecast.at(0) << std::endl;
            std::cout << "Low Temp: " << vector_forecast.at(1) << std::endl;
            std::cout << "Description: " << vector_forecast.at(2) << std::endl;
            std::cout << "Date: " << vector_forecast.at(3) << std::endl;
            std::cout << " ---- " <<std::endl;
        }
     };

    /*
     * We make a call to weather_report_forecast to get the weather in a city
     * during the different parts of the day
     * For more information \see rapp::cloud::weather_report_forecast
     */
    ctrl.make_call<rapp::cloud::weather_report_forecast>("Athens", "", 0, call_forecast);
    return 0;
}
