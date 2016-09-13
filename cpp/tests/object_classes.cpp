#define BOOST_TEST_MODULE ObjectTest
/**
 * Copyright 2015 RAPP
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * #http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fstream>
#include <chrono>
#include <iostream>
#include <boost/test/unit_test.hpp>

#include "../includes/objects/human/human.hpp"
#include "../includes/objects/face/face.hpp"
#include "../includes/objects/qr_code/qr_code.hpp"
#include "../includes/objects/picture/picture.hpp"
#include "../includes/objects/audio/audio.hpp"
#include "../includes/objects/time/time.hpp"
#include "../includes/objects/point/point.hpp"
#include "../includes/objects/quaternion/quaternion.hpp"
#include "../includes/objects/pose/pose.hpp"
#include "../includes/objects/msg_metadata/msg_metadata.hpp"
#include "../includes/objects/pose_stamped/pose_stamped.hpp"
#include "../includes/objects/planned_path/planned_path.hpp"

BOOST_AUTO_TEST_SUITE(object_classes_test)


/**
 * \brief TEST for time object
 *
 * We check the constructors creating identical objects and comparing 
 * between them.
 *
 * Methods seconds and nanoseconds are checked comparing the atributes
 * between the objects created before. They have to be the same.
 */
BOOST_AUTO_TEST_CASE(object_time_test)
{
    std::chrono::nanoseconds t(1464949299093018853);
    rapp::object::time obj_time1 = rapp::object::time(t);
    rapp::object::time obj_time2 = rapp::object::time(t);
    BOOST_CHECK(obj_time1 ==  obj_time2);

    BOOST_CHECK_EQUAL(obj_time1.seconds(), 1464949299);
    BOOST_CHECK_EQUAL(obj_time1.nanoseconds(), 93018853);

    // assignment constructor
    rapp::object::time obj_time3 = rapp::object::time(obj_time1);
    BOOST_CHECK(obj_time1 == obj_time3); 

    // copy constructor
    auto obj_time4 = obj_time3;
    BOOST_CHECK(obj_time3 == obj_time4);

    // test seconds
    uint32_t s_obj_time1 = obj_time1.seconds();
    uint32_t s_obj_time2 = obj_time2.seconds();
    BOOST_CHECK_EQUAL(s_obj_time1, s_obj_time2);

    // test nanoseconds
    uint64_t n_obj_time1 = obj_time1.nanoseconds();
    uint64_t n_obj_time2 = obj_time2.nanoseconds();
    BOOST_CHECK_EQUAL(n_obj_time1, n_obj_time2);

    // test comparison operator
    BOOST_CHECK(obj_time1 == obj_time2);
}

/**
 * \brief TEST for point object
 *
 * The constructors are checked creating identical
 * objects and comparing between them.
 */
BOOST_AUTO_TEST_CASE(object_point_test)
{
    double x = 0.9999999776482582;
    double y = 0.9999999776482582;
    double z = 0.0;
    auto point1 = rapp::object::point(x, y, z);
    auto point2 = rapp::object::point(x, y, z);
    BOOST_CHECK(point1 ==  point2);

    auto point3 = rapp::object::point(point1);
    BOOST_CHECK(point1 == point3);

    auto point4 = rapp::object::point(0, 0, 0);
    auto point0 = rapp::object::point();
    BOOST_CHECK(point4 == point0);
    
    auto point5 = point4;
    BOOST_CHECK(point4 == point5);

    //to check that the variable is the same
    BOOST_CHECK_EQUAL(point1.x, 0.9999999776482582);
    BOOST_CHECK_EQUAL(point1.y, 0.9999999776482582);

}

/**
 * \brief TEST for quaternion object 
 *
 * The constructor are checked creating identical objects
 * and comparing between them.
 * A extra checked was added to guarantee the atributes
 * have the same valor that constants created.
 */
BOOST_AUTO_TEST_CASE(object_quaternion_test)
{
    auto quat0 = rapp::object::quaternion();
    auto quat1 = rapp::object::quaternion(0, 0, 0, 1);
    BOOST_CHECK( quat0 == quat1);
    
    double x = 0.0;
    double y = 0.0;
    double z = 0.3062984133859556;
    double w = 0.9519355450644997;
    
    auto quat2 = rapp::object::quaternion(x, y, z, w);
    auto quat3 = rapp::object::quaternion(quat2);
    BOOST_CHECK(quat2 == quat3);

    BOOST_CHECK_EQUAL(quat3.z, 0.3062984133859556);
    BOOST_CHECK_EQUAL(quat3.w, 0.9519355450644997);

    auto quat4 = quat3;
    BOOST_CHECK(quat3 == quat4);
}

