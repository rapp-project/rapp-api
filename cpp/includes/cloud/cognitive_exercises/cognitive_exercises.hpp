#ifndef RAPP_CLOUD_COGNITIVE_EXERCISES
#define RAPP_CLOUD_COGNITIVE_EXERCISES
/**
 * Copyright 2015 RAPP
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * #http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class cognitive_test_selector
 * \brief chose a congitive game to play 
 * \version 0.7.0
 * \date 15 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 *
 * \NOTE https://github.com/rapp-project/rapp-platform/tree/master/rapp_web_services/services#cognitive-test-selector
 *		 has changed - will update in 0.7.0
 */
class cognitive_test_selector : public http_request
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
							const std::string test_type,
                            const std::string test_subtype,
                            const std::string test_diff,
                            const std::string test_index,
                            functor callback
						   );
    /**
     * \brief handle platform's JSON reply
     */
	void deserialise(std::string json) const;

private:
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
 * \version 0.7.0
 * \date 15 August 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
class cognitive_record_performance : public http_request
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
                                 );
    /**
     * \brief handle platform's JSON reply
     */
    void deserialise(std::string json) const;

private:
    ///
    std::function<void(std::string)> delegate_;
};

/**
 * \class cognitive_get_history
 * \version 0.7.0
 * \date 15 August 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
class cognitive_get_history : public http_request
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
                         );
    /**
     * \brief forward (don't parse) platform reply
     */
    void deserialise(std::string json) const;

private:

    std::function<void(std::string)> delegate_;
};

/**
 * \class cognitive_get_scores
 * \version 0.7.0
 * \date 15 August  2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
class cognitive_get_scores : public http_request
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
                        );
    
    /**
     * \brief handle platform's JSON reply
     */
    void deserialise(std::string json) const;

private:
    /// Member
    std::function<void(std::vector<unsigned int>,
                       std::vector<float>)> delegate_;
};
}
}
#endif
