#ifndef RAPP_CLOUD_GEOLOCATION
#define RAPP_CLOUD_GEOLOCATION
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
#include <rapp/cloud/asio/http_request.hpp>
namespace rapp {
namespace cloud {
/**
 * \brief geolocation service
 * \class geolocation
 * \version 0.7.0
 * \date September 2016
 * \author Alex Gkiokas ,a.gkiokas@ortelio.co.uk>
 */
class geolocation : public http_request
{
public:
    /**
     * \param ipaddr: the machine's ip
     * \param engine: the API (default ip-api)
     * \param callback: receives a JSON reply
     */
    geolocation(
                 const std::string ipaddr,
                 const std::string engine,
                 std::function<void(std::string,
                                    std::string,
                                    std::string,
                                    float,
                                    float,
                                    std::string,
                                    std::string)> callback
               );

    /**
     * \brief handle platform's JSON reply
     */
	void deserialise(std::string json) const;

private:   

    ///Member 
    std::function<void(std::string,
                       std::string,
                       std::string,
                       float,
                       float,
                       std::string,
                       std::string)> delegate_;
};
}
}
#endif
