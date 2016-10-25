#ifndef RAPP_CLOUD_RECOGNITION
#define RAPP_CLOUD_RECOGNITION
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
#include <rapp/objects/picture.hpp>
#include <rapp/objects/qr_code.hpp>
#include <rapp/cloud/asio/http_request.hpp>
namespace rapp {
namespace cloud {
/**
 * \class object_recognition
 * \brief recognize object from an image
 * \version 0.7.0
 * \date September 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class object_recognition : public http_request
{
public:
    /**
    * \brief Constructor
    * \param image is a picture object pointer
    * \param callback is the function that will receive a string
    */
    object_recognition(
                        const rapp::object::picture & image,
                        std::function<void(std::string)> callback
                      );
    
	/**
	 * \brief handle the rapp-platform JSON reply
	 */
    void deserialise(std::string json) const;

private:
    /// The callback called upon completion of receiving the detected faces
    std::function<void(std::string)> delegate_;
};

/**
 * \class qr_recognition
 * \brief service request to detect QR codes
 * \version 0.7.0
 * \date September 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class qr_recognition : public http_request
{
public:
    /**
    * \brief Constructor
    * \param image is a picture object pointer
    * \param callback is the function that will receive a vector of detected qr(s)
    * \param image_format must be defined, e.g.: jpeg, png, gif, etc.
    */
    qr_recognition(
                    const rapp::object::picture & image,
                    std::function<void(std::vector<rapp::object::qr_code>)> callback
                  );
    /**
	 * \brief handle the rapp-platform JSON reply
	 */
    void deserialise(std::string json) const;
private:
    /// The callback called upon completion of receiving the detected faces
    std::function<void(std::vector<rapp::object::qr_code>)> delegate_;
};

/**
 * \class learn_object
 * \brief learn object gives by the user
 * \version 0.7.0
 * \date October 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class learn_object : public http_request
{
public:
    /**
    * \brief Constructor
    * \param image is a picture object pointer
    * \param callback is the function that will receive a string
    */
    learn_object(
                  const rapp::object::picture &image,
                  const std::string user,
                  const std::string name,
                  std::function<void(int)> callback
                );
    
	/**
	 * \brief handle the rapp-platform JSON reply
	 */
    void deserialise(std::string json) const;

private:
    /// The callback called upon completion of receiving the detected faces
    std::function<void(int)> delegate_;
};

/**
 * \class clear_object
 * \brief Clears operational memory for selected user
 * \version 0.7.0
 * \date October 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class clear_object : public http_request
{
public:
    /**
    * \brief Constructor
    * \param image is a picture object pointer
    * \param callback is the function that will receive a string
    */
    clear_object(
                  const std::string user,
                  std::function<void(int)> callback
                );
    
	/**
	 * \brief handle the rapp-platform JSON reply
	 */
    void deserialise(std::string json) const;

private:
    /// The callback called upon completion of receiving the detected faces
    std::function<void(int)> delegate_;
};

}
}
#endif
