#ifndef RAPP_CLOUD_NEWS
#define RAPP_CLOUD_NEWS
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \brief get news
 * \class news_explore
 * \version 0.7.0
 * \date 15 August 2016
 */
class news_explore : public caller, public http_request
{
public:
    /**
     * \param news_engine: search news engine
     * \param keywords: list desired keywords 
     * \param exclude_titles: list of ecluded titles
     * \param region: language/region
     * \param topic: main news topic
     * \param num_news: number of news stories limit
     * \param callback: receives a JSON reply
     */
    news_explore(
                  const std::string news_engine,
                  const std::vector<std::string> keywords,
                  const std::vector<std::string> exclude_titles,
                  const std::string region,
                  const std::string topic,
                  const unsigned int num_news,
                  std::function<void(std::string)> callback
                )
    : http_header("POST /hop/email_fetch HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()), 
      delegate_(callback)
    {
        boost::property_tree::ptree tree;
        tree.put("news_engine", email);
        tree.put("passwd", pwd);

        boost::property_tree::ptree keyword_array;
        for (const auto key : keywords) {
            keyword_array.push_back(std::make_pair("", key));
        }
        tree.add_child("keywords", keyword_array);

        boost::property_tree::ptree exclude_title_array;
        for (const auto key : exclude_titles) {
            exclude_title_array.push_back(std::make_pair("", key));
        }
        tree.add_child("exclude_titles", exclude_title_array);

        tree.put("region", region);
        tree.put("topic", topic);
        tree.put("num_news", boost::lexical_cast<std::string>(num_news));
        std::stringstream ss;

        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

		// JSON PDT value unquote
        std::string json = rapp::misc::json_unquote_pdt_value<unsigned int>()(ss.str(), num_news);
        http_post::add_content("json", json, false); 
        http_post::end();
     }


    /**
     * \brief handle platform's JSON reply
     */
	void deserialise(std::string json) const
    {
        std::stringstream ss(json);
        delegate_(std::move(json));
    }

    /**
    * \brief method to fill the buffer with http_post and http_header information
    * \param info is the data of the platform    
    */
    boost::asio::streambuf fill_buffer(rapp::cloud::platform info)
    {
           return std::move(http_request::fill_buffer(info));
    }

private:
    /// 
    std::function<void(std::string)> delegate_;
};
}
}
#endif
