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
class plan_path_2d : public asio_http
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
    : asio_http(), delegate_(callback)
    {
        std::string boundary = rapp::misc::random_boundary();
        boost::property_tree::ptree tree;
        tree.put("map_name", map_name, s());
        tree.put("robot_type", robot_type, s());
        tree.put("algorithm", algorithm, s());
        tree.add_child("start", start.treefy());
        tree.add_child("goal", goal.treefy());

        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        post_  = "--" + boundary + "\r\n"
            + "Content-Disposition: form-data; name=\"json\"\r\n\r\n"
            + ss.str();
        post_ += "\r\n--" + boundary + "--";

        head_preamble_.uri = "POST /hop/path_planning_plan_path_2d HTTP/1.1\r\n";
        head_preamble_.content_type = "Content-Type: multipart/form-data; boundary=" + boundary;

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
        int plan_found;

        // see `examples/planned.path.json` for example
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

            // get `plan_error`
            plan_error = tree.get<std::string>("error");

            // get `plan_found`
            plan_found = tree.get<int>("plan_found");

            // iterate array `path` objects
            for (auto child : tree.get_child("path")) {
                auto pt_header = child.second.get_child("header");
                rapp::object::msg_metadata meta(pt_header);
                rapp::object::pose pose(child.second.get_child("pose"));
            
                rapp::object::pose_stamped ps(meta, pose);
                path.push_back(std::move(ps));
            }
        }
        catch (boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "plan_path_2d::handle_reply Error parsing: " << je.filename() 
                << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate_(rapp::object::planned_path(boost::lexical_cast<uint8_t>(plan_found), 
                    plan_error, 
                    path));
    }
    /// 
    std::function<void(rapp::object::planned_path path)> delegate_;
};

// 
class path_upload_map : public asio_http
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
    : asio_http(), delegate_(callback)
    {
        std::string boundary = rapp::misc::random_boundary();
		// multipart/form-data append JSON first
		post_  = "--" + boundary + "\r\n"
	    + "Content-Disposition: form-data; name=\"map_name\"\r\n\r\n"
	    + map_name + "\r\n";

        // write the PNG file binary data
        std::string png = rapp::misc::random_boundary() + ".png";
        post_ += "--" + boundary + "\r\n"
            + "Content-Disposition: form-data; name=\"png_file\"; filename=\"" + png + "\"\r\n"
            + "Content-Type: image/" + png_file.type() + "\r\n"
            + "Content-Transfer-Encoding: binary\r\n\r\n";
        // Append binary data
        auto imagebytes = png_file.bytearray();
        post_.insert(post_.end(), imagebytes.begin(), imagebytes.end());

        // write the YAML file data
        std::string yaml = rapp::misc::random_boundary() + ".yaml";
        post_ += "\r\n--" + boundary + "\r\n"
            + "Content-Disposition: form-data; name=\"yaml_file\"; filename=\"" + yaml + "\"\r\n"
            + "Content-Transfer-Encoding: binary\r\n\r\n";
        post_.append(yaml_file.get_string());
        post_ += "\r\n--" + boundary + "--";

        // set the HTTP header URI pramble and the Content-Type
        head_preamble_.uri = "POST /hop/path_planning_upload_map HTTP/1.1\r\n";
        head_preamble_.content_type = "Content-Type: multipart/form-data; boundary=" + boundary;

        // bind the base class callback, to our handle_reply
        callback_ = std::bind(&path_upload_map::handle_reply, this, std::placeholders::_1);
    }
private:
    /**
     * \brief handle platform's JSON reply
     */
    void handle_reply(std::string json)
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

    /// delegate
    std::function<void(std::string)> delegate_;
};
}
}
#endif
