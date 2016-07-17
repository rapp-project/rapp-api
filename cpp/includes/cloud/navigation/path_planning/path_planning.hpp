#ifndef RAPP_CLOUD_PATH_PLANNING
#define RAPP_CLOUD_PATH_PLANNING
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class plan_path_2d
 * \brief plan a 2D path
 * \version 0.6.0
 * \date May 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class plan_path_2d : public asio_service_http
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
                  std::function<void(rapp::object::planned_path)> callback,
                  rapp::cloud::platform_info info
                )
	: asio_service_http(info), delegate_(callback)
	{
        boost::property_tree::ptree tree;
        tree.put("map_name", map_name);
        tree.put("robot_type", robot_type);
		tree.put("algorithm", algorithm);
        tree.add_child("", start.treefy());
        tree.add_child("", end.treefy());
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        post_ = ss.str();
        header_ = "POST /hop/path_planning_plan_path_2d HTTP/1.1\r\n";
        callback_ = std::bind(&plan_path_2d::handle_reply, this, std::placeholders::_1);
	}
private:
    /**
     * \brief handle platform's JSON reply
     */
    void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        std::vector<rapp::object::pose_stamped> path;
        std::string plan_error;
        std::string plan_found;

        // see `examples/planned.path.json` for example
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

            // get `plan_error`
            for (auto child : tree.get_child("error")) {
                plan_error = child.second.get_value<std::string>();
            }

            // get `plan_found`
            for (auto child : tree.get_child("plan_found")) {
                plan_found = child.second.get_value<std::string>();
            }

            // iterate array `path` objects
            for (auto child : tree.get_child("path")) {

                // iterate each anonymous object's members
                for (auto iter = child.second.begin(); iter!= child.second.end(); ++iter) {

                    // header + time stamp
                    rapp::objects::header meta;
                    rapp::object::time t;
                    rapp::object::point position;
                    rapp::object::quaternion orientation;

                    // first member is `header` TODO: add methods for all objects: `load_from_json` and implement logic there.
                    if (iter->first == "header") {
                        //
                        for (auto it : iter->second) {
                            // sequence
                            if (it.first == "seq") {
                                meta.seq = it.second.get_value<int>();
							}
                            // frame id
                            else if (it.first == "frame_id") {
                               meta.frameid = it.second.get_value<std::string>();
							}
                            // stamp
                            else if (it.first == "stamp") {
                                for (auto it2 : it.second.begin(); it2 != it.second.end(); ++it2) {
                                    if (it2.first == "secs") {
                                        t.sec = it2.second.get_value<uint32_t>();
                                    }
                                    else if (it2.first == "nsecs") {
                                        t.nsec= it2.second.get_value<uint32_t>();
                                    }
                                }
                                meta.stamp = t;
                            }
                        }
                    }

                    // second member is `pose` TODO: add methods for all objects: `load_from_json` and implement logic there.
                    else if (iter->first == "pose") {
                        //
                        for (auto it : iter->second) {
                            // position
                            if (it.first == "position") {
                                // position object
                                for (auto it2 : it.second.begin(); it2 != it.second.end(); ++it2) {
                                    if (it2.first == "x") {
                                        position.x = it2.second.get_value<uint32_t>();
                                    }
                                    else if (it2.first == "y") {
                                        position.y = it2.second.get_value<uint32_t>();
                                    }
                                    else if (it2.first == "z") {
                                        position.z = it2.second.get_value<uint32_t>();
                                    }
                                }
                            }
                            
                            // quaternion
                            else if (it.first == "orientation") {
                                for (auto it2 : it.second.begin(); it2 != it.second.end(); ++it2) {
                                    if (it2.first == "x") {
                                        orientation.x = it2.second.get_value<uint32_t>();
                                    }
                                    else if (it2.first == "y") {
                                        orientation.y = it2.second.get_value<uint32_t>();
                                    }
                                    else if (it2.first == "z") {
                                        orientation.y = it2.second.get_value<uint32_t>();
                                    }
                                    else if (it2.first == "w") {
                                        orientation.y = it2.second.get_value<uint32_t>();
                                    }
                                }
                            }
                        }
                    }

                    rapp::object::pose pose(position, orientation);
                    rapp::object::pose_stamped ps(meta, pose);
                    path.push_back(ps); 
                }
            }
		}
        catch (boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "plan_path_2d::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }

        delegate_(std::move(rapp::object::planned_path(plan_found, plan_error, path)));
    }
    /// 
    std::function<void(rapp::object::planned_path path)> delegate_;
};

// 
class path_upload_map : public asio_service_http
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
                      const rapp::object::picture png_file,
                      const std::string yaml_file,
                      const std::string map_name,
                      std::function<void(std::string)> callback,
                      rapp::cloud::platform_info info
                    )
    : asio_service_http(info), delegate_(callback)
    {
        boost::property_tree::ptree tree;
        tree.put("", map_name);
        tree.put("yaml_file", yaml_file);
		tree.put("map_name", map_name);

        // TODO: is the yaml a file or a string?
        // TODO: is the png_file a file, or a filename?
    }
private:
    /**
     * \brief handle platform's JSON reply
     */
     void handle_reply(std::string json)
     {

     }
     ///
     std::function<void(std::string>)> delegate_;
};
}
}
#endif
