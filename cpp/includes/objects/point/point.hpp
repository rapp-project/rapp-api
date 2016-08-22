#ifndef RAPP_OBJECT_POINT
#define RAPP_OBJECT_POINT
#include "includes.ihh"
namespace rapp {
namespace object {

/**
 * \struct point
 * \brief encapsulate point position vector
 * \version 0.7.0
 * \date 19 August 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
struct point
{
    /**
     * \brief Consruct using code coordinates (x,y,z)
     * \param x is x coordinate
     * \param y is y coordinate
     * \param z is z coordinate
     */
    point(float x, float y, float z)
    : x(x), y(y), z(z)
    {}
    
    /// \brief Allow Empty Consructor
    point() = default;
    
    /// \brief Copy Conatructor
    point(const rapp::object::point &) = default;

	/// \brief construct using rapidJSON
    point( const rapidjson::Value::ConstMemberIterator & iter)
    {
        auto it_x = iter->FindMember("x");
        if (it_x != iter->MemberEnd()) {
            if (it_x->value.IsDouble()){
                this->x = it_x->value.GetDouble();
            }
            else
                throw std::runtime_error("member `x` not a float");    
        }
        else 
            throw std::runtime_error("param has no `x` value");
        
        auto it_y = iter->FindMember("y");
        if (it_y != iter->MemberEnd()) {
            if (it_y->value.IsDouble()){
                this->y = it_y->value.GetDouble();
            }
            else
                throw std::runtime_error("member `y` not a float");    
        }
        else 
            throw std::runtime_error("param has no `y` value");
        
        auto it_z = iter->FindMember("z");
        if (it_z != iter->MemberEnd()) {
            if (it_z->value.IsDouble()){
                this->z = it_z->value.GetDouble();
            }
            else
                throw std::runtime_error("member `z` not a float");    
        }
        else 
            throw std::runtime_error("param has no `z` value");

    }
    
    /// \brief Equality operator
    bool operator==(const rapp::object::point & rhs) const
    {
		return (this->x == rhs.x) &&
			   (this->y == rhs.y) &&
			   (this->z == rhs.z);
    }

	/// \brief serialization with rapidJSON
    template <typename W>
    void Serialize(W & writer) const
    {
        writer.StartObject();
        writer.String("y");
        writer.Double(y);
        writer.String("x");
        writer.Double(x);
        writer.String("z");
        writer.Double(z);
        writer.EndObject();
    } 
    
    /// members
	float x = 0;
    float y = 0;
    float z = 0;
};
}
}
#endif
