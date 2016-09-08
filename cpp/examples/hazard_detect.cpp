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
#include "cloud/vision/detection.hpp"
#include "objects/picture/picture.hpp"
/**
 * \brief example to detect hazards in a file passed by argument. 
 *
 *  You can test with arg: "tests/data/object_classes_picture_4.png"
 */
int main(int argc, char* argv[])
{
    if (argc == 2) {
        /*
         * First, the path and the name of the file is saved
         */
        std::cout << "hazard detect: " << argv[1] << std::endl;
        std::string file  = argv[1];

        /*
         * Construct the platform info setting the hostname/IP, port and authentication token
         * Then proceed to create a cloud controller.
         * We'll use this object to create cloud calls to the platform.
         */
        rapp::cloud::platform info = {"rapp.ee.auth.gr", "9001", "rapp_token"}; 
        rapp::cloud::service_controller ctrl(info);

        /*
         * The image is loaded from argv[1] to a picture class
         */
        auto pic = rapp::object::picture(file);

		/*
         * Construct a lambda, std::function or bind your own functor.
         * In this example we'll pass an inline lambda as the callback.
         * All it does is receive a double and we show the angle of the door
         * in the case that a hazard is found.         
         */
		auto callback = [&](double door_angle) {
            std::cout << "Door angle: " << door_angle  << std::endl;
        };

        /*
         * We make a call to hazard_detection class to detect hazards in the file
         * We need: \param a rapp::object::picture
         *          \param callback is the inline lamdba we have defined above.
         */
		ctrl.make_call<rapp::cloud::hazard_detection_door_check>(pic, callback);
	    return 0;
    }
    else {
        std::cerr << "no arguments given" << std::endl;
        return 1;
    }
}
