#include "asio_handler.hpp"
namespace rapp {
namespace cloud {

void asio_handler::error_handler(const boost::system::error_code & error)
{
    std::cerr << "error: " << error.message() << std::endl;
}

void asio_handler::invalid_request(const std::string message)
{
    std::cerr << "invalid http request: " <<  message << std::endl;
}

void asio_handler::content_length(std::string response, std::size_t & length)
{
    static const boost::regex reg("Content-Length:\\s[-0-9]+", 
                                  boost::regex::icase);
    boost::match_results<std::string::const_iterator> results;
    // search for matching regex
    if (boost::regex_search(response, results, reg)) {
        if (results.size() > 0) {
            std::string key = results[0];
            key.erase(std::remove(key.begin(), 
                                  key.end(), '\n'), 
                                  key.end());
            // find the `: `
            std::string hay = ": ";
            std::size_t i = key.find(hay);
            if (i != std::string::npos) {
                length = boost::lexical_cast<std::size_t>(
                                    key.substr(i+hay.size(), std::string::npos));
            }
            else {
                std::cerr << "malformed `Content-Lengtht` delimiter" << std::endl;
            }
        }
    }
}

bool asio_handler::has_content_length(std::string response)
{
    static const boost::regex reg("Content-Length:\\s[-0-9]+", boost::regex::icase);
    boost::match_results<std::string::const_iterator> results;
    // search for matching regex
    if (boost::regex_search(response, results, reg)) {
        return (results.size() > 0 ? true : false);
    }
    else {
        return false;
    }
}

std::string asio_handler::strip_header(std::string response)
{
    // find the "\r\n\r\n" double return after the header
    std::size_t i = response.find("\r\n\r\n");
    if (i != std::string::npos) {
        return response.substr(i+4, std::string::npos);
    }
    else {
        throw std::runtime_error("no double return after header");
    }
}

std::string asio_handler::random_boundary() const
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

std::string asio_handler::escape_string(const std::string & str) 
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

std::string asio_handler::decode64(const std::string &val)
{
    using namespace boost::archive::iterators;
    using It = transform_width<binary_from_base64<std::string::const_iterator>, 8, 6>;
    return boost::algorithm::trim_right_copy_if(std::string(It(std::begin(val)), 
                                                            It(std::end(val))), 
                                                            [](char c) {return c == '\0';});
}

std::string asio_handler::encode64(const std::string &val)
{
    using namespace boost::archive::iterators;
    using It = base64_from_binary<transform_width<std::string::const_iterator, 6, 8>>;
    auto tmp = std::string(It(std::begin(val)), It(std::end(val)));
    return tmp.append((3 - val.size() % 3) % 3, '=');
}

}
}
