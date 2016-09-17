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

#include <rapp/cloud/service_controller.hpp>
#include <rapp/objects/picture.hpp>
#include <rapp/cloud/email.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
    using namespace std::string_literals;

    // \param platform it has to be initialized with 
    // the address, the port and the token of the server
	rapp::cloud::platform info = {"rapp.ee.auth.gr", "9001", "rapp_token"}; 

	// \param  service controler is initialized with 
    // the platform data. It has to control the information
    // between us and the server for having a response.
	rapp::cloud::service_controller ctrl(info);

    /*
     * Your callback for sending emails - it will receive an error if one did occur
     */
    auto callb = [](std::string error) { 
        if(error.empty()) {
            std::cout << "Message sent correctly" << std::endl; 
        }
    };
    
    /*
     * We can attach files to the email, in this case, an image.
     */
    auto pic = rapp::object::picture("data/object_classes_picture_1.png");

    /*
     * The following example will send an email using your credentials.
     * For detailed information \see rapp::cloud::email_send
     * You have to remember to enable access in your gmail account (if using one)
     * and make sure you're setting the correct SMTP port and parameters.
     */ 
    ctrl.make_call<rapp::cloud::email_send>("rappemailtest@gmail.com",
                                            "XXX",
                                            "smtp.gmail.com",
                                            "587",
                                            std::vector<std::string>({{"your@email.com"}}),
                                            "body mail",
                                            "test",
                                            pic.bytearray(),
                                            callb);
    /*
     * The following example will fetch your email from the server, using \param email address,
     * The \param 1469865600 is a UNIX timestamp equivalent to:07/30/2016 @ 8:00am (UTC)
     * The \param 1473940800 is a UNIX timestamp equivalent to:09/15/2016 @ 12:00am (UTC)
     */
    auto call_fetch = [](std::vector<std::tuple<std::string, 
                                                std::vector<std::string>,
                                                std::string,
                                                std::string,
                                                std::vector<std::string>>> emails) {
        std::cout << "Num emails found: " << emails.size()  << std::endl;
    };
    ctrl.make_call<rapp::cloud::email_fetch>("rappemailtest@gmail.com",
                                             "XXX",
                                             "imap.gmail.com",
                                             "993",
                                             "ALL",
                                             1470009600, 
                                             1473940800,
                                             7,
                                             call_fetch);
} 
