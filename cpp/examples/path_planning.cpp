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
/**
 * \brief example  
 */
int main()
{
   /**
    * Construct the platform info setting the hostname/IP, port and authentication token
    * Then proceed to create a cloud controller.
    * We'll use this object to create cloud calls to the platform.
    */
    rapp::cloud::platform info = {"rapp.ee.auth.gr", "9001", "rapp_token"}; 
    rapp::cloud::service_controller ctrl(info);

    /**
     * Example of weather_report_current
     */
    
    /**
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a vector of string and we show all 
     * the parameters about weather
     */
     auto callback = [&](rapp::object::planned_path path) {
         std::cout << path.get_plan() << std::endl;
         //std::cout << path.get_path() << std::endl;
     };

     std::chrono::nanoseconds t(0);
    // Pose_stamped start param
     rapp::object::pose_stamped start(rapp::object::msg_metadata(0, 
                                                                 t, 
                                                                 ""),
                                      rapp::object::pose(rapp::object::point(10, 10, 20),
                                                         rapp::object::quaternion(0, 0, 0, 0))); 
    // Pose_stamped goal param
     rapp::object::pose_stamped goal(rapp::object::msg_metadata(0, t, ""),
                                     rapp::object::pose(rapp::object::point(30, 10, 20),
                                                        rapp::object::quaternion(0, 0, 0, 0))); 

    /**
     * We make a call to plan_path_2d.
     *
     * We need: # map_name (String): The map name to use.
     *          #robot_type (String): The robot type. 
     *          #algorithm {String}: The path planning algorithm to apply.
     *          #start: Start pose of the robot. (rapp::object::pose_stamped)
     *          #goal: Goal pose of the robot. (rapp::object::pose_stamped)
     */
    ctrl.make_call<rapp::cloud::plan_path_2d>("MAP_NAME", "NAO", "dijkstra", start, goal, callback);
   
    return 0;
}
