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
#include "cloud/service_controller/service_controller.hpp"
#include "cloud/cognitive_exercises/cognitive_exercises.hpp"
#include <iostream>
///
/// query subclasses and superclass of of argv[1]
///
int main(int argc, char* argv[])
{
    using namespace std::string_literals;

    /// \param platform it has to be initialized with 
    /// the address, the port and the token of the server
	rapp::cloud::platform info = {"rapp.ee.auth.gr", "9001", "rapp_token"}; 

	/// \param  service controler is initialized with 
    /// the platform data. It has to control the information
    /// between us and the server for having a response.
	rapp::cloud::service_controller ctrl(info);

	// callback - print json information
    auto sb_cb = [](std::string json)
				 { std::cout << json; };

    // callback for take nlohmann::json::iterator
    // With it, we read the content of the json given
    auto it_cb = [](nlohmann::json::const_iterator it_records)
                 {
                     for ( auto it = it_records->begin(); it != it_records->end(); it++)
                     {
                         std::cout<< it->get<std::string>() << std::endl;
                     }
                 };
    // Example for class cognitive_test_selector
    /// \param functor is a callback for taking all the 
    /// data about the test
    auto functor = [] (std::vector<std::string> questions,
                       std::vector<std::string> possible_ans,
                       std::vector<std::string> correct_ans,
                       std::string test_i,
                       std::string test_y,
                       std::string test_s) 
    {

        std::cout<< "Questions: "<<std::endl;
        for (std::string obj: questions) {
            std::cout<< obj << std::endl;
        }

        std::cout<< "Possible answers: "<<std::endl;
        for (std::string obj: possible_ans) {
            std::cout<< obj << std::endl;
        }

        std::cout<< "Correct answers: "<<std::endl;
        for (std::string obj: correct_ans) {
            std::cout<< obj <<std::endl;
        }

        std::cout<< "Test instance: "<< test_i <<std::endl;
        std::cout<< "Test type: "<< test_i <<std::endl;           
        std::cout<< "Test subtype: "<< test_i <<std::endl;
    };

    /// \brief A call is done to the controller to use
    /// cognitive_test_selector
    ///
    /// \param test_type (String): Cognitive Exercise test type.
    /// ('ArithmeticCts', 'AwarenessCts', 'ReasoningCts') 
    /// \param test_subtype (String): Use this to force select 
    /// from this subtype. Defaults to empty string "".
    /// \param test_diff (String): Use this to force select from 
    /// this difficulty. Defaults to empty string "".
    /// \param test_index (String): Use this to force select 
    /// from this id. Defaults to empty string "".
    /// \param functor is the callback that we made before. 
    ctrl.make_call<rapp::cloud::cognitive_test_selector>( "ArithmeticCts", 
                                                          "TransactionChangeCts", 
                                                          "1", 
                                                          "1", 
                                                          functor);

    
    // Example for class cognitive_record_performance

    /// \brief Call done to the controller to use cognitive_record_performance
    /// 
    /// \param test_instance (String): Cognitive Exercise test instance. 
    /// The full cognitive test entry name as returned by the cognitive_test_chooser web service.
    /// \param score (Integer): User's performance score on given test entry. 
	ctrl.make_call<rapp::cloud::cognitive_record_performance>("ArithmeticCts_stXqnGrc", 40, sb_cb);

    //Example for class cognitive_get_history

    /// \brief Call done to the controller to use cognitive_get_history
    ///
    /// \param test_type (String): Cognitive Exercise test type. 
    /// \param from_time (Integer): Unix timestamp.
    /// \param to_time (Integer): Unix timestamp.
    /// \param callback for taking the values
    ctrl.make_call<rapp::cloud::cognitive_get_history>(0, 100000000, "", it_cb);

    //Example for class cognitive_get_scores

    // function to get the values of the class and see them
    auto call_scores = [](std::vector<unsigned int> t_c, std::vector<float> scores){
        
        std::cout<< "Test_classes: "<<std::endl;
        for ( unsigned int obj: t_c) {
            std::cout<<obj <<std::endl;
        }

        std::cout<< "Scores: "<<std::endl;
        for ( unsigned int obj: scores) {
            std::cout<<obj <<std::endl;
        }
    };

    /// \brief Call done to the controller to use cognitive_get_score
    ///
    /// \param test_type (String): Cognitive Exercise test type.     
    /// \param up_to_time (Integer): Unix timestamp. Return scores that 
    /// have been recorder up to this time value
    ctrl.make_call<rapp::cloud::cognitive_get_scores>(100000000, "", call_scores);

    return 0;
}
