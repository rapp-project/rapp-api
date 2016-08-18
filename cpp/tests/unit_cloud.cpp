#define BOOST_TEST_MODULE ObjectTest
#include <boost/test/unit_test.hpp>
#include "../includes/cloud/asio/http_response.hpp"
#include "../includes/cloud/asio/http_header.hpp"
#include "../includes/cloud/asio/http_post.hpp"
#include "../includes/cloud/asio/http_request.hpp"
#include "../includes/cloud/asio/platform.hpp"

BOOST_AUTO_TEST_SUITE(cloud_classes_test)

/// \brief test `includes/cloud/asio/response.hpp`
BOOST_AUTO_TEST_CASE(cloud_response_test)
{
    BOOST_TEST_MESSAGE("rapp::cloud::http_response test");

    std::string buf = "Buffer_Example";
    auto obj1 = std::make_unique<rapp::cloud::http_response>(buf);

    // copy constructo test
    auto obj2 = std::make_unique<rapp::cloud::http_response>(buf);

    // NO equality operators
    BOOST_CHECK(obj2->to_string() == obj1->to_string());

    // check method `to_string`
    BOOST_TEST_MESSAGE("rapp::cloud::http_response test `to_string` method");
    std::string str_obj1 = obj1->to_string();
    std::string str_hard = "Buffer_Example";

    /// FAILS
    BOOST_CHECK(str_obj1 == str_hard);

    // check `strip_http_header`
    BOOST_TEST_MESSAGE("rapp::cloud::http_response test `strip_http_header`");
    std::string hardcoded_header = "GET /tutorials/other/top-20-mysql-best-practices/ HTTP/1.1\r\n"; 
                hardcoded_header += "Host: net.tutsplus.com\r\n";
                hardcoded_header += "Accept-Encoding: gzip,deflate\r\n";
                hardcoded_header += "Connection: keep-alive\r\n";
                hardcoded_header += "Content-Length: 9\r\n";
                hardcoded_header += "Cache-Control: no-cache\r\n\r\n";

    std::string stripped = obj1->strip_http_header(hardcoded_header);
    BOOST_CHECK(stripped.empty());

    // check method does not have a content length
    BOOST_TEST_MESSAGE("rapp::cloud::http_response test `has_content_lenght` method");
    std::size_t length = -1;
    std::size_t length_response = obj1->has_content_length();
    BOOST_CHECK(length == length_response);

    // check method has valid content length
    auto obj4 = std::make_unique<rapp::cloud::http_response>(hardcoded_header);
    std::size_t length2 = 9;
    std::size_t length_response2 = obj4->has_content_length();
    BOOST_CHECK(length2 == length_response2);
}

/// \brief test `includes/cloud/asio/http_header.hpp`
BOOST_AUTO_TEST_CASE(cloud_http_header_test)
{
    BOOST_TEST_MESSAGE("rapp::cloud::http_header test");

    std::string ur = "uri\r\n";
    rapp::cloud::http_header head1 = rapp::cloud::http_header(ur);

    //check method `to_string`
    BOOST_TEST_MESSAGE("rapp::cloud::http_header test `to string` method");

    std::string head2 = "uri\r\n";
                head2 += "Host: http://example:8080 \r\n";
                head2 += "User-Agent: rapp_api/cpp/0.7.0\r\n";
                head2 += "Connection: close\r\n";
                head2 += "Accept: */*\r\n";
                head2 += "Accept-Token: token\r\n";
                head2 += "Content-Length: 8\r\n";
                head2 += "Content-Type: multipart/form-data; boundary=" +head1.get_boundary();
                head2 += "\r\n\r\n";
    
    rapp::cloud::platform info = { "http://example", "8080", "token"};
    
    unsigned int length_test = 8;
   
    std::string head3 = head1.to_string(info, length_test);
   
    /// FAILS
    BOOST_CHECK(head3 == head2);                

    //check method `get_boundary`
    BOOST_TEST_MESSAGE("rapp::cloud::http_header test `get_boundary` method");

    std::string test2 = head1.get_boundary();
    BOOST_CHECK(head1.get_boundary() == test2);
}

/// \brief test `includes/cloud/asio/http_post.hpp` 
BOOST_AUTO_TEST_CASE(cloud_http_post_test)
{
    BOOST_TEST_MESSAGE("rapp::cloud::http_post test");

    std::string boundary_example = rapp::misc::random_boundary();
    auto post1 = std::make_unique<rapp::cloud::http_post>(boundary_example); 

    // assignament test
    auto post2 = std::make_unique<rapp::cloud::http_post>(boundary_example);
    // NO equality operators
    BOOST_CHECK(post1->to_string() == post2->to_string());
    
    std::string name = "ortelio";
    std::string content = "content";
    std::string data_example = post1->to_string();

    std::string string_post3 = data_example
                             + "--" + boundary_example + "\r\n"
                             + "Content-Disposition: form-data; name=\"" + name + "\"\r\n\r\n"
                             + content
                             + "\r\n"; 

    auto post4 = std::make_unique<rapp::cloud::http_post>(boundary_example);

    post4->add_content(name, content, true);
    BOOST_CHECK(post4->to_string() == string_post3);

    std::string filename = "image";
    std::vector<rapp::types::byte> bytes;
    bytes.push_back(89);
    bytes.push_back(50);
    std::string string_post4 = data_example
                             + "--" + boundary_example + "\r\n"
                             + "Content-Disposition: form-data; name=\"" + name + "\";"
                             + " filename=\"" + filename + "\r\n"
                             + "Content-Transfer-Encoding: binary\r\n\r\n";

    string_post4.insert(data_example.end(), bytes.begin(), bytes.end());
    string_post3 += "\r\n";                     

    auto post5 = std::make_unique<rapp::cloud::http_post>(boundary_example);

    post5->add_content(name, filename, bytes);
    BOOST_CHECK(post5->to_string() == string_post4);

    // check method `end`
    BOOST_TEST_MESSAGE("rapp::cloud::http_post test `end` method");

    std::string data2 = post1->to_string();
    data2 +=  "--" + boundary_example + "--\r\n";

    auto post6 = std::make_unique<rapp::cloud::http_post>(boundary_example);
    post6->end();

    BOOST_CHECK(post6->to_string() == data2);

    std::string data3 = post4->to_string();
    BOOST_CHECK(string_post3 == data3);

    std::string data4 = post1->to_string();
    unsigned int size1, size2;
    size1 = data4.size()*sizeof(std::string::value_type);
    size2 = post1->size();

    BOOST_CHECK(size1 == size2);
}

/// \brief test`includes/cloud/asio/http_request.hpp` 
BOOST_AUTO_TEST_CASE(cloud_request_test)
{
    std::string boundary1 = rapp::misc::random_boundary();
    const std::string ur = "ur\r\n";
    std::string ur2 = "ur\r\n";

    auto request_test = rapp::cloud::http_request(ur);
    auto request_2 = std::make_unique<rapp::cloud::http_request>(ur2);

    rapp::cloud::platform info = {"localhost", "9001", "rapp_token"};
    //check method `fill_buffer`
    boost::asio::streambuf buffer;
    request_test.fill_buffer(buffer, info); 

    std::cout << request_2->to_string(info);

    //BOOST_CHECK(buf_str == ostr);
}


BOOST_AUTO_TEST_SUITE_END()
