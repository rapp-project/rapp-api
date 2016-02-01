#ifndef RAPP_CLOUD_COGNITIVE_TEST_CHOSER
#define RAPP_CLOUD_COGNITIVE_TEST_CHOSER
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class cognitive_test_choster
 * \brief chose a congitive game to play 
 * \version 1
 * \date January 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class cognitive_test_choser : public rapp::services::asio_service_http
{
public:
	/**
	 * \brief handler obtains a cognitive test from cloud.rapp
	 * \param user set the user
     * \param test_type set the test type
	 */
	cognitive_test_choser(
							const std::string user,
							const std::string test_type,
							std::function<void(std::string)> callback
						 )
	: rapp::services::asio_service_http (), delegate_(callback)
	{
		std::string boundary = random_boundary();
		post_  = "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"user\"\r\n\r\n";
		post_ += user + "\r\n";
		post_ += "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"test_type\"\r\n\r\n";
		post_ += test_type + "\r\n"; 
		post_ += "--" + boundary + "--";
        // Count Data size
        auto size = post_.size() * sizeof(std::string::value_type);
        header_ =  "POST /hop/cognitive_test_choser HTTP/1.1\r\n";
        header_ += "Host: " + std::string(rapp::cloud::address) + "\r\n";
        header_ += "Connection: close\r\n";
        header_ += "Content-Length: " + boost::lexical_cast<std::string>(size) + "\r\n";
        header_ += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n\r\n";
        // bind the base class callback, to our handle_reply
        callback_ = std::bind(&cognitive_test_choser::handle_reply, this, std::placeholders::_1);
	}

private:

	void handle_reply(std::string json)
    { 
		delegate_(json);		
	}

	std::function<void(std::string)> delegate_; 
};
}
}
#endif
