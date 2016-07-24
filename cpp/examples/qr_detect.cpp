#include "cloud/service_controller/service_controller.hpp"
#include "cloud/vision/qr_detection/qr_detection.hpp"
#include "objects/picture/picture.hpp"
///
/// Pass as argv[1] an image with a QR code
///
int main(int argc, char* argv[])
{
    if (argc > 1) {
        std::cout << "scan for QR: " << argv[1] << std::endl;
        std::string file = argv[1];

        // Service Controller 
        rapp::cloud::platform_info info = {"localhost", "9001", "mytoken"}; 
        rapp::cloud::service_controller ctrl(info);

        // test pic was loaded
        auto pic = rapp::object::picture(file);

		// callback lambda: print the QR code label(s)
		auto callback = [&](std::vector<rapp::object::qr_code> codes)
						{
							std::cout << "found " << codes.size() << " QR codes" << std::endl;
							for (const auto code : codes) {
								std::cout << code.label() << std::endl;
							}
						};

		// detect QR code(s)
		ctrl.make_call<rapp::cloud::qr_detection>(pic, callback);
		return 0;
    }
} 
