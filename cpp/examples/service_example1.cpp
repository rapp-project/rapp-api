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
		rapp::cloud::platform_info info = {"localhost", "9001", "mytoken"}; 
        rapp::cloud::service_controller ctrl(info);

		// a callback which prints the number of faces found
        auto callback = [&](std::vector<rapp::object::face> faces)
                        {std::cout << "found " << faces.size() << " faces!" << std::endl;};

        // load the image from argv[1]
        auto pic = rapp::object::picture(file);

		// make the cloud call
        ctrl.make_call<rapp::cloud::face_detection>(pic, false, callback);  

		// TODO: show other ways of using the service_controller (job, jobs, threads, etc)
        return 0;
    }
    else {
        std::cerr << "you must pass an arguments: a picture file\r\n";
    }
}
