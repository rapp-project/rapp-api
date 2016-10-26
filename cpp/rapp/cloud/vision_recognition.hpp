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
#include <rapp/objects/point.hpp>
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
 * \class learn_object
 * \brief learn object gives by the user
 * \version 0.7.0
 * \date October 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class object_detection_learn_object : public http_request
{
public:
    /**
    * \brief Constructor
    * \param fname is the path (id) of model image
    * \param user is the user name
    * \param name is the name of the object
    * \param callback is the function that will receive an int with the result 
    */
    object_detection_learn_object(
                                   const rapp::object::picture & image,
                                   const std::string name,
                                   const std::string user,
                                   std::function<void(int)> callback
                                 );
	/**
	 * \brief handle the rapp-platform JSON reply
	 */
    void deserialise(std::string json) const;

private:
    std::function<void(int)> delegate_;
};

/**
 * \class clear_models
 * \brief Clears operational memory for selected user
 * \version 0.7.0
 * \date October 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class object_detection_clear_models : public http_request
{
public:
    /**
    * \brief Constructor
    * \param user is the user name
    * \param callback is the function that will receive an int 
    */
    object_detection_clear_models(
                                    const std::string user,
                                    std::function<void(int)> callback
                                 );
    
	/**
	 * \brief handle the rapp-platform JSON reply
	 */
    void deserialise(std::string json) const;

private:
    std::function<void(int)> delegate_;
};

/**
 * \class load_models
 * \brief Load one or more models to operational memory
 * \version 0.7.0
 * \date October 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class object_detection_load_models : public http_request
{
public:
    /**
    * \brief Constructor
    * \param user is the user name
    * \param names is the object names to load
    * \param callback is the function that will receive a string
    */
    object_detection_load_models(
                                  const std::string user,
                                  const std::vector<std::string> names,
                                  std::function<void(int)> callback
                                );
    
	/**
	 * \brief handle the rapp-platform JSON reply
	 */
    void deserialise(std::string json) const;

private:
    std::function<void(int)> delegate_;
};

/**
 * \class find_objects
 * \brief user can provide query image to detect objects
 * \version 0.7.0
 * \date October 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class object_detection_find_objects : public http_request
{
public:
    /**
    * \brief Constructor
    * \param fname is the path (id) of query image
    * \param user is the user name
    * \param limit is the limit search to N best matches
    * \param callback is the function that will receive the objects found
    */
    object_detection_find_objects(
                                  const rapp::object::picture & image,
                                  const std::string user,
                                  const int limit,
                                  std::function<void(std::vector<std::string>,
                                                     std::vector<rapp::object::point>, 
                                                     std::vector<double>,
                                                     int)> callback
                                );
    
	/**
	 * \brief handle the rapp-platform JSON reply
	 */
    void deserialise(std::string json) const;

private:
    std::function<void(std::vector<std::string>,
                       std::vector<rapp::object::point>, 
                       std::vector<double>,
                       int)> delegate_;
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
    /// The callback called upon completion of receiving the qr codes
    std::function<void(std::vector<rapp::object::qr_code>)> delegate_;
};

}
}
#endif
