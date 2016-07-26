#include "cloud/service_controller/service_controller.hpp"
#include "cloud/available_services/available_services.hpp"
#include <iostream>
///
int main(int argc, char* argv[])
{
	// Service Controller 
	rapp::cloud::platform_info info = {"155.207.19.229", "9001", "rapp_token"}; 
	rapp::cloud::service_controller ctrl(info);

	// receives a list of available services
	auto cb = [](std::vector<std::pair<std::string, std::string>> services)
				{
					 std::cout << "available services: " << std::endl;
					 for (const auto & pair : services) {
						std::cout << pair.first << " " << pair.second << std::endl;
					 }
				 };

	// make the call
	ctrl.make_call<rapp::cloud::available_services>(cb);
	return 0;
}