/**
 * \brief TEST for pose object
 *
 * The constructors are checked creating identical
 * objects and comparing between them.
 *
 * For methods, we take the parameters and 
 * they are compared with the objects created for
 * initialize that object.
 */
BOOST_AUTO_TEST_CASE(object_pose_test)
{
    auto quat =rapp::object::quaternion( 0, 
                                         0, 
                                         0.17576372515799546, 
                                         0.9844323810798712);

    auto point = rapp::object::point( 0.9999999776482582, 
                                      0.9999999776482582, 
                                      0);

    auto pose0 = rapp::object::pose();
    auto pose1 = rapp::object::pose(pose0);
    BOOST_CHECK(pose0 == pose1);

    auto pose2 = rapp::object::pose( point, quat); 
    auto pose3 = rapp::object::pose( point, quat);
    BOOST_CHECK(pose2 == pose3);

    const auto quat1 = pose3.get_orientation();
    BOOST_CHECK(quat1 == quat);
    BOOST_CHECK_EQUAL(quat1.w, 0.9844323810798712);
    BOOST_CHECK_EQUAL(quat1.z, 0.17576372515799546);

    const auto point1 = pose3.get_position();
    BOOST_CHECK(point == point1);
    BOOST_CHECK_EQUAL( point1.x, 0.9999999776482582);

    auto pose4 = pose3;
    BOOST_CHECK(pose3 == pose4);
}

/**
 * \brief TEST for msg_metadata object
 *
 * The constructors are checked creating identical
 * objects and comparing between them.
 *
 * For methods, we take the parameters and 
 * they are compared with the objects created for
 * initialize that object.
 */
BOOST_AUTO_TEST_CASE(object_msg_metadata_test)
{
    std::chrono::nanoseconds t(1464949299093018853);
    auto time0 = rapp::object::time(t);
    int seq0 = 0;
    std::string frameid0 = "map";

    auto msg0 = rapp::object::msg_metadata();
    auto msg1 = rapp::object::msg_metadata(msg0);
    BOOST_CHECK(msg0 == msg1);
    
    auto msg2 = rapp::object::msg_metadata();
    BOOST_CHECK(msg0 == msg2);

    auto msg3 = rapp::object::msg_metadata( seq0, time0, frameid0);
    auto msg4 = rapp::object::msg_metadata( seq0, time0, frameid0);
    BOOST_CHECK(msg3 == msg4);

    rapp::object::time time1 = msg4.get_time();
    BOOST_CHECK_EQUAL(time1.seconds(),1464949299);
    BOOST_CHECK_EQUAL(time1.nanoseconds(),93018853);

    BOOST_CHECK_EQUAL(msg4.get_seq(), 0);
    BOOST_CHECK_EQUAL(msg4.get_frame(), "map");

}

/**
 * \brief TEST for pose_stamped object
 *
 * In the same way that the classes before
 * the constructors are checked creating identical
 * objects and comparing between them.
 *
 * For methods, we take the parameters and 
 * they are compared with the objects created for
 * initialize that object.
 */
BOOST_AUTO_TEST_CASE(object_pose_stamped_test)
{
    std::chrono::nanoseconds t(1464949299093018853);
    auto time0 = rapp::object::time(t);
    int seq0 = 0;
    std::string frameid0 = "map";
    auto header0 = rapp::object::msg_metadata(seq0 , time0, frameid0);
   
    auto quat =rapp::object::quaternion(0, 
                                        0, 
                                        0.17576372515799546, 
                                        0.9844323810798712);

    auto point = rapp::object::point(0.9999999776482582, 
                                     0.9999999776482582, 
                                     0);

    auto pose0 = rapp::object::pose( point, quat);

    auto ps_obj0 = rapp::object::pose_stamped();
    auto ps_obj1 = rapp::object::pose_stamped(ps_obj0);
    BOOST_CHECK(ps_obj0 == ps_obj1);

    auto ps_obj2 = rapp::object::pose_stamped();
    BOOST_CHECK(ps_obj0 == ps_obj2);

    auto ps_obj3 = rapp::object::pose_stamped(header0, pose0);
    auto ps_obj4 = rapp::object::pose_stamped(header0, pose0);
    BOOST_CHECK(ps_obj3 == ps_obj4);

    const auto pose1 = ps_obj4.get_pose();
    auto quat1 = pose1.get_orientation();
    BOOST_CHECK(quat == quat1);
    
    auto point1 = pose1.get_position();
    BOOST_CHECK(point == point1);

    auto header1 = ps_obj4.get_header();
    auto frameid1= header1.get_frame();
    auto seq1 = header1.get_seq();
    auto time1 = header1.get_time();
    BOOST_CHECK_EQUAL(frameid1, frameid0);
    BOOST_CHECK_EQUAL(seq1, seq0);
    BOOST_CHECK_EQUAL(time1.seconds(),1464949299);
    BOOST_CHECK_EQUAL(time1.nanoseconds(),93018853);

    auto ps_obj5 = ps_obj4;
    BOOST_CHECK(ps_obj4 == ps_obj5);
}

