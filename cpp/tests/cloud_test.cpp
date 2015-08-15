#define BOOST_TEST_MODULE CloudTest
#include <boost/test/unit_test.hpp>
#include "../includes/cloud/faceDetector/faceDetector.hpp"
#include "../includes/cloud/qrDetector/qrDetector.hpp"
#include "../includes/objects/picture/picture.hpp"

BOOST_AUTO_TEST_SUITE ( cloud_test )

BOOST_AUTO_TEST_CASE( constructors_test )
{
    // Create a Face Detector
    // use lena.jpg
    auto pic = std::make_shared<rapp::object::picture>( "lena.jpg" );
    BOOST_CHECK( pic != nullptr );

    // Empty callback
    auto f_cb = [&]( std::vector<rapp::object::face> ){ };
    // Construct
    auto fDetect = std::make_shared<rapp::cloud::faceDetector>( pic, "jpg", f_cb );
    BOOST_CHECK( fDetect != nullptr );
    
    // Create a Qr Detector
    // use qrcode.png
    auto qr = std::make_shared<rapp::object::picture>( "qrcode.png" );
    BOOST_CHECK( qr != nullptr );
    auto q_cb = [&]( std::vector< rapp::object::qrCode > codes ){};
    auto qrDetect = std::make_shared<rapp::cloud::qrDetector>( qr, "png", q_cb );


    // TODO, all other handlers need be tested here
}

BOOST_AUTO_TEST_SUITE_END( )
