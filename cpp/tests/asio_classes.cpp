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

#include <boost/test/unit_test.hpp>
#include "../includes/cloud/asio/http_response.hpp"
#include "../includes/cloud/asio/http_header.hpp"
#include "../includes/cloud/asio/http_post.hpp"
#include "../includes/cloud/asio/http_request.hpp"
#include "../includes/cloud/asio/platform.hpp"
#include "../includes/objects/picture/picture.hpp"

BOOST_AUTO_TEST_SUITE(cloud_classes_test)

/**
 * \brief TEST for http_reponse class
 *
 * First, we check the constructor creating two equal objects and comparing
 * their attribute buffer between them.
 *
 * Second, method 'to_string()' is checked creating an string equal to argument
 * we pass to the constructor, and they are compared.
 *
 * Third, method 'strip_http_header' is checked creating manually a http header
 * and comparing with the header created by the class. It's checked too
 * if it's empty.
 *
 * Last, method 'has_content_lenght' is checked comparing with and size_t with
 * the same size that the header created before, and comparing them.
 */
BOOST_AUTO_TEST_CASE(cloud_response_test)
{
    // header has zero content-length
    std::string hardcoded_header = "GET /tutorials/other/top-20-mysql-best-practices/ HTTP/1.1\r\n"; 
                hardcoded_header += "Host: net.tutsplus.com\r\n";
                hardcoded_header += "Accept-Encoding: gzip,deflate\r\n";
                hardcoded_header += "Connection: keep-alive\r\n";
                hardcoded_header += "Content-Length: 9\r\n";
                hardcoded_header += "Cache-Control: no-cache\r\n\r\n";

    std::string buf = hardcoded_header;
    auto obj1 = std::make_unique<rapp::cloud::http_response>(buf);

    BOOST_CHECK(obj1);
    BOOST_CHECK_EQUAL(9, obj1->content_length());

    auto obj2 = std::make_unique<rapp::cloud::http_response>(buf);
    BOOST_CHECK(obj2);
    BOOST_CHECK_EQUAL(9, obj2->content_length());

    //BOOST_CHECK_EQUAL(*obj2, *obj1);
}

/**
 * \brief TEST for http_header class
 *
 * First,  we check the constructor and the  method 'to_string()' creating manually
 * an http header and comparing with the header created by the class.
 *
 * Second, method 'get boundary' is checked comparing the attibute of the first
 * object with itself
 */
BOOST_AUTO_TEST_CASE(cloud_http_header_test)
{
    std::string ur = "hop/test\r\n";
    rapp::cloud::http_header head1 = rapp::cloud::http_header(ur);

    std::string head2 = "hop/test\r\n";
                head2 += "Host: http://example:8080\r\n";
                head2 += "Accept-Token: token\r\n";
                head2 += "Content-Length: 8\r\n";
                head2 += "\r\n\r\n";
    
    rapp::cloud::platform info = { "http://example", "8080", "token"};
    unsigned int length_test = 8;
    std::string head3 = head1.to_string(info, length_test);
   
    BOOST_CHECK_EQUAL(head3, head2);                

    std::string test2 = head1.get_boundary();
    BOOST_CHECK_EQUAL(head1.get_boundary(), test2);
}

/**
 * \brief TEST for http_post class
 * First, we check the constructor creating two equal objects and comparing
 * their attribute buffer between them.
 *
 * Second, method 'to_string()' is checked creating a post header manually
 * equal that the class creates for comparing them.
 *
 * Third, both methods 'add_content' is checked creating a post data manually
 * and comparing with the one created by the class
 *
 * Last, method 'size' is checked using the same string and calculating
 * the size manually and with the method.
 */ 
BOOST_AUTO_TEST_CASE(cloud_http_post_test)
{
    std::string boundary_example = rapp::misc::random_boundary();
    auto post1 = std::unique_ptr<rapp::cloud::http_post>(new rapp::cloud::http_post(boundary_example)); 
    BOOST_CHECK(post1);

    auto post2 = std::unique_ptr<rapp::cloud::http_post>(new rapp::cloud::http_post(boundary_example));
    BOOST_CHECK(post2);

    // check if two http posts with same boundary are the same
    BOOST_CHECK_EQUAL(post1->to_string(), post2->to_string());
    
    // craft a manual POST Content Disposition and compare it to the method
    std::string string_post3 = post1->to_string()
                             + "--" + boundary_example + "\r\n"
                             + "Content-Disposition: form-data; name=\"blah\"\r\n\r\n"
                             + "blah blah blah"
                             + "\r\n"; 

    auto post4 = std::unique_ptr<rapp::cloud::http_post>(new rapp::cloud::http_post(boundary_example));
    BOOST_CHECK(post4);
    post4->add_content("blah", "blah blah blah", true);

    // compare manual string with method one
    BOOST_CHECK_EQUAL(post4->to_string(), string_post3);

    // load the picture byes
    const std::string file = "tests/data/asio_classes_qr_code_1.png";
    auto pic = std::unique_ptr<rapp::object::picture>(new rapp::object::picture(file));
    BOOST_CHECK(pic);
    const auto bytes = pic->bytearray();
    std::string string_post4 = "--" + boundary_example + "\r\n"
                             + "Content-Disposition: form-data; name=\"blah\";"
                             + " filename=\"" + file + "\"\r\n\r\n";
    string_post4.insert(string_post4.end(), bytes.begin(), bytes.end());
    string_post4 += "\r\n";                     

    auto post5 = std::unique_ptr<rapp::cloud::http_post>(new rapp::cloud::http_post(boundary_example));
    BOOST_CHECK(post5);
    post5->add_content("blah", file, bytes);

    // test the content dispoition for files with manual string
    BOOST_CHECK_EQUAL(post5->to_string(), string_post4);

    // check post sizes
    unsigned int str_size = string_post4.size()*sizeof(std::string::value_type);
    BOOST_CHECK_EQUAL(str_size, post5->size());

    // check post sizes
    BOOST_CHECK(post4->size() != post5->size()); 
}

/**
 *\brief TEST for http_request class
 *
 * This class was checked looking with `cout` command what was the result 
 */
BOOST_AUTO_TEST_CASE(cloud_request_test)
{
    std::string boundary1 = rapp::misc::random_boundary();
    const std::string ur = "ur\r\n";
    std::string ur2 = "ur\r\n";

    auto request_test = rapp::cloud::http_request(ur);
    auto request_2 = std::unique_ptr<rapp::cloud::http_request>(new rapp::cloud::http_request(ur2));
    BOOST_CHECK(request_2);

    rapp::cloud::platform info = {"localhost", "9001", "rapp_token"};
    boost::asio::streambuf buffer;
    request_test.fill_buffer(buffer, info); 
}

BOOST_AUTO_TEST_SUITE_END()
