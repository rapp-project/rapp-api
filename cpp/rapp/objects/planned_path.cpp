#include "planned_path.hpp"

namespace rapp {
namespace object {

planned_path::planned_path( 
               uint8_t plan_found,
               std::string planning_error,
               std::vector<pose_stamped> path 
            )
: plan_found_(plan_found),
  planning_error_(planning_error), 
  path_(path)
{}

planned_path::planned_path(const json & arg)
{
    auto path_it = arg.find("path");
    if (path_it == arg.end()){
        throw std::runtime_error("no param path in json");
    }
    else {
         for (auto it = path_it->begin(); it != path_it->end(); it++){
            path_.push_back(rapp::object::pose_stamped(it));
         } 
    }

    auto planf_it = arg.find("plan_found");
    if (planf_it == arg.end()){
        throw std::runtime_error("no param plan_found in json");
    }
    else {
        plan_found_ = planf_it->get<uint8_t>();        
    }

    auto err_it = arg.find("error");
    if (err_it == arg.end()){
        throw std::runtime_error("no param error in json");
    }
    else {
        planning_error_ = err_it->get<std::string>();        
    }
}

json planned_path::to_json() const
{
    auto list = json::array();
    for (const auto & pose : path_) {
       list.push_back(pose.to_json()); 
    }
    json final_json = {{ "path", list}, { "plan_found", plan_found_}, {"error", planning_error_}};
    return final_json;
}

bool planned_path::operator==(const rapp::object::planned_path & rhs) const
{
    return (this->plan_found_ == rhs.get_plan()) &&
           (this->planning_error_ == rhs.get_error()) &&
           (this->path_ == rhs.get_path());
}

uint8_t planned_path::get_plan() const
{
    return plan_found_;
}

std::string planned_path::get_error() const
{
    return planning_error_;
}

std::vector<rapp::object::pose_stamped> planned_path::get_path() const
{
    return path_;
}

}
}
