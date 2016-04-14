#define BOOST_TEST_MODULE ServiceTest
#include <boost/test/unit_test.hpp>
#include "../includes/cloud/service_controller/service_controller.hpp"

BOOST_AUTO_TEST_SUITE ( service_test )

BOOST_AUTO_TEST_CASE( constructors_test )
{
    // Test a service controller pointer 
    auto ctrl = std::make_shared<rapp::cloud::service_controller>("rapp.cloud", "9001");
    // Only way to test is by comparison to nullptr
    BOOST_CHECK(ctrl != nullptr);
}

BOOST_AUTO_TEST_SUITE_END( )
