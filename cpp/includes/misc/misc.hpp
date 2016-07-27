#ifndef RAPP_MISC
#define RAPP_MISC
/**
 * \brief common misc helper functions
 * \version 0.6.0
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 * \date July 2016
 */
namespace rapp {
namespace misc {

/// \brief decode base64
/// \param val must be encoded using base64
inline std::string decode64(const std::string &val)
{
	if (val.empty()) {
		throw std::runtime_error("empty string param");
	}
    using namespace boost::archive::iterators;
    using It = transform_width<binary_from_base64<std::string::const_iterator>, 8, 6>;
    return boost::algorithm::trim_right_copy_if(std::string(It(std::begin(val)), 
                                                            It(std::end(val))), 
                                                            [](char c) {return c == '\0';});
}

/// \brief encode base64
/// \param val must be plain-text string
/// \return a base64 encoded string
inline std::string encode64(const std::string &val)
{
	if (val.empty()) {
		throw std::runtime_error("empty string param");
	}
    using namespace boost::archive::iterators;
    using It = base64_from_binary<transform_width<std::string::const_iterator, 6, 8>>;
    auto tmp = std::string(It(std::begin(val)), It(std::end(val)));
    return tmp.append((3 - val.size() % 3) % 3, '=');
}

/// \brief Create a random boundary for the multipart/form in HTTP
inline std::string random_boundary()
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

/// \brief escape JSON strings when sending them over the socket
/// \param str will be escaped and returned
inline std::string escape_string(const std::string & str)
{
	if (str.empty()) {
		throw std::runtime_error("empty string param");
	}
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

}
}

/// convenience function `std::make_unique` for non c++11 compilers
#if __cplusplus==201402L
// c++14 - nothing here
#elif __cplusplus==201103L
// c++11 - 
namespace std {
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}
#endif

#endif
