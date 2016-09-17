#ifndef RAPP_CLOUD_PATH_PLANNING
#define RAPP_CLOUD_PATH_PLANNING
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
#include <rapp/objects/planned_path.hpp>
#include <rapp/objects/pose_stamped.hpp>
#include <rapp/objects/picture.hpp>
#include <rapp/objects/yaml.hpp>

namespace rapp {
namespace cloud {
/**
 * \class plan_path_2d
 * \brief plan a 2D path
 * \version 0.7.0
 * \date September 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class plan_path_2d : public http_request
{
public:
	/**
	 * \param map_name used to load the map
	 * \param robot_type defines the robot being used, e.g., "NAO"
     * \param algorithm, e.g. "dijkstra"
	 * \callback will receive the planned path
	 */
	plan_path_2d(
                  const std::string map_name,
                  const std::string robot_type,
                  const std::string algorithm,
                  const rapp::object::pose_stamped start,
                  const rapp::object::pose_stamped goal,
                  std::function<void(rapp::object::planned_path)> callback
                );
        
    /**
     * \brief handle platform's JSON reply
     */
    void deserialise(std::string json) const;

private:
    // 
    std::function<void(rapp::object::planned_path path)> delegate_;
};

/**
 * \class plan_upload_map
 * \brief upload a map
 * \version 0.7.0
 * \date September 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class path_upload_map : public http_request
{
public:
    /**
     * \brief upload a map 
     * \param png_file is an image (PNG format) of the map
     * \param yaml_file is a map description yaml file
     * \param map_name is the name of the map
     * \note callback only receives an error if one occurs
     */
     path_upload_map(
                      const rapp::object::picture & png_file,
					  const rapp::object::yaml & yaml_file,
                      const std::string map_name,
                      std::function<void(std::string)> callback
                    );
    
    /**
     * \brief handle platform's JSON reply
     */
     void deserialise(std::string json) const;
        
private:
     /// delegate
     std::function<void(std::string)> delegate_;
};
}
}
#endif
