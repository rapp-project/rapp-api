#include <rapp/cloud/service_controller.hpp>
#include <rapp/cloud/vision_detection.hpp>
#include <rapp/cloud/weather_report.hpp>
#include <rapp/cloud/ontology.hpp>
#include <rapp/objects/picture.hpp>
#include <iostream>
#include <functional>

using namespace rapp::cloud;

class reactor
{
public:
    /*
     * \brief constructor passing the information of the platform
     */
    reactor(rapp::cloud::platform info)
    : ctrl_(info)
    {}

    /*
     * \brief method to see how many faces have been found
     */
    void handle_face(std::vector<rapp::object::face> faces)
    {        
        std::cout << "Found " << faces.size() << " faces!" << std::endl;
    }

    /*
     * \brief method to see the result of ontology subclasses
     */
    void handle_ontology_sub(std::vector<std::string> classes)
    {        
        std::cout << "Sub classes: " << std::endl;
        for (const auto & str : classes) {
            std::cout << str << std::endl;
        }    
    }

    /*
     * \brief method to see the parameters of the weather
     */
    void handle_weather(std::vector<std::string> weather) 
    {
        std::cout << "Temperature: " << weather.at(1) << std::endl;
        std::cout << "Humidity: " << weather.at(3) << std::endl;
        std::cout << "Wind speed: " << weather.at(6) << std::endl;
    }

    /*
     * \brief method to make a call at the same time of 
     * face_detection, weather_report_current and ontology_subclasses_of
     * \param pic is the picture where we are going to look for a face
     * \param object is the object we want to know its ontology subclasses
     * \param city is the name of the city where we want to know the weather
     */
    void run(rapp::object::picture pic, std::string object, std::string city)
    {
        ctrl_.make_calls(face_detection(pic, false, std::bind(&reactor::handle_face, this, std::placeholders::_1)),
                         weather_report_current(city, "", 0, std::bind(&reactor::handle_weather, this, std::placeholders::_1)),
                         ontology_subclasses_of(object, true, std::bind(&reactor::handle_ontology_sub, this, std::placeholders::_1)));
    }
    
private:
    rapp::cloud::service_controller ctrl_;
};

/*
 * \brief example to show how the new class works
 */
int main()
{
    /*
     * We initialize an reactor object.
     * We have to pass it like a pointer because its member
     * service_controller can't be copied
     */
    rapp::cloud::platform info = {"rapp.ee.auth.gr", "9001", "rapp_token"}; 
    auto my_reactor = std::make_unique<reactor>(info);

    /* 
     * We load an image. You have to run thi example in the examples folder.
     * In other cases, use the proper path.
     */
    auto pict = rapp::object::picture("data/object_classes_picture_1.png");

    /*
     * The method run is done to make the multiple calls,
     * passing the corresponding parameters.
     */
    my_reactor->run(pict, "Toy", "Madrid");

    return 0;
}
