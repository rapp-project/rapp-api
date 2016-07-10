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
 *
 * WARNING: serious logic flaw: pose_stamp assumes a timestamp (header) which is uknown for goal
 * BUG:     JSON does not have keys for "start" and "end"
 *
 */
class plan_path_2d : public asio_service_http
{
public:
    
	/**
	 * \param map_name ?
	 * \param robot_type ?
     * \param algorithm ?
	 * \callback will receive the ?
	 */
	plan_path_2d(
                  const std::string map_name,
                  const std::string robot_type,
                  const std::string algorithm,
                  const rapp::object::pose_stamped start,
                  const rapp::object::pose_stamped goal,
                  std::function<void(rapp::object::planned_path)> callback,
                  const std::string token
                )
	: asio_service_http(token), delegate_(callback)
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
	 * TODO: { plan_found: 0, path: [], error: '' } what is path ? (obviously its planned_path but whats the JSON?
     */
    void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        try {
			// TODO: I require keys for 'start' and 'end'
		}
        catch (boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "plan_path_2d::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        // create wav file and move it to the delegate
        auto wav = std::unique_ptr<rapp::object::microphone_wav>(
                                            new rapp::object::microphone_wav(bytearray));
    }
    /// 
    std::function<void(rapp::object::planned_path path)> delegate_;
};

// TODO: path_upload_map
class path_upload_map : public asio_service_http
{
public:

private:

};
}
}
#endif
