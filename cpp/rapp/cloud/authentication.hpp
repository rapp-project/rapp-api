#ifndef RAPP_CLOUD_AUTHENTICATION
#define RAPP_CLOUD_AUTHENTICATION
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
#include <rapp/cloud/asio/http_request.hpp>
#include "includes.ihh"

namespace rapp {
namespace cloud {
/**
 * \class login_user
 * \brief class to login the rapp platform
 * \version 0.7.0
 * \date 17 October 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class login_user : public http_request
{
public:

    /**
     * \brief contructor of the login_user class
     * \param username: account username 
     * \param password: account password
     * \param device_token: the device from which the user tries to login
     * \param callback: function which receives the JSON reply
     */
    login_user(std::string username,
               std::string password,
               std::string device_token,
               std::function<void(std::string)> callback              
              );

    /**
     * \brief handle platform's JSON reply
     */
    void deserialise(std::string json);

private:
    ///private members
    std::function<void(std::string)> delegate_;
};

/**
 * \class register_user_from_platform
 * \brief class to create a new user of the rapp platform
 * \version 0.7.0
 * \date 17 October 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class register_user_from_platform : public http_request
{
public:

    /**
     * \brief constructor of the class register_user_from_platform
     * \param creator_username: creator's (robot-admin) RAPP-platform account username
     * \param creator_password: creator's (robot-admin) RAPP-platform account password
     * \param new_user_username: new user's account username
     * \param new_user_password: new user's account password
     * \param language: the user's language
     * \param callback: function which receives the JSON reply
     */
    register_user_from_platform(std::string creator_username,
                                std::string creator_password,
                                std::string new_user_username,
                                std::string new_user_password,
                                std::string language,
                                std::function<void(std::string)> callback
                               );
    /**
     * \brief handle platform's JSON reply
     */
    void deserialise(std::string json);

private:
    ///private members
    std::function<void(std::string)> delegate_;
};

/**
 * class register_user_from_store
 * \brief class to create a new user of the rapp store
 ** \version 0.7.0
 * \date 17 October 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class register_user_from_store : public http_request
{
public:

    /**
     * \brief constructor of the class register_user_from_store
     * \param username: new user's username
     * \param password: new user's password
     * \param device_token: creator device token from RAPP store
     * \param language: the user's account language
     * \param callback: function which receives the JSON reply
     */
    register_user_from_store(std::string username,
                             std::string password,
                             std::string device_token,
                             std::string language,
                             std::function<void(std::string)> callback
                            );
    /**
     * \brief handle platform's JSON reply
     */
    void deserialise(std::string json);

private:
    ///private members
    std::function<void(std::string)> delegate_;
};

}
}
#endif


