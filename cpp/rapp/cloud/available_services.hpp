#ifndef RAPP_CLOUD_AVAILABLE_SERVICES
#define RAPP_CLOUD_AVAILABLE_SERVICES
#include "includes.ihh"
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
#include <rapp/cloud/asio/http_request.hpp>

namespace rapp {
namespace cloud {
/**
 * \class available_services
 * \brief requests available services from platform
 * \version 0.7.0
 * \date 14 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class available_services : public http_request
{
public:
	typedef std::pair<std::string, std::string> service;

    /**
     * \brief construct without any special parameters
     * \param callback will receive a vector of services strings
     */
    available_services(std::function<void(std::vector<service>)> callback);
    
    /**
     * \brief handle platform's JSON reply
     */
    void deserialise(std::string json);

private:
    /// user's handler
    std::function<void(std::vector<service> services)> delegate_;
};
}
}
#endif
