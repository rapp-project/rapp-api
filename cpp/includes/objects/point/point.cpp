#include "point.hpp"
namespace rapp {
namespace object {

point::point(double x, double y, double z)
: x(x), y(y), z(z)
{}
    
point::point(const json::const_iterator & position)
{
    if (position->find("x") == position->end()) {
        throw std::runtime_error("no param x in position");
    }
    else {
        x = position->find("x")->get<double>();
    }
    if (position->find("y") == position->end()) {
        throw std::runtime_error("no param y in position");
    }
    else {
        y = position->find("y")->get<double>();
    }
    if (position->find("z") == position->end()) {
        throw std::runtime_error("no param z in position");
    }
    else {
        z = position->find("z")->get<double>();
    }
}

json::object_t point::to_json() const
{
    json::object_t values = {{"x", x}, {"y", y}, {"z", z}};
    json::object_t obj    = {{"position" , values}};
    return obj;
}

bool point::operator==(const rapp::object::point & rhs) const
{
    return (this->x == rhs.x) &&
           (this->y == rhs.y) &&
           (this->z == rhs.z);
}


}
}
