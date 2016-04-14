#ifndef RAPP_ASIO_HELPER
#define RAPP_ASIO_HELPER
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class asio_helper
 * \version 1
 * \date April 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 * \brief helper functions for asio services
 */
class asio_helper
{
public:

	/// Create a random boundary for the multipart/form in HTTP
    std::string random_boundary() const
    {
        std::string chars("abcdefghijklmnopqrstuvwxyz"
                          "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                          "1234567890");
        boost::random::random_device rng;
        std::string uid;
        // Randomly chose 16 characters
        boost::random::uniform_int_distribution<> index_dist(0, chars.size() - 1);
        for (int i = 0; i < 16; ++i){
            uid.push_back(chars[index_dist(rng)]);
		}
        return uid;
    }

    // escape JSON strings when sending them over the socket
    std::string escape_string(const std::string & str) 
    {
        std::ostringstream ss;
        for (auto iter = str.cbegin(); iter != str.cend(); iter++) {
            switch (*iter) {
                case '\\': ss << "\\\\"; break;
                case '"': ss << "\\\""; break;
                case '/': ss << "\\/"; break;
                case '\b': ss << "\\b"; break;
                case '\f': ss << "\\f"; break;
                case '\n': ss << "\\n"; break;
                case '\r': ss << "\\r"; break;
                case '\t': ss << "\\t"; break;
                default: ss << *iter; break;
            }
        }
        return ss.str();
    } 

	// decode base64
    std::string decode64(const std::string &val)
    {
        using namespace boost::archive::iterators;
        using It = transform_width<binary_from_base64<std::string::const_iterator>, 8, 6>;
        return boost::algorithm::trim_right_copy_if(std::string(It(std::begin(val)), 
																It(std::end(val))), 
																[](char c) {return c == '\0';});
    }

	// encode base64
    std::string encode64(const std::string &val)
    {
        using namespace boost::archive::iterators;
        using It = base64_from_binary<transform_width<std::string::const_iterator, 6, 8>>;
        auto tmp = std::string(It(std::begin(val)), It(std::end(val)));
        return tmp.append((3 - val.size() % 3) % 3, '=');
    }
};
}
}
#endif
