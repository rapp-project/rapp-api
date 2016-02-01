#ifndef RAPP_CLOUD_RECORD_COG_TEST_PERF
#define RAPP_CLOUD_RECORD_COG_TEST_PERF
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
class record_cognitive_test_performance : public rapp::services::asio_service_http
{
public:
	/**
	 * \brief record congitive performance
	 * \param user the user who did the test
	 * \param test_instance the test performed
	 * \param score the score achieved
	 * \note you must provide a callback which will obtain and parse
	 *       the json reply from the cloud.
	 */
	record_cognitive_test_performance(
										const std::string user,
										const std::string test_instance,
										const std::string score,
										std::function<void(std::string)> callback
									 )
	: rapp::services::asio_service_http (), delegate_(callback)
	{
		std::string boundary = random_boundary();
		post_  = "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"user\"\r\n\r\n";
		post_ += user + "\r\n";
		post_ += "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"test_instance\"\r\n\r\n";
		post_ += test_instance + "\r\n"; 
		post_ += "--" + boundary + "\r\n";
        post_ += "Content-Disposition: form-data; name=\"score\"\r\n\r\n";
		post_ += score + "\r\n"; 
		post_ += "--" + boundary + "--";
        // Count Data size
        auto size = post_.size() * sizeof(std::string::value_type);
        header_ =  "POST /hop/record_cognitive_test_performance HTTP/1.1\r\n";
        header_ += "Host: " + std::string(rapp::cloud::address) + "\r\n";
        header_ += "Connection: close\r\n";
        header_ += "Content-Length: " + boost::lexical_cast<std::string>(size) + "\r\n";
        header_ += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n\r\n";
        // bind the base class callback, to our handle_reply
        callback_ = std::bind(&record_cognitive_test_performance::handle_reply, this, std::placeholders::_1);
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
