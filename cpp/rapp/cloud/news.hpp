#ifndef RAPP_CLOUD_NEWS
#define RAPP_CLOUD_NEWS
#include "includes.ihh"
#include <rapp/cloud/asio/http_request.hpp>
namespace rapp {
namespace cloud {
/**
 * \brief get news
 * \class news_explore
 * \version 0.7.0
 * \date September 2016
 * \author Maria Ramos Montero <m.ramos@ortelio.co.uk>
 */
class news_explore : public http_request
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
                  std::function<void(std::vector<std::vector<std::string>>)> callback
                );

    /**
     * \brief handle platform's JSON reply
     */
	void deserialise(std::string json) const;

private:
    ///Member 
    std::function<void(std::vector<std::vector<std::string>>)> delegate_;
};
}
}
#endif