/**
 * \brief TEST for planned_path object
 *
 * In the same way that the classes before
 * the constructors are checked creating identical
 * objects and comparing between them.
 *
 * For methods, we take the parameters and 
 * they are compared with the objects created for
 * initialize that object.
 */
BOOST_AUTO_TEST_CASE(object_planned_path_test)
{
    std::chrono::nanoseconds t(1464949299093018853);
    auto time0 = rapp::object::time(t);
    int seq0 = 0;
    std::string frameid0 = "map";
    auto header0 = rapp::object::msg_metadata(seq0 , time0, frameid0);
   
    auto quat =rapp::object::quaternion(0, 
                                        0, 
                                        0.17576372515799546, 
                                        0.9844323810798712);

    auto point = rapp::object::point(0.9999999776482582, 
                                     0.9999999776482582, 
                                     0);

    auto pose0 = rapp::object::pose( point, quat);
    auto ps_obj0 = rapp::object::pose_stamped(header0, pose0);

    auto pp_obj = rapp::object::planned_path();
    auto pp_obj1 = rapp::object::planned_path();
    BOOST_CHECK(pp_obj == pp_obj1);

    auto pp_obj2 = rapp::object::planned_path(pp_obj);
    BOOST_CHECK(pp_obj == pp_obj2);

    std::vector<rapp::object::pose_stamped> ps_vector;
    ps_vector.push_back(ps_obj0);
    auto pp_obj3 = rapp::object::planned_path(1, "", ps_vector);
    auto pp_obj4 = rapp::object::planned_path(1, "", ps_vector);
    BOOST_CHECK(pp_obj3 == pp_obj4); 
    BOOST_CHECK_EQUAL(pp_obj3.get_plan(), 1);
    BOOST_CHECK_EQUAL(pp_obj3.get_error(), "");
    BOOST_CHECK(pp_obj3.get_path() == ps_vector);

    auto pp_obj5 = pp_obj4;
    BOOST_CHECK(pp_obj4 == pp_obj5);
}

/**
 * \brief TEST for qr_code object
 *
 * The constructor are checked creating identical
 * objects and comparing between them.
 *
 * For methods, we take the parameters and 
 * they are compared with the objects created for
 * initialize that object.
 */
BOOST_AUTO_TEST_CASE(object_qr_code_test)
{
    auto qr0 = rapp::object::qr_code();
    auto qr1 = rapp::object::qr_code();
    BOOST_CHECK(qr0 == qr1);

    auto qr2 = rapp::object::qr_code(qr0);
    BOOST_CHECK(qr0 == qr2);

    auto qr3 = rapp::object::qr_code( 0.1f, 0.1f, "test");
    auto qr4 = rapp::object::qr_code( 0.1f, 0.1f, "test");
    BOOST_CHECK(qr3 == qr4);

    BOOST_CHECK_EQUAL(qr4.label(), "test");

    auto qr5 = qr4;
    BOOST_CHECK(qr4 == qr5);
}

/**
 * \brief TEST for human object
 *
 * The constructor are checked creating identical
 * objects and comparing between them.
 *
 * For methods, we take the parameters and 
 * they are compared with the objects created for
 * initialize that object.
 */
