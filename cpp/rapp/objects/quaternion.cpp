#include "quaternion.hpp"
namespace rapp {
namespace object {

quaternion::quaternion(double x, double y, double z, double w)
: x(x), y(y), z(z), w(w)
{}

quaternion::quaternion(const json::const_iterator & orientation)
{
        if (orientation->find("x") == orientation->end()) {
            throw std::runtime_error("no x variable in orientation");
        }
        else {
            x = orientation->find("x")->get<double>();
        }
        if (orientation->find("y") == orientation->end()) {
            throw std::runtime_error("no y variable in orientation");
        }
        else {
            y = orientation->find("y")->get<double>();
        }
        if (orientation->find("z") == orientation->end()) {
            throw std::runtime_error("no z variable in orientation");
        }
        else {
           z = orientation->find("z")->get<double>();
        }
        if (orientation->find("w") == orientation->end()) {
            throw std::runtime_error("no w variable in orientation");
        }
        else {
           w = orientation->find("w")->get<double>();
        }
}

json::object_t quaternion::to_json() const
{
    json::object_t values = {{"x", x}, {"y", y}, {"z", z}, {"w", w}};
    return values;
}

bool quaternion::operator==(const rapp::object::quaternion & rhs) const
{
    return (this->x == rhs.x) &&
           (this->y == rhs.y) && 
           (this->z == rhs.z) &&
           (this->w == rhs.w);

}

double quaternion::get_x() const
{
    return x;
}

double quaternion::get_y() const
{
    return y;
}

double quaternion::get_z() const
{
    return z;
}

double quaternion::get_w() const
{
    return w;
}

}
}
