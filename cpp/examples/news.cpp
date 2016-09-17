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
#include <rapp/cloud/news.hpp>
/*
 *\brief Example of how to get news about what you need  
 */
int main()
{
    /* Construct the platform info setting the hostname/IP, port and authentication token
     * Then proceed to create a cloud controller.
     * We'll use this object to create cloud calls to the platform.
     */
    rapp::cloud::platform info = {"rapp.ee.auth.gr", "9001", "rapp_token"}; 
    rapp::cloud::service_controller ctrl(info);

    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a vector of a vector of strings and 
     * shows all the parameters of news
     */
     auto callback = [&](std::vector<std::vector<std::string>> news) {
         for (auto vec : news) {
             std::cout << "Title: " << vec.at(0) << std::endl;
             std::cout << "Content: " << vec.at(1) << std::endl;
             std::cout << "Publisher: " << vec.at(2) << std::endl;
             std::cout << "Published date: " << vec.at(3) << std::endl;
             std::cout << "Url: " << vec.at(4) << std::endl;
             std::cout << " ------ " <<std::endl;
         }
     };

    /* 
     * We make a call to news_explore, with keywords and some information about
     * what we are looking for. In this example we are looking for corruption 
     * news in Europe.
     * For more information \see rapp::cloud::news_explorer
     */ 
    ctrl.make_call<rapp::cloud::news_explore>("Google News", 
                                              std::vector<std::string>({{"corruption"}}),
                                              std::vector<std::string>({{"Panama"}}),
                                              "Europe", 
                                              "politics", 
                                              3,  
                                              callback);
    return 0;
}
