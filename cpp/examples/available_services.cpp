#include "cloud/service_controller/service_controller.hpp"
#include "cloud/available_services/available_services.hpp"
#include <iostream>


int main(int argc, char* argv[])
{
    /**
     * Construct the platform info setting the hostname/IP, port and authentication token
     * Then proceed to create a cloud controller.
     * We'll use this object to create cloud calls to the platform.
     */
	rapp::cloud::platform info = {"rapp.ee.auth.gr", "9001", "rapp_token"}; 
	rapp::cloud::service_controller ctrl(info);

    /**
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a list of services and print them on stdout.
     */
	auto cb = [](std::vector<std::pair<std::string, std::string>> services) {
         std::cout << "available services: " << std::endl;
         for (const auto & pair : services) {
            std::cout << pair.first << " " << pair.second << std::endl;
         }
     };

	/**
     * Finally we make the call.
     * The simplest way to use the `make_call` template function, specifying
     * as template type the actual cloud call, in this case the `available_services` class.
     * This method will **block** until its complete.
     */
	//ctrl.make_call<rapp::cloud::available_services>(cb);

    ctrl.make_calls(rapp::cloud::available_services(cb),
                    rapp::cloud::available_services(cb));
	return 0;
}
