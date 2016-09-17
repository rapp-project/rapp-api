/*
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
#include <rapp/cloud/service_controller.hpp>
#include <rapp/cloud/cognitive_exercises.hpp>
#include <iostream>
/*
 * \brief Example for all cognitive classes
 */
int main()
{
    /*
     * \param platform it has to be initialized with 
     * the address, the port and the token of the server
     */
	rapp::cloud::platform info = {"rapp.ee.auth.gr", "9001", "rapp_token"}; 

    /*
	 * \param  service controler is initialized with 
     * the platform data. It has to control the information
     * between us and the server for having a response.
     */
	rapp::cloud::service_controller ctrl(info);

    /*
     * The following example shows how to use cognitive_test_selector class
     * \param functor is a callback for taking all the data about the test
     */
    auto functor = [](std::vector<std::string> questions,
                      std::vector<std::vector<std::string>> possible_ans,
                      std::vector<std::string> correct_ans,
                      std::string test_i,
                      std::string test_y,
                      std::string test_s) {

        std::cout<< "Questions: "<<std::endl;
        for (std::string obj : questions) {
            std::cout<< obj << std::endl;
        }
        std::cout<< "Possible answers: "<<std::endl;
        for (auto arr : possible_ans) {
            for (std::string str : arr) {
                std::cout<< str << std::endl;
            }
        }
        std::cout<< "Correct answers: "<<std::endl;
        for (std::string obj : correct_ans) {
            std::cout<< obj <<std::endl;
        }

        std::cout<< "Test instance: "<< test_i <<std::endl;
        std::cout<< "Test type: "<< test_i <<std::endl;           
        std::cout<< "Test subtype: "<< test_i <<std::endl;
        std::cout<< " ------ " << std::endl;
    };

    /*
     * \brief A call is done to the controller to take the tests that
     * we want.
     * For more information \see rapp::cloud::cognitive_test_selector
     */
    ctrl.make_call<rapp::cloud::cognitive_test_selector>("ArithmeticCts", 
                                                         "TransactionChangeCts", 
                                                         "1", 
                                                         "1", 
                                                         functor);

    /*
     * The following example shows how to use cognitive_record_performance
     * class.
     *
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a string with the records of the test selected     
     * */
    auto sb_cb = [](std::string json) { 
        std::cout << json << std::endl;
        std::cout<< " ------ " << std::endl;
    };

    /*
     * \brief Call done to the controller to take the records of the test
     * selected.
     * For more information \see rapp::cloud::cognitive_record_performance
     */
	ctrl.make_call<rapp::cloud::cognitive_record_performance>("ArithmeticCts_stXqnGrc", 40, sb_cb);

    /*
     * The following example we use class cognitive_get_history to take
     * all the results of the user in the test selected or all of them.
     * 
     * Like in the examples above, we use an inline lambda as the callback 
     * With it, we read the content of the json given
     */
    auto it_cb = [](std::string str) {
        std::cout << str << std::endl;        
        std::cout<< " ------ " << std::endl;
    };

    /*
     * \brief Call done to the controller to use cognitive_get_history and
     * take the result of the test in a time given.
     * For more information \see rapp::cloud::cognitive_get_history
     */
    ctrl.make_call<rapp::cloud::cognitive_get_history>(0, 100000000, "", it_cb);

    /*
     * The following example we use class cognitive_get_score to take
     * the scores in the test selected from a time given.
     * 
     * Like in the examples above, we use an inline lambda as the callback 
     * With it, we read the tests selected and the results.
     */
    auto call_scores = [](std::vector<std::string> t_c, std::vector<float> scores) {
        std::cout<< "Test_classes: "<<std::endl;
        for (std::string obj: t_c) {
            std::cout<<obj <<std::endl;
        }
        std::cout<< "Scores: "<<std::endl;
        for (unsigned int obj: scores) {
            std::cout<<obj <<std::endl;
        }
        std::cout<< " ------ " << std::endl;
    };

    /*
     * \brief Call done to the controller to use cognitive_get_scores and
     * take the scores of the test in a time given.
     * For more information \see rapp::cloud::cognitive_get_scores
     */
    ctrl.make_call<rapp::cloud::cognitive_get_scores>(100000000, "", call_scores);
    return 0;
}
