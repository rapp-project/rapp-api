#ifndef RAPP_OBJECT_POINT
#define RAPP_OBJECT_POINT
#include "includes.ihh"
namespace rapp {
namespace object {

using namespace rapidjson;    
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
    point( const rapidJSON::Value::CostMemberIterator & iter)
    {
        auto it_x = iter->FindMember("x");
        if (it_x != iter->MemberEnd()) {
            if (it_x->value.IsFloat()){
                this->x = it_x->value.GetFloat();
            }
            else
                throw std::runtime_error("member `x` not a float");    
        }
        else 
            throw std::runtime_error("param has no `x` value");
        
        auto it_y = iter->FindMember("y");
        if (it_y != iter->MemberEnd()) {
            if (it_y->value.IsFloat()){
                this->y = it_y->value.GetFloat();
            }
            else
                throw std::runtime_error("member `y` not a float");    
        }
        else 
            throw std::runtime_error("param has no `y` value");
        
        auto it_z = iter->FindMember("z");
        if (it_z != iter->MemberEnd()) {
            if (it_z->value.IsFloat()){
                this->z = it_z->value.GetFloat();
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
        writer.String("x");
        writer.Float(x);
        writer.String("y");
        writer.Float(y);
        writer.String("z");
        writer.Float(z);
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
