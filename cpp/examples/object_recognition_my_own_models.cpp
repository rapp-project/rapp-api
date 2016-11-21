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
 * \brief Example to load, learn and find objects of a picture
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
    auto pic = rapp::object::picture("data/object_classes_picture_2.jpg");
    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive an int to indicate the state. 
    */
    auto callback = [](int result) {
        switch (result) {
            case 0:
                std::cout << "Correct" << std::endl;
                break;
            case -1:
                std::cout << "No models" << std::endl;
                break;
            case -2:
                std::cout << "No image to analyse" << std::endl;
                break;
            default:
                std::cout << "Error" <<std::endl;
                break;
        }
    };

    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive the data of the objects found. 
    */
    auto find_cb = [](std::vector<std::string> obj_names,
                     std::vector<rapp::object::point> points, 
                     std::vector<double> scores,
                     int result) 
    {
        std::cout << "Number of objects found: " << obj_names.size() << std::endl;
        std::cout << "Size vector points: " << points.size() << std::endl;
        std::cout << "Size of scores: " << scores.size() << std::endl;
        std::cout << "Result: " << result << std::endl; 
    };
    /*
     * We make a call to learn_object class to learn objects from the file
     * For more information \see rapp::cloud::object_detection_learn_object
     */
    ctrl.make_call<rapp::cloud::object_detection_learn_object>(pic, "cat", "rapp", callback);

    /*
     * Before finding objects, we load them beforehand.
     * In this vector we say the names of the objects to load
     */
    std::vector<std::string> names = {"cat"};

    /*
     * We make a call to load_models class to load objects from the file
     * For more information \see rapp::cloud::object_detection_load_models
     */
    ctrl.make_call<rapp::cloud::object_detection_load_models>("rapp", names, callback);

    /*
     * We make a call to find_objects in the picture sent
     * For more information \see rapp::cloud::object_detection_find_objects
     */
    ctrl.make_call<rapp::cloud::object_detection_find_objects>(pic, "rapp", 1, find_cb);

    /*
     * We make a call to clear_model class to clear the memory
     * For more information \see rapp::cloud::clear_model
     */
    ctrl.make_call<rapp::cloud::object_detection_clear_models>("rapp", callback);
    return 0;
}
