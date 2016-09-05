#include "cloud/service_controller/service_controller.hpp"
#include "cloud/vision/detection.hpp"
#include "objects/picture/picture.hpp"
///
/// Pass as param a PNG image
///
int main(int argc, char* argv[])
{
    if (argc == 2) {
        std::cout << "face detect: " << argv[1] << std::endl;
        std::string file  = argv[1];

		using namespace rapp::cloud;

        // service controler
        platform info = {"rapp.ee.auth.gr", "9001", "rapp_token"}; 
		service_controller ctrl(info);

        // load the image from argv[1]
        auto pic = rapp::object::picture(file);

		// callback lambda
		auto callback = [&](std::vector<rapp::object::face> faces)
						{std::cout << "found " << faces.size() << " faces!" << std::endl;};

		// detect faces
		ctrl.make_call<face_detection>(pic, false, callback);
	    return 0;
    }
}
