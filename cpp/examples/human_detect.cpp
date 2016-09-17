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
#include <rapp/cloud/vision_detection.hpp>
#include <rapp/objects/picture.hpp>
/*
 * \brief example to detect humans in a image 
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
     * The image is loaded from its path to a picture class.
     * If you run the example inside examples folder, this path is valid.
     * In other cases, you'll have to change it for a proper one.
     */
    auto pic = rapp::object::picture("data/object_classes_picture_3.png");

    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a vector of rapp::object::human and
     * we show the size of the vector to know how many humans have 
     * been found.
     */
    auto callback = [&](std::vector<rapp::object::human> humans) {
        std::cout << "Found " << humans.size() << " humans!" << std::endl;
    };

    /*
     * We make a call to human_detection class to detect humans in the file
     * For more information \see rapp::cloud::human_detection
     */
    ctrl.make_call<rapp::cloud::human_detection>(pic, callback);
    return 0;
}