BOOST_AUTO_TEST_CASE(object_human_test)
{
    auto human0 = rapp::object::human();
    auto human1 = rapp::object::human();
    BOOST_CHECK(human0 == human1);

    auto human2 = rapp::object::human(human0);
    BOOST_CHECK(human0 == human2);

    auto human3 = rapp::object::human( 0.1f, 0.2f, 0.3f, 0.4f);
    auto human4 = rapp::object::human( 0.1f, 0.2f, 0.3f, 0.4f);
    BOOST_CHECK(human3 == human4);

    BOOST_CHECK_EQUAL(human4.get_left_x(), 0.1f);
    BOOST_CHECK_EQUAL(human4.get_left_y(), 0.2f);   
    BOOST_CHECK_EQUAL(human4.get_right_x(), 0.3f);
    BOOST_CHECK_EQUAL(human4.get_right_y(), 0.4f);

    auto human5 = human4;
    BOOST_CHECK(human4 == human5);
}

/**
 * \brief TEST for face object
 *
 * The constructor are checked creating identical
 * objects and comparing between them.
 *
 * For methods, we take the parameters and 
 * they are compared with the objects created for
 * initialize that object.
 */
BOOST_AUTO_TEST_CASE(object_face_test)
{
    auto face0 = rapp::object::face();
    auto face1 = rapp::object::face();
    BOOST_CHECK(face0 == face1);

    auto face2 = rapp::object::face(face0);
    BOOST_CHECK(face0 == face2);

    auto face3 = rapp::object::face(0.1f, 0.2f, 0.3f, 0.4f);
    auto face4 = rapp::object::face(0.1f, 0.2f, 0.3f, 0.4f);
    BOOST_CHECK(face3 == face4);

    BOOST_CHECK_EQUAL(face4.get_left_x(), 0.1f);
    BOOST_CHECK_EQUAL(face4.get_left_y(), 0.2f);   
    BOOST_CHECK_EQUAL(face4.get_right_x(), 0.3f);
    BOOST_CHECK_EQUAL(face4.get_right_y(), 0.4f);

    auto face5 = face4;
    BOOST_CHECK(face4 == face5);
}

/**
 * \brief TEST for picture object
 *
 * The constructor are checked creating identical
 * objects and comparing between them.
 *
 * To compare different images a vector of images
 * is created, to verify all of them
 */

BOOST_AUTO_TEST_CASE(object_picture_test)
{
    std::vector<std::string> infiles = { "tests/data/object_classes_picture_1.png", 
                                         "tests/data/object_classes_picture_2.jpg", 
                                         "tests/data/object_classes_picture_3.png", 
                                         "tests/data/object_classes_picture_4.jpg", 
                                         "tests/data/object_classes_picture_5.jpg", 
                                         "tests/data/object_classes_picture_6.jpg" };

    // Construct from a file-path
    rapp::object::picture lena(infiles[0]);

    for (auto it = infiles.begin() + 1; it != infiles.end(); ++it) {
        // Construct from a file-path
        rapp::object::picture picture1(*it);

        // Open a byte steam from file, and construct the picture
        std::ifstream bytestream(*it, std::ios::in | std::ios::binary | std::ios::ate);
        rapp::object::picture b_copy(bytestream);
        BOOST_CHECK(picture1 == b_copy);

        // Copy constructor
        rapp::object::picture r_copy = picture1;
        BOOST_CHECK(picture1 == r_copy);

        // Assignment
        rapp::object::picture asmt = picture1;
        BOOST_CHECK(asmt == picture1);

        BOOST_CHECK(lena != picture1);
    }
}

/**
 * \brief TEST for audio object
 *
 * The constructors are checked creating identical
 * objects and comparing between them.
 *
 * Different audios are saved in a vector and 
 * they are used to compare between formats.
 */
BOOST_AUTO_TEST_CASE(object_audio_test)
{
    // audio tests
    std::vector<std::string> infiles = { "tests/data/object_classes_audio_1.ogg", 
                                         "tests/data/object_classes_audio_2.wav" 
                                       };

    rapp::object::audio t1(infiles.at(0));
    std::ifstream bytes1(infiles.at(0), std::ios::in | std::ios::binary | std::ios::ate);
    rapp::object::audio t1_ifstrm(bytes1);

    BOOST_CHECK(t1 == t1_ifstrm);

    rapp::object::audio t2(infiles.at(1));
    rapp::object::audio t2_cpy = t2;

    BOOST_CHECK( t2 == t2_cpy );
}

BOOST_AUTO_TEST_SUITE_END()
