#include <rapp/cloud/service_controller.hpp>
#include <rapp/objects/picture.hpp>
#include <rapp/cloud/vision_detection.hpp>
#include <iostream>

int main()
{
    rapp::cloud::platform info = {"rapp.ee.auth.gr", "9001", "rapp_token"}; 
    rapp::cloud::service_controller ctrl(info);

    auto pic = rapp::object::picture("data/object_classes_picture_7.jpg");

    auto face_cb = [&](std::vector<rapp::object::face> faces) { 
        std::cout << "Found " << faces.size() << " faces!" << std::endl;
    };

    auto human_cb = [&](std::vector<rapp::object::human> humans) {
        std::cout << "Found " << humans.size() << " humans!" << std::endl;
    };

    auto hazard_cb = [&](double door_angle) {
        std::cout << "Door angle: " << door_angle  << std::endl;
    };

    ctrl.make_calls(rapp::cloud::face_detection(pic, false, face_cb),
                    rapp::cloud::human_detection(pic, human_cb),
                    rapp::cloud::door_angle_detection(pic, hazard_cb));

    return 0;
}
