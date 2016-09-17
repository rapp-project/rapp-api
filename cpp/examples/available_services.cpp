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
#include <rapp/cloud/available_services.hpp>
#include <iostream>
/*
 * \brief Example to show how available_services works
 */
int main(int argc, char* argv[])
{
    /*
     * Construct the platform info setting the hostname/IP, port and authentication token
     * Then proceed to create a cloud controller.
     * We'll use this object to create cloud calls to the platform.
     */
	rapp::cloud::platform info = {"rapp.ee.auth.gr", "9001", "rapp_token"}; 
	rapp::cloud::service_controller ctrl(info);

    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a list of services and print them on stdout.
     */
	auto cb = [](std::vector<std::pair<std::string, std::string>> services) {
         std::cout << "available services: " << std::endl;
         for (const auto & pair : services) {
            std::cout << pair.first << " " << pair.second << std::endl;
         }
     };

	/*
     * Finally we make the call.
     * The simplest way to use the `make_call` template function, specifying
     * as template type the actual cloud call, in this case the `available_services` class.
     * This method will **block** until its complete.
     * For more information \see rapp::cloud::available_services
     */
	ctrl.make_call<rapp::cloud::available_services>(cb);
	return 0;
}
