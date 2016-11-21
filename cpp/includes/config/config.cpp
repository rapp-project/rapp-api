#include "config.hpp"

std::string rapp::config::load_auth_token(std::string filename)
{
	if (filename.empty()){
		throw std::runtime_error("empty filename");
	}
	std::ifstream infile(filename);
	if (!infile.is_open()) {
		throw std::runtime_error("failed to open file: " + filename);
	}
	std::string token;
	if (std::getline(infile, token)) {
		return token;
	}
	else {
		return "";
	}
}

rapp::cloud::platform_info rapp::config::load_yaml_config(std::string filename)
{
	if (filename.empty()){
		throw std::runtime_error("empty filename");
	}
	std::ifstream infile(filename);
	if (!infile.is_open()) {
		throw std::runtime_error("failed to open file: " + filename);
	}
	std::string line;
	rapp::cloud::platform_info lhs;
	int i = 1;
	while (std::getline(infile, line)) {
		// process one line
		boost::char_separator<char> sep{":"};
		boost::tokenizer<boost::char_separator<char>> tokens(line, sep);
		std::vector<std::string> list;
		// cleanup: remove spaces, delimiter : and quotes
		for (const auto t : tokens) {
			std::string s(t);
			boost::trim(s);
			boost::replace_first(s, "'", "");
			boost::replace_last(s, "'", "");
			list.push_back(s);
		}
		// line must have two tokens
		if (list.size() == 2){
			// address line
			if (boost::iequals(list.at(0), "address")) {
				lhs.address = list.at(1);
			}
			// port line
			else if (boost::iequals(list.at(0), "port")) {
				lhs.port = list.at(1);
			}
			// protocol line
			else if (boost::iequals(list.at(0), "protocol")) {
				lhs.protocol = list.at(1);
			}
			else {
				throw std::runtime_error("unknown config entry");
			}
		}
		else if (list.size() > 0 && list.size() != 2){
			throw std::runtime_error("malformed line " + 
									 boost::lexical_cast<std::string>(i) + 
									 " in " + filename);
		}
		i++;
	}
	return std::move(lhs);
}
