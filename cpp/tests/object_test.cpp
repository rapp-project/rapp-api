#define BOOST_TEST_MODULE ObjectTest
#include <boost/test/unit_test.hpp>
#include "../includes/objects/face/face.hpp"
#include "../includes/objects/qrCode/qrCode.hpp"
#include "../includes/objects/picture/picture.hpp"
#include "../includes/objects/audio/audio.hpp"

BOOST_AUTO_TEST_SUITE ( object_test )

BOOST_AUTO_TEST_CASE( constructors_test )
{
    BOOST_TEST_MESSAGE( "constructors test" );

    // Test all face constructors work
    // Empty face object
    auto f_ptr = std::make_shared<rapp::object::face>( );
    BOOST_CHECK( f_ptr != nullptr );

    // Contruct with coordinates
    rapp::object::face f_valid( 0.5f,0.3f,0.1f,0.6f,0.8f,0.9f);

    // Copy Constructor
    rapp::object::face f_copy( f_valid );
    BOOST_CHECK( f_copy == f_valid );

    // Assignment constructor
    rapp::object::face f_asmt = f_copy;
    BOOST_CHECK( f_asmt == f_copy );
    
    // Test all qrCode contructors work
    auto qr_ptr = std::make_shared<rapp::object::qrCode>();
    BOOST_CHECK( qr_ptr != nullptr );

    // Construct with coordinate and message
    rapp::object::qrCode qr_valid (0.1f, 0.1f, "alex");

    // Copy constructor
    rapp::object::qrCode qr_copy( qr_valid );
    BOOST_CHECK( qr_copy == qr_valid );

    // Asignment constructor
    rapp::object::qrCode qr_asmt = qr_copy;
    BOOST_CHECK( qr_copy == qr_asmt );

    // Test all picture contructors work
    // NOTE: Use lena.jpg as the file

    // Construct from a file-path
    rapp::object::picture lena ( "Lenna.png" );

    // Open a byte steam from file, and construct the picture
    std::ifstream bytestream( "Lenna.png", std::ios::in | std::ios::binary | std::ios::ate );
    rapp::object::picture b_copy( bytestream );
    BOOST_CHECK( lena == b_copy );

    // Copy constructor
    rapp::object::picture r_copy = lena;
    BOOST_CHECK( lena == r_copy );

    // Assignment
    rapp::object::picture asmt = lena;
    BOOST_CHECK( lena == asmt );

    // audio tests
    rapp::object::audio t1 ( "terminator_1.wav" );
    std::ifstream bytes( "terminator_1.wav", std::ios::in | std::ios::binary | std::ios::ate );
    rapp::object::audio t1_ifstrm ( bytes );

    BOOST_CHECK( t1 == t1_ifstrm );

    rapp::object::audio t2 ( "terminator_2.wav" );
    rapp::object::audio t2_cpy = t2;

    //BOOST_CHECK_PREDICATE( std::not_equal_to<rapp::object::audio>(), (t1)(t2) );
    BOOST_CHECK( t2 == t2_cpy );

    rapp::object::OGGfile og1 ("recording_sentence1.ogg");
    rapp::object::OGGfile og2 ( og1 );
    rapp::object::WAVfileSingleChannel wv1 ("yes-no.wav");

    BOOST_CHECK( og1 == og2 );
    //BOOST_CHECK( og1 != wv1 );
}

BOOST_AUTO_TEST_SUITE_END( )
