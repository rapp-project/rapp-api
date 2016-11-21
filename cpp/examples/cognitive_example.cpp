#include "cloud/service_controller/service_controller.hpp"
#include "cloud/cognitive_exercises/cognitive_exercises.hpp"
#include <iostream>
///
/// query subclasses and superclass of of argv[1]
///
int main(int argc, char* argv[])
{
	// service controler
	rapp::cloud::platform_info info = {"rapp.ee.auth.gr", "9001", "rapp_token"}; 
	rapp::cloud::service_controller ctrl(info);

	// sub-class callback - print each sub-class
	auto sb_cb = [](std::string json)
				 { std::cout << json; };

	ctrl.make_call<rapp::cloud::cognitive_record_performance>("random_test", 0.9, sb_cb);

	return 0;
}
