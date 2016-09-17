#include <iostream>
#include <rapp/config/config.hpp>
///
int main(int argc, char * argv[])
{	
	// load the YAML config file sample
	auto conf = rapp::config::load_yaml_config("data/config.yaml");
	// load a token config file sample
	conf.token = rapp::config::load_auth_token("data/token");

	std::cout << "address: " << conf.address << "\r\n";
	std::cout << "port: " << conf.port << "\r\n";
	std::cout << "protocol: " << conf.protocol << "\r\n";
	std::cout << "auth_token: " << conf.token << "\r\n";

	return 0;
}
