#ifndef RAPP_CLOUD_EMAIL
#define RAPP_CLOUD_EMAIL
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
 * \brief fetch email(s)
 * \class email_fetch
 * \version 0.7.0
 * \date August 2016
 */
class email_fetch : public http_request
{
public:
    /** 
     * \brief construct in order to acquire email(s)
     * \param email: user's email address
     * \param pwd: user's plain-text password
     * \param server: email imap address
     * \param port: email imap port
     * \param email_status: which mail is requested (ALL, UNSEEN)
     * \param from_date: fetch emails since date (unix timestamp)
     * \param to_date: fetch emails to date (unix timestamp)
     * \param num_emails: number of emails requested
     * \param callback will receive a JSON string with acquired email(s)
     */
     email_fetch(
                 const std::string email,
                 const std::string pwd,
                 const std::string server,
                 const std::string port,
                 const std::string email_status,
                 const unsigned int from_date,
                 const unsigned int to_date,
                 const unsigned int num_emails,
                 std::function<void(std::string)> callback
                );

    /**
     * \brief handle platform's JSON reply
     */
	void deserialise(std::string json) const;
    
private:
    // 
    std::function<void(std::vector<std::string>)> delegate_;
};

/**
 * \brief send an email
 * \class email_send
 * \version 0.7.0
 * \date August 2016
 */
class email_send : public http_request
{
public:
    /** 
     * \brief construct in order to send email
     * \param email: user's email address
     * \param pwd: user's plain-text password
     * \param server: email imap address
     * \param port: email imap port
     * \param recipients: vector of email addresses
     * \param body: email body
     * \param subject: email subject
     * \param data: data attached to the email
     * \param callback may receive a JSON reply of error(s)
     */
     email_send(
                 const std::string email,
                 const std::string pwd,
                 const std::string server,
                 const std::string port,
                 const std::vector<std::string> recipients,
                 const std::string body,
                 const std::string subject,
                 const std::vector<rapp::types::byte> data,
                 std::function<void(void)> callback
               );
	
    /**
     * \brief handle platform's JSON reply
     */
	void deserialise(std::string json) const;
   
private:
    /// 
    std::function<void(void)> delegate_;
};
}
}
#endif
