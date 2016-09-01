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

#include "cloud/service_controller/service_controller.hpp"
#include "cloud/ontology/ontology.hpp"
#include <iostream>
///
/// query subclasses and superclass of of argv[1]
///
// whats the argument Maria?
int main(int argc, char* argv[])
{
    if (argc > 1) {
        std::cout << "query sub/super classes of: " << argv[1] << std::endl;
        std::string query = argv[1];

       /**
        * Construct the platform info setting the hostname/IP, port and authentication token
        * Then proceed to create a cloud controller.
        * We'll use this object to create cloud calls to the platform.
        */
        rapp::cloud::platform info = {"rapp.ee.auth.gr", "9001", "rapp_token"}; 
		rapp::cloud::service_controller ctrl(info);

        /**
         * Construct a lambda, std::function or bind your own functor.
         * In this example we'll pass an inline lambda as the callback.
         * All it does is receive a list of services and print them on stdout.
         */
        auto subclass_cb = [](std::vector<std::string> classes) { 
            std::cout << "sub classes: " << std::endl;
            for (const auto & str : classes) {
                std::cout << str << std::endl;
            }
        };

        auto superclass_cb = [](std::vector<std::string> classes) { 
            std::cout << "super classes: " << std::endl;
            for (const auto & str : classes) {
                std::cout << str << std::endl;
            }
        };

		ctrl.make_call<rapp::cloud::ontology_subclasses_of>(query, true, subclass_cb);
		ctrl.make_call<rapp::cloud::ontology_superclasses_of>(query, false, superclass_cb);

        return 0;
    }
}
