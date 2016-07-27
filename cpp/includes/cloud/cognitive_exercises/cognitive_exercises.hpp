#ifndef RAPP_CLOUD_COGNITIVE_EXERCISES
#define RAPP_CLOUD_COGNITIVE_EXERCISES
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class cognitive_test_selector
 * \brief chose a congitive game to play 
 * \version 0.6.0
 * \date April 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class cognitive_test_selector : public asio_service_http
{
public:

	/// callback functor
	typedef std::function<void(std::vector<std::string>,
                               std::vector<std::string>,
                               std::vector<std::string>,
                               std::string,
                               std::string,
                               std::string)> functor;

	/**
	 * \brief handler obtains a cognitive test from cloud.rapp
	 * \param user set the user
     * \param test_type set the test type
     * \param callback receives arrays of strings and strings
	 */
	cognitive_test_selector(
							const std::string user,
							const std::string test_type,
                            functor callback,
						   )
	: asio_service_http(), delegate_(callback)
	{
        boost::property_tree::ptree tree;
        tree.put("test_type", test_type);
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        post_ = ss.str();

		// set the HTTP header URI pramble and the Content-Type
        head_preamble_.uri = "POST /hop/cognitive_test_selector HTTP/1.1\r\n";
        head_preamble_.content_type = "Content-Type: application/x-www-form-urlencoded";

        callback_ = std::bind(&cognitive_test_selector::handle_reply, this, std::placeholders::_1);
	}
private:
    /**
     * \brief handle platform's JSON reply
     */
	void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        std::vector<std::string> questions;
        std::vector<std::string> possib_ans;
        std::vector<std::string> correct_ans;
        std::string test_instance;
        std::string test_type;
        std::string test_subtype;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);
            // NOTE: untested!
            for (auto child : tree.get_child("questions")) {
                questions.push_back(child.second.get_value<std::string>());
            }
            for (auto child : tree.get_child("possib_ans")) {
                possib_ans.push_back(child.second.get_value<std::string>());
            }
            for (auto child : tree.get_child("correct_ans")) {
                correct_ans.push_back(child.second.get_value<std::string>());
            }
            for (auto child : tree.get_child("test_instance")) {
                test_instance = child.second.get_value<std::string>();
            }
            for (auto child : tree.get_child("test_type")) {
                test_type = child.second.get_value<std::string>();
            }
            for (auto child : tree.get_child("test_subtype")) {
                test_subtype = child.second.get_value<std::string>();
            }
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "cognitive_test_selector JSON error: " << value << std::endl;
                }
            }
	    }
        catch (boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "cognitive_test_selector::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate_(questions,
                  possib_ans,
                  correct_ans,
                  test_instance
                  test_type,
                  test_subtype);
    }

    /// 
    std::function<void(std::vector<std::string>,
                       std::vector<std::string>,
                       std::vector<std::string>,
                       std::string,
                       std::string,
                       std::string)> delegate_;
};

/**
 * \class cognitive_record_performance
 * \version 0.6.0
 * \date May-2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
class cognitive_record_performance : public asio_service_http
{
public:
    /**
     * \brief record performance for a cognitive test
     * \param test_instance sets the actual test
     * \param score is the recorded score
     * \param callback receives the platform's response
     */
     cognitive_record_performance(
                                    const std::string test_instance,
                                    const float score,
                                    std::function<void(std::string)> callback
                                 )
    : asio_service_http(), delegate_(callback)
    {
        boost::property_tree::ptree tree;
        tree.put("test_instance", test_instance);
        tree.put("score", boost::lexical_cast<std::string>(score));
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        post_ = ss.str();

		// set the HTTP header URI pramble and the Content-Type
        head_preamble_.uri = "POST /hop/cognitive_record_performance HTTP/1.1\r\n";
        head_preamble_.content_type = "Content-Type: application/x-www-form-urlencoded";

        callback_ = std::bind(&cognitive_record_performance::handle_reply, this, std::placeholders::_1);
    }

private:
    /**
     * \brief handle platform's JSON reply
     */
    void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        std::string performance_entry;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

            // NOTE: untested!
            for (auto child : tree.get_child("performance_entry")) {
                performance_entry = second.get_value<std::string>();
            }

            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "cognitive_record_performance JSON error: " << value << std::endl;
                }
            }
	    }
        catch (boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "cognitive_record_performance::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate_(performance_entry);
    }

    ///
    std::function<void(std::string)> delegate_;
};

/**
 * \class cognitive_get_history
 * \version 0.6.0
 * \date May 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
class cognitive_get_history : public asio_service_http
{
public:
    /**
     * \brief get history of cognitive game
     * \param from_time is a unix timestamp
     * \param to_time is a unix timestamp
     * \param test_type is the cognitive test
     * \param callback will receive a JSON reply
     */
    cognitive_get_history(
                            unsigned int from_time,
                            unsigned int to_time,
                            const std::string test_type,
                            std::function<void(std::string)> callback
                         )
    : asio_service_http(), delegate_(callback)
    {
        boost::property_tree::ptree tree;
        tree.put("from_time", boost::lexical_cast<std::string>(from_time));
        tree.put("to_time", boost::lexical_cast<std::string>(to_time));
        tree.put("test_type", test_type);
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        post_ = ss.str();

		// set the HTTP header URI pramble and the Content-Type
        head_preamble_.uri = "POST /hop/cognitive_get_history HTTP/1.1\r\n";
        head_preamble_.content_type = "Content-Type: application/x-www-form-urlencoded";

        callback_ = std::bind(&cognitive_get_history::handle_reply, this, std::placeholders::_1);
    }
private:
    /**
     * \brief forward (don't parse) platform reply
     */
    void handle_reply(std::string json)
    {
        delegate_(std::move(json));
    }

    ///
    std::function<void(std::string)> delegate_;
};

/**
 * \class cognitive_get_scores
 * \version 0.6.0
 * \date May 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
class cognitive_get_scores : public asio_service_http
{
public:
    /**
     * \brief get cognitive test scores
     * \param up_to_time defines scores queried up to that unix timestamp
     * \param test_type the test type
     * \param callback will receive an array of test classes and respective scores
     */
    cognitive_get_scores(
                          unsigned int up_to_time,
                          const std::string test_type,
                          std::function<void(std::vector<unsigned int>, std::vector<float>)> callback
                        )
    : asio_service_http(), delegate_(callback)
    {
        boost::property_tree::ptree tree;
        tree.put("up_to_time", boost::lexical_cast<std::string>(from_time));
        tree.put("test_type", test_type);
        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        post_ = ss.str();

		// set the HTTP header URI pramble and the Content-Type
        head_preamble_.uri = "POST /hop/cognitive_get_scores HTTP/1.1\r\n";
        head_preamble_.content_type = "Content-Type: application/x-www-form-urlencoded";

        callback_ = std::bind(&cognitive_get_scores::handle_reply, this, std::placeholders::_1);
    }
private:
    /**
     * \brief handle platform's JSON reply
     */
    void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        std::vector<unsigned int> test_classes;
        std::vector<float> scores;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

            // NOTE: untested!
            for (auto child : tree.get_child("test_classes")) {
                test_classes.push_back(second.get_value<unsigned int>());
            }

            for (auto child : tree.get_child("scores")) {
                scores.push_back(second.get_value<float>());
            }

            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "cognitive_get_scores JSON error: " << value << std::endl;
                }
            }
	    }
        catch (boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "cognitive_get_scores::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate_(test_classes, scores);
    }

    ///
    std::function<void(std::vector<unsigned int>,
                       std::vector<float>)> delegate_;
};
}
}
#endif
