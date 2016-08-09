#define BOOST_TEST_MODULE ObjectTest
#include <boost/test/unit_test.hpp>
#include "../includes/cloud/asio/response.http"

BOOST_AUTO_TEST_SUITE(cloud_classes_test)

/// \brief test `includes/cloud/asio/response.hpp`
BOOST_AUTO_TEST_CASE(cloud_response_test)
{
    BOOST_TEST_MESSAGE("rapp::cloud::response test");

    rapp::cloud::response obj1 = rapp::cloud::response("blah");

    // assignment test
    auto obj2 = obj1;
    BOOST_CHECK(obj1 == obj2);

    // copy constructo test
    auto obj3 = rapp::cloud::response(obj1);
    BOOST_CHECK(obj3 == obj1);

    // check method `to_string`
    BOOST_TEST_MESSAGE("rapp::cloud::response test `to_string` method");
    std::string str_obj1 = obj1.to_string();
    std::string str_hard = "blah";
    BOOST_CHECK(str_obj1 == str_hard);

    // check `strip_to_header`
    BOOST_TEST_MESSAGE("rapp::cloud::response test `strip_http_header`");
    std::string hardcoded_header = "GET /tutorials/other/top-20-mysql-best-practices/ HTTP/1.1\r\n"
                                += "Host: net.tutsplus.com\r\n"
                                += "Accept-Encoding: gzip,deflate\r\n"
                                += "Connection: keep-alive\r\n"
                                += "Content-Length: 9\r\n"
                                += "Cache-Control: no-cache\r\n\r\n";

    std::string stripped = obj1.strip_http_header(hardcoded_header);
    BOOST_CHECK(stripped.is_empty());

    // check method does not have a content length
    BOOST_TEST_MESSAGE("rapp::cloud::response test `has_content_lenght` method");
    std::size_t length = -1;
    std::size_t length_response = obj1.has_content_lenght();
    BOOST_CHECK(length == length_response);

    // check method has valid content length
    auto obj4 = rapp::cloud::response(hardcoded_header);
    std::size_t length2 = 9;
    std::size_t length_response2 = obj4.has_content_length();
    BOOST_CHECK( length2 == length_response2);
}

/// \brief test `includes/cloud/asio/http_header.hpp`
BOOST_AUTO_TEST_CASE(cloud_http_header_test)
{
    BOOST_TEST_MESSAGE("rapp::cloud::http_header test");

    rapp::cloud::http_header head1 = rapp::cloud::http_header();

    //copy constructor test
    auto head2 = head1;
    BOOST_CHECK(head1 == head2);

    //check method `to_string`
    BOOST_TEST_MESSAGE("rapp::cloud::http_header test `to string` method");

    std::string head3 = head1.uri_
                     += "Host: http://example:8080 \r\n"
                     += "User-Agent: rapp_api/cpp/0.7.0\r\n"
                     += "Connection: close\r\n";
                     += "Accept: */*\r\n"
                     += "Accept-Token: token\r\n"
                     += "Content-Length: 8\r\n"
                     += "Content-Type: multipart/form-data; boundary=" +head1.boundary_
                     += "\r\n\r\n";
    
     rapp::cloud::platform_info info = { "http://example", "8080", "token"};
    
     unsigned int length_test = 8;
   
     std::string head4 = head1.to_string(info, length_test);
    
     BOOST_CHECK( head3 == head4);                

    //check method `set_uri`
    BOOST_TEST_MESSAGE("rapp::cloud::http_header test `set_uri` method");
    
    std::string test = "test";
    head1.set_uri(test);
    BOOST_CHECK(head1.uri_ == test);

    //check method `get_boundary`
    BOOST_TEST_MESSAGE("rapp::cloud::http_header test `get_boundary` method");

    std::string test2 = head1.get_boundary();
    BOOST_CHECK(head1.boundary_ == test2);


}

/// \brief test `includes/cloud/asio/http_post.hpp` 
BOOST_AUTO_TEST_CASE(cloud_http_post_test)
{
    BOOST_TEST_MESSAGE("rapp::cloud::http_post test");

    std::string boundary_example = rapp::misc::random_boundary();
    rapp::cloud::http_post post1 = rapp::cloud::http_post::http_post(boundary_example); 

    // assignament test
    auto post2 = post1;
    BOOST_CHECK( post1 == post2);
    
    // check method `add_content`
    BOOST_TEST_MESSAGE("rapp::cloud::http_post test `add_content` method");
    
    std::string name = "ortelio";
    std::string content = "content";
    std::string data_example = post1.data_;

    std::string string_post3 = data_example
                             += "--" + boundary_example + "\r\n";
                             += "Content-Disposition: form-data; name=\""\ + name + "\"\r\n\r\n";
                             += content
                             += "\r\n"; 

    auto post4 = post1;

    post4.add_content(name, content, true);
    BOOST_CHECK(post4.data_ ==string_post3);

    // check method `add_content`
    BOOST_TEST_MESSAGE("rapp::cloud::http_post test `add_content` second method");

    std::string filename = "image";
    std::vector<rapp::types::byte> bytes;
    bytes.push_back(89);
    bytes.push_back(50);

    std::string string_post3 = data_example
                     += "--" + boundary_example + "\r\n"
                     += "Content-Disposition: form-data; name=\""\ + name + "\"\";"
                     += " filename=\"" + filename + "\"\r\n"
                     += "Content-Transfer-Encoding: binary\r\n\r\n";

    string_post3.insert(data_.end(), bytes.begin(), bytes.end());
    string_post3+= "\r\n";                     

    auto post5 = post1;

    post5.add_content(name, filename, bytes);
    BOOST_CHECK(post5.data_ == string_post3);

    // check method `end`
    BOOST_TEST_MESSAGE("rapp::cloud::http_post test `end` method");

    std::string data2 = post1.data_;
    data2 +=  "--" + boundary + "--\r\n";

    auto post6 = post1;
    post6.end();

    BOOST_CHECK(post6.data_ == data2);

    //check method `to_string`
    BOOST_TEST_MESSAGE("rapp::cloud::http_post test `to_string` method");

    std::string data3 = post1.to_string();
    BOOST_CHECK(post1.data_ == data3);

    //check method `size`
    BOOST_TEST_MESSAGE("rapp::cloud::http_post test `size` method");

    std::string data4 = post1.data_;
    unsigned int size1, size2;
    size1 = data4.size()*sizeof(std::string::value_type);
    size2 = post1.size();

    BOOST_CHECK(size1 == size2);

}

/// \brief test`includes/cloud/asio/request.hpp` 
BOOST_AUTO_TEST_CASE(cloud_request_test)
{
    BOOST_TEST_MESSAGE("rapp::cloud::request test");
    
    //check method `fill_buffer`
    BOOST_TEST_MESSAGE("rapp::cloud::request test `request` method");
    
    std::string boundary1 = rapp::misc::random_boundary();
 
    rapp::cloud::http_header head = rapp::cloud::http_header();
    rapp::cloud::http_post post =rapp::cloud::http_post(boundary1);
    rapp::cloud::request request_test = rapp::cloud::request(head, post);

    std::string str = head.to_string() + post.to_string();
    rapp::cloud::platform_info info = {"localhost", "9001", "rapp_token"};


    boost::asio::streambuf buffer;
    // TEST
    request_test.fill_buffer(buffer, info); 

    std::string buf_str((std::istreambuf_iterator<char>(&buffer)), 
                        std::istreambuf_iterator<char>());

    BOOST_CHECK(buf_str == str);
}


BOOST_AUTO_TEST_SUITE_END()
