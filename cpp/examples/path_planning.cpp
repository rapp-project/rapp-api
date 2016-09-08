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
#include "cloud/navigation/path_planning/path_planning.hpp"
//
//\brief example  
//
int main()
{
    //Construct the platform info setting the hostname/IP, port and authentication token
    //Then proceed to create a cloud controller.
    //We'll use this object to create cloud calls to the platform.
    rapp::cloud::platform info = {"rapp.ee.auth.gr", "9001", "rapp_token"}; 
    rapp::cloud::service_controller ctrl(info);

    // Example of path_upload_map

    // We load a png image of the map
    rapp::object::picture png_file("data/object_classes_map_1.png");

    // We load an yaml file with the description of the map
    rapp::object::yaml yaml_file("data/object_classes_map_1.yaml");

    // Construct a lambda, std::function or bind your own functor.
    // In this example we'll pass an inline lambda as the callback.
    // All it does is receive a string with the error (in the case
    // that one occurs) 
     auto callback_map = [&](std::string str) {
         if (str.empty()) {
            std::cout << "map uploaded OK" << std::endl;
         }
         else {
             std::cout << str << std::endl;
         }
     };

    // We make a call to plan_upload_map.
    // 
    // We need: #png_file: The map image png file.
    //          #yaml_file: The map description yaml file.
    //          #map_name: The map name.
    //          #callback
    ctrl.make_call<rapp::cloud::path_upload_map>(png_file, yaml_file, "Example_map", callback_map);


    // Example of plan_path_2d
    
    // Construct a lambda, std::function or bind your own functor.
    // In this example we'll pass an inline lambda as the callback.
    // All it does is receive a rapp::object::planned_path and 
    // shows if a plan has been found
    auto callback = [&](rapp::object::planned_path path) {
         std::cout << path.get_plan() << std::endl;
         std::cout << path.to_json() << std::endl;
    };

    // Time stamp to use with the pose_stamped object
    std::chrono::nanoseconds t(0);

    // Pose_stamped start param
    //
    // This object is composed by msg_metadata and pose
    // msg_metadata needs: #seq(int): defines data sequence
    //                     #stamp(std::chrono) is message data generation time stamp
    //                     #frameid(string) is data coordination frame
    // pose needs: #rapp::object::point is the position (x, y, z)
    //             #rapp::object::quaternion is the orientation (x, y, z, w)
    rapp::object::pose_stamped start(rapp::object::msg_metadata(0, t, ""),
                                     rapp::object::pose(rapp::object::point(1, 1, 0),
                                                        rapp::object::quaternion(0, 0, 0, 1))); 

    // Pose_stamped goal param
    rapp::object::pose_stamped goal(rapp::object::msg_metadata(0, t, ""),
                                    rapp::object::pose(rapp::object::point(2, 2, 0),
                                                       rapp::object::quaternion(0, 0, 0, 1))); 

    // We make a call to plan_path_2d.
    // 
    // We need: #map_name (String): The map name to use.
    //          #robot_type (String): The robot type. 
    //          #algorithm {String}: The path planning algorithm to apply.
    //          #start: Start pose of the robot. (rapp::object::pose_stamped)
    //          #goal: Goal pose of the robot. (rapp::object::pose_stamped)
    //          #callback
    ctrl.make_call<rapp::cloud::plan_path_2d>("Example_map", "NAO", "dijkstra", start, goal, callback);

    return 0;
}
