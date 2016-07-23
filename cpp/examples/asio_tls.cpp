#include "cloud/service_controller/service_controller.hpp"
#include "cloud/asio_socket_https/asio_socket_https.hpp"
///
/// TODO: test under linux only
///
int main(int argc, char* argv[])
{
    // service controler
	rapp::cloud::platform_info info = {"localhost", "9001", "mytoken"}; 
	rapp::cloud::service_controller ctrl(info);

    // run an asio https
    auto test = std::make_shared<rapp::cloud::asio_socket_https>();
    if (test) {
        ctrl.run_job(test);
    }
    return 0;
}
