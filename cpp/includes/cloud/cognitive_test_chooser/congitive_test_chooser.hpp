#ifndef RAPP_CLOUD_COGNITIVE_TEST_CHOSER
#define RAPP_CLOUD_COGNITIVE_TEST_CHOSER
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class cognitive_test_choster
 * \brief chose a congitive game to play 
 * \version 0.6.0
 * \date April 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class cognitive_test_choser : public asio_service_http
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
	: asio_service_http(std::get<0>(auth), std::get<1>(auth)), delegate_(callback)
	{
        boost::property_tree::ptree tree;
        tree.put("user", user);
        tree.put("test_type", test_type);
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        post_ = ss.str();

        header_ = "POST /hop/cognitive_test_choser HTTP/1.1\r\n"
                + "Content-Type: application/json\r\n";

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
