#include "../includes/cloud/service_controller/service_controller.hpp"
#include "../includes/cloud/qr_detection/qr_detection.hpp"
#include "../includes/objects/picture/picture.hpp"
///
/// Pass as argv[1] an image with a QR code
///
int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        std::cout << "scan for QR: " << argv[1] << std::endl;
        std::string file = argv[1];
		std::string token = "my_token";

        rapp::cloud::service_controller ctrl;

        if(auto pic = std::make_shared<rapp::object::picture>(file))
        {
            auto callback = [&](std::vector<rapp::object::qr_code> codes)
                            {
                                std::cout << "found " << codes.size() 
										  << " QR codes" << std::endl;
                                for (const auto code : codes)
                                    std::cout << code.label() << std::endl;
                            };
            auto fdetect = std::make_shared<rapp::cloud::qr_detection>(pic, token, callback);
            ctrl.run_job(fdetect);
            return 0;
        }
        else
            throw std::runtime_error("can't load: "+file);
    }
} 
