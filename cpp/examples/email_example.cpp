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
#include "objects/picture/picture.hpp"
#include "cloud/email/email.hpp"
#include <iostream>

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

    /// \brief callback to print data
    auto callb = [](std::string json)
                 { std::cout << json; };

    /// Load an image for sending in a mail and passing in bytes
    rapp::object::picture picture1("tests/data/object_classes_picture_1.png");
    std::vector<rapp::types::byte> data = picture1.bytearray();

    /// Example class email_send

    /// \brief Call to service controller in order to send email
    ///
    /// \param email: user's email address
    /// \param pwd: user's plain-text password
    /// \param server: email imap address
    /// \param port: email imap port
    /// \param recipients: vector of email addresses
    /// \param body: email body
    /// \param subject: email subject
    /// \param data: data attached to the email
    /// \param callback may receive a JSON reply of error(s)

    std::vector<std::string> recipients = {"recipient@example.com",
                                           "recipient2@example.com"};

    ctrl.make_call<rapp::cloud::email_send>("example@example.com",
                                            "pwd",
                                            "https://webmail.example.com",
                                            "143",
                                            recipients,
                                            "body mail",
                                            "subject",
                                            data,
                                            callb);


    /// Example class email_receive

    /// \brief construct in order to acquire email(s)
    /// \param email: user's email address
    /// \param pwd: user's plain-text password
    /// \param server: email imap address
    /// \param port: email imap port
    /// \param email_status: which mail is requested (ALL, UNSEEN)
    /// \param from_date: fetch emails since date (unix timestamp)
    /// \param to_date: fetch emails to date (unix timestamp)
    /// \param num_emails: number of emails requested
    /// \param callback will receive a JSON string with acquired email(s)
    ctrl.make_call<rapp::cloud::email_fetch>("example@example.com",
                                               "pass",
                                               "https://webmail.example.com",
                                               "143",
                                               "ALL",
                                               1469865600, /**< Is equivalent to:07/30/2016 @ 8:00am (UTC) */
                                               1472630400, /**< Is equivalent to:08/31/2016 @ 8:00am (UTC) */ 
                                               200,
                                               callb);


} 
