#include "../includes/cloud/service_controller/service_controller.hpp"
#include "../includes/cloud/face_detection/face_detection.hpp"
#include "../includes/objects/picture/picture.hpp"
///
/// Pass as param a PNG image
/// TODO: Valigrind this example
///
int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        std::cout << "face detect: " << argv[1] << std::endl;
        std::string file  = argv[1];
		std::string token = argv[2];

        // service controler
        rapp::cloud::service_controller ctrl;

        // load the image from argv[1]
        if (auto pic = std::make_shared<rapp::object::picture>(file))
        {
            auto callback = [&](std::vector<rapp::object::face> faces)
                            {std::cout << "found " << faces.size() << " faces!" << std::endl;};
            auto fdetect = std::make_shared<rapp::cloud::face_detection>(pic, false, callback, token);
            if (fdetect)
                ctrl.run_job(fdetect);
        }
        else
            std::cerr << "Error loading image: " << argv[1] << std::endl;

        return 0;
    }
}
