#include "cloud/service_controller/service_controller.hpp"
#include "cloud/vision/face_detection/face_detection.hpp"
#include "objects/picture/picture.hpp"
///
int main(int argc, char* argv[])
{
    if (argc == 2) {
        std::cout << "face detect: " << argv[1] << std::endl;
        std::string file  = argv[1];

        // service controler
        rapp::cloud::service_controller ctrl;
        auto callback = [&](std::vector<rapp::object::face> faces)
                        {std::cout << "found " << faces.size() << " faces!" << std::endl;};

        // load the image from argv[1]
        if (auto pic = std::make_shared<rapp::object::picture>(file)) {
            ctrl.make_call<rapp::cloud::face_detection>(pic, false, callback);
        }
        else {
            std::cerr << "Error loading image: " << argv[1] << std::endl;
        }
        return 0;
    }
    else {
        std::cerr << "you must pass an arguments: a picture file\r\n";
    }
}
