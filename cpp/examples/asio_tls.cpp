#include "../includes/cloud/service_controller/service_controller.hpp"
#include "../includes/cloud/asio_socket_https/asio_socket_https.hpp"
///
/// TODO: test under linux only
///
int main(int argc, char* argv[])
{
    // service controler
    rapp::cloud::service_controller ctrl;
    // run an asio https
    auto test = std::make_shared<rapp::cloud::asio_socket_https>("my_token");
    if (test) {
        ctrl.run_job(test);
    }
    return 0;
}
