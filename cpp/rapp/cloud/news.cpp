#include "news.hpp"
namespace rapp {
namespace cloud {

news_explore::news_explore(
                            const std::string news_engine,
                            const std::vector<std::string> keywords,
                            const std::vector<std::string> exclude_titles,
                            const std::string region,
                            const std::string topic,
                            const unsigned int num_news,
                            std::function<void(std::vector<std::vector<std::string>>)> callback
                          )
: http_request("POST /hop/news_explore HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    json json_doc = {{"news_engine", news_engine},
                     {"keywords", keywords},
                     {"exclude_titles", exclude_titles},
                     {"region", region},
                     {"topic", topic},
                     {"num_news", num_news}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

void news_explore::deserialise(std::string json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    try {
        json_f = json::parse(json);
    }
    catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
    auto error = misc::get_json_value<std::string>("error", json_f);
    if (!error.empty()) {
        std::cerr << "error JSON: " << error <<std::endl;
    }
    else {
        std::vector<std::vector<std::string>> news_stories;
        for (auto obj : json_f["news_stories"]) {
            std::vector<std::string> news = {obj["title"], 
                                             obj["content"], 
                                             obj["publisher"], 
                                             obj["publishedDate"],
                                             obj["url"]};
            news_stories.push_back(news);
        }
        delegate_(news_stories);
    }
}

}
}
