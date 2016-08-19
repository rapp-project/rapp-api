#include "cloud/service_controller/service_controller.hpp"
#include "cloud/navigation/path_planning/path_planning.hpp"
#include "objects/pose_stamped/pose_stamped.hpp"
#include "objects/planned_path/planned_path.hpp"
#include "objects/yaml/yaml.hpp"
#include "objects/picture/picture.hpp"
#include <chrono>
#include <stdlib.h>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

rapp::object::pose vec2pose(const std::vector<float> & p, const std::vector<float> & o) {
    return rapp::object::pose(
        rapp::object::point(p[0], p[1], p[2]),
        rapp::object::quaternion(o[0], o[1], o[2], o[3])
    );
}

template<typename T>
inline std::ostream& operator << (std::ostream& os, const std::vector<T>& v) {
    os << "[";
    std::string delim = "";
    for (const auto & elem : v) {
        os << delim << elem;
        delim = ", ";
    }
    os << "]";
    return os;
}

///
/// Pass as param start and goal poses and path to png and yaml file and map name
///
int main(int argc, char* argv[])
{
    po::options_description desc("");

    std::vector<float> start_p;
    std::vector<float> start_or;
    std::vector<float> goal_p;
    std::vector<float> goal_or;

    std::string addr;
    std::string port;
    std::string token;

    std::string map_name;
    std::string map_path;

    desc.add_options()
        ("start,s", po::value<std::vector<float> >(&start_p)->multitoken()->default_value({1, 1, 0}, "1 1 0"), "starting position")
        ("start_or", po::value<std::vector<float> >(&start_or)->multitoken()->default_value({0, 0, 0, 1}, "0 0 0 1"), "start orientation")
        ("goal,g", po::value<std::vector<float> >(&goal_p)->multitoken()->default_value({2, 2, 0}, "2 2 0"), "goal position")
        ("goal_or", po::value<std::vector<float> >(&goal_or)->multitoken()->default_value({0, 0, 0, 1}, "0 0 0 1"), "goal orientation")
        ("addr,a", po::value<std::string>(&addr)->default_value("localhost"), "platform address or hostname")
        ("port,p", po::value<std::string>(&port)->default_value("9001"), "platform port")
        ("token,t", po::value<std::string>(&token)->default_value("rapp_token"), "platform token")
        ("map,m", po::value<std::string>(&map_name), "map name")
        ("path", po::value<std::string>(&map_path)->default_value("."), "path to look for maps in")
        ("help,h", "show this help")
    ;

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm); 

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return 1;
        }
    } catch (po::error & e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    std::cout << "start: " << start_p << " " << start_or << "\n";
    std::cout << "goal: " << goal_p << " " << goal_or << "\n";

    if (vm.count("map") < 1) {
        std::cout << "No map specified.\n";
        return 1;
    }

    if (start_p.size() != 3) {
        std::cout << "start point should have exactly three elements\n";
        return 1;
    }
    if (goal_p.size() != 3) {
        std::cout << "goal point should have exactly three elements\n";
        return 1;
    }
    if (start_or.size() != 4) {
        std::cout << "start orientation should have exactly four elements\n";
        return 1;
    }
    if (goal_or.size() != 4) {
        std::cout << "goal orientation should have exactly three elements\n";
        return 1;
    }

    // service controler
    rapp::cloud::platform_info info = {addr, port, token}; 
    rapp::cloud::service_controller ctrl(info);

    // callback lambda UPLOAD MAP
    auto upload_callback = [&](std::string status)
    {std::cout << "upload status: \n" << status << " \n" << std::endl;};
    // upload map
    std::string yaml_file_name  = map_path + "/" + map_name + ".yaml";
    std::string png_file_name  = map_path + "/" + map_name + ".png";
    std::cout<<"yaml: " << yaml_file_name<<std::endl;
    std::cout<<"png: " << png_file_name<<std::endl;
    std::cout<<"map_name: "<<map_name<<std::endl;
    auto yaml_file = rapp::object::yaml(yaml_file_name);
    auto picture_file = rapp::object::picture(png_file_name);

    ///
    ctrl.make_call<rapp::cloud::path_upload_map>(picture_file, yaml_file, map_name, upload_callback);

    //set start and goal 
    std::chrono::nanoseconds nanosec(10);

    // start pose
    auto start = rapp::object::pose_stamped(
        rapp::object::msg_metadata(0,rapp::object::time(nanosec),"frame_x"),
        vec2pose(start_p, start_or)
    );

    // goal pose
    auto goal = rapp::object::pose_stamped(
        rapp::object::msg_metadata(1,rapp::object::time(nanosec),"frame_x"),
        vec2pose(goal_p, goal_or)
    );

    // callback lambda PLAN_PATH_2D
    auto callback = [&](rapp::object::planned_path path)
    {
        if (path.plan_found) {
            for(const auto & p : path.path) {
                std::cout << "[" << p.pose.position.x << ", " << p.pose.position.y << "]" << std::endl;
            }
        } else {
            std::cout << "Path not found\n";
        }
    };

    ctrl.make_call<rapp::cloud::plan_path_2d>(map_name, "NAO", "dijkstra", start, goal, callback);
    return 0;
}
