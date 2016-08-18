#include "cloud/service_controller/service_controller.hpp"
#include "cloud/navigation/path_planning/path_planning.hpp"
#include "objects/pose_stamped/pose_stamped.hpp"
#include "objects/planned_path/planned_path.hpp"
#include "objects/yaml/yaml.hpp"
#include "objects/picture/picture.hpp"
#include <chrono>
#include <stdlib.h>
///
/// Pass as param start and goal poses and path to png and yaml file and map name
///
int main(int argc, char* argv[])
{
    if (argc == 18) 
	{
		// service controler
        rapp::cloud::platform_info info = {"localhost", "9001", "rapp_token"}; 
		rapp::cloud::service_controller ctrl(info);

		// callback lambda UPLOAD MAP
		auto upload_callback = [&](std::string status)
							{std::cout << "upload status: \n" << status << " \n" << std::endl;};
		// upload map
		std::string yaml_file_name  = argv[16];
		std::string png_file_name  = argv[15];
		std::string map_name  = argv[17];
		std::cout<<"yaml: "<<yaml_file_name<<std::endl;

		std::cout<<"png: "<<png_file_name<<std::endl;
		std::cout<<"map_name: "<<map_name<<std::endl;
		auto yaml_file = rapp::object::yaml(yaml_file_name);
		auto picture_file = rapp::object::picture(png_file_name);

		///
		ctrl.make_call<rapp::cloud::path_upload_map>(picture_file, yaml_file, map_name, upload_callback);

		//set start and goal 
		std::chrono::nanoseconds nanosec(10);
		
		// start pose
		auto start = rapp::object::pose_stamped(rapp::object::msg_metadata(0,rapp::object::time(nanosec),"frame_x"),rapp::object::pose(rapp::object::point((float) atof(argv[1]), (float) atof(argv[2]),  (float) atof(argv[3])), rapp::object::quaternion((float) atof(argv[4]), (float) atof(argv[5]),(float) atof(argv[6]),  (float) atof(argv[7]))) );

		auto goal = rapp::object::pose_stamped(rapp::object::msg_metadata(1, rapp::object::time(nanosec), "frame_x"), rapp::object::pose(rapp::object::point((float) atof(argv[8]), (float) atof(argv[9]),  (float) atof(argv[10])), rapp::object::quaternion((float) atof(argv[11]), (float) atof(argv[12]), (float) atof(argv[13]), (float) atof(argv[14]))) );

		// callback lambda PLAN_PATH_2D
		auto callback = [&](rapp::object::planned_path path)
							{std::cout << "is plan found? \n" << path.plan_found << " \n" << std::endl; std::cout << "Plan has " << path.path.size() << " points\n";};

		// detect faces
		
		ctrl.make_call<rapp::cloud::plan_path_2d>(map_name, "NAO", "dijkstra", start, goal, callback);
		return 0;
    }
}
