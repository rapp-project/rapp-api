#ifndef RAPP_CLOUD_PATH_PLANNING
#define RAPP_CLOUD_PATH_PLANNING
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class plan_path_2d
 * \brief plan a 2D path
 * \version 0.7.0
 * \date 15 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class plan_path_2d :  public caller, public http_request
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
                )
	: http_header("POST /hop/path_planning_plan_path_2d HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()), 
      delegate_(callback)
	{
        boost::property_tree::ptree tree;
        tree.put("map_name", map_name);
        tree.put("robot_type", robot_type);
		tree.put("algorithm", algorithm);

        tree.add_child("", start.treefy());
        tree.add_child("", end.treefy());

        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

        std::string json = ss.str();
        http_post::add_content("json", json, false); 
        http_post::end();
     
    }

    /**
     * \brief handle platform's JSON reply
     */
    void deserialise(std::string json) const
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
				for (auto iter = child.second.begin(); iter!= child.second.end(); ++iter) {
                    // header + time stamp
					std::unique_ptr<pose_metadata> meta;
                    if (iter->first == "header") {
						meta = std::unique_ptr<pose_metadata>(new meta(iter));
					}
                    // pose + position + quaternion from JSON
					std::unique_ptr<pose> pose;
                    else if (iter->first == "pose") {
						pose = std::unique_ptr<pose>(new pose(iter));   
					}
                    rapp::object::pose_stamped ps(*meta, *pose);
                    path.push_back(std:move(ps));
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

    /**
    * \brief method to fill the buffer with http_post and http_header information
    * \param info is the data of the platform    
    */
    boost::asio::streambuf fill_buffer(rapp::cloud::platform info)
    {
           return std::move(http_request::fill_buffer(info));
    }

private:
    // 
    std::function<void(rapp::object::planned_path path)> delegate_;
};

// 
class path_upload_map :  public caller, public http_request
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
                    )
    : http_header("POST /hop/path_upload_map HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()), delegate_(callback)
    {
        http_post::add_content("map_name", map_name, true);
        auto imagebytes = png_file.bytearray();
        http_post::add_content("png_file", png_fname, imagebytes);

        //ymal file
        std::string png_fname = rapp::misc::random_boundary() + ".png";
        //passing string into bytes
        std::string yaml_data = yaml_file.get_string();
        vector<rapp::types::byte> yaml_bytes(yaml_data.begin(), yaml_data.end());
        http_post::add_content("yaml_file", yaml_fname, yaml_bytes);
        http_post::end();

    }

    /**
     * \brief handle platform's JSON reply
     */
     void deserialise(std::string json) const
     {
		std::stringstream ss(json);
		std::string error;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

			for (auto child : tree.get_child("error")) {
                error = child.second.get_value<std::string>();
            }
	    }
        catch (boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "available_services::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate_(error);
     }
    
     /**
     * \brief method to fill the buffer with http_post and http_header information
     * \param info is the data of the platform    
     */
     boost::asio::streambuf fill_buffer(rapp::cloud::platform info)
     {
            return std::move(http_request::fill_buffer(info));
     }


private:
     /// delegate
     std::function<void(std::string>)> delegate_;
};
}
}
#endif
