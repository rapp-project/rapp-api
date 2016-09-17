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
#include <rapp/cloud/path_planning.hpp>
/*
 * \brief Example for upload a map and find a path for a robot
 * between two points in that map.
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
     * Example of path_upload_map
     *
     * The image of the map is loaded from its path to a picture class.
     * If you run the example inside examples folder, this path is valid.
     * In other cases, you'll have to change it for a proper one.
     */
    rapp::object::picture png_file("data/object_classes_map_1.png");

    /*
     * The yaml file is loaded from its path to a yaml class.
     * It cointains the description of the map
     * If you run the example inside examples folder, this path is valid.
     * In other cases, you'll have to change it for a proper one.
     */
    rapp::object::yaml yaml_file("data/object_classes_map_1.yaml");

    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a string with the error (in the case
     * that one occurs) 
     */
     auto callback_map = [&](std::string str) {
         if (str.empty()) {
            std::cout << "Map uploaded OK" << std::endl;
         }
         else {
             std::cout << str << std::endl;
         }
     };

    /*
     * We make a call to plan_upload_map. The map which we want to use we
     * have to put it a name. This map's name is going to be use in the next example to 
     * find a path.
     * For more information \see rapp::cloud::path_upload_map
     */
    ctrl.make_call<rapp::cloud::path_upload_map>(png_file, yaml_file, "Example_map", callback_map);

    /*
     * Example of plan_path_2d
     *
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a rapp::object::planned_path and 
     * shows if a plan has been found
     */
    auto callback = [&](rapp::object::planned_path path) {
        uint8_t path_info = path.get_plan();
        switch (path_info) {
            case 0 :
                std::cout << "Not path found" << std::endl;
                break;
            case 1:
                std::cout << "Path found!" << std::endl;
                break;
            default :
                std::cout << "Wrong map, robot or algorithm" << std::endl;
        }
    };
    
    /*
     * \param t is a time stamp to use with the pose_stamped object
     */
    std::chrono::nanoseconds t(0);

    /*
     * \param start is a pose_stamped object in which we are saying all the data 
     * about how is the robot at the beginning of the path
     * For more information \see rapp::object::pose_stamped 
     */
    rapp::object::pose_stamped start(rapp::object::msg_metadata(0, t, ""),
                                     rapp::object::pose(rapp::object::point(1, 1, 0),
                                                        rapp::object::quaternion(0, 0, 0, 1))); 

    /*
     * \param goal is a pose_stamped object in which we are saying all the data
     * about how we want the robot finished the path
     * For more information \see rapp::object::pose_stamped
     */
    rapp::object::pose_stamped goal(rapp::object::msg_metadata(0, t, ""),
                                    rapp::object::pose(rapp::object::point(2, 2, 0),
                                                       rapp::object::quaternion(0, 0, 0, 1))); 
    /*
     * We make a call to plan_path_2d to find a path in the map which we want, with a specific type
     * of robot, and with a specific algorithm of searching  between the two \param pose_stamped
     * For more information \see rapp::cloud::plan_path_2d
     */ 
    ctrl.make_call<rapp::cloud::plan_path_2d>("Example_map", "NAO", "dijkstra", start, goal, callback);
    return 0;
}
