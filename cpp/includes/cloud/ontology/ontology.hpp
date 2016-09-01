#ifndef RAPP_CLOUD_ONTOLOGY
#define RAPP_CLOUD_ONTOLOGY
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
 * \class ontology_subclasses_of
 * \brief get ontology subclass of a query
 * \version 0.7.0
 * \date September 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class ontology_subclasses_of : public http_request
{
public:
    /**
     * \brief constructor for this handler
     * \param query is the entity for which we will try to acquire its Super-Ordinates
     * \param callback is the functor that will receive the classes discovered
     * \param token is the rapp authentication token
     */
    ontology_subclasses_of(
                            std::string ontology_class,
                            bool recursive,
                            std::function<void(std::vector<std::string>)> callback
                          );

    /**
     * \brief handle and parse JSON reply
     */
    void deserialise(std::string json) const;

private:
    /// The callback called upon completion of receiving the detected faces
    std::function<void(std::vector<std::string> classes)> delegate__;
};

/**
 * \class ontology_superclasses_of
 * \brief get ontology super-classes of query
 * \version 0.7.0
 * \date September 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class ontology_superclasses_of : public http_request
{
public:
    /**
     * \param ontology_class is the entity for which we will try to acquire its Super-Ordinates
     * \param callback is the functor that will receive the classes discovered
     * \param token is user authentication token
     */
    ontology_superclasses_of(
                              const std::string ontology_class,
                              bool recursive,
                              std::function<void(std::vector<std::string>)> callback
                            );

    /**
     * \brief handle and parse JSON reply
     */
    void deserialise(std::string json) const;
    
private:
    /// The callback called upon completion of receiving the detected faces
    std::function<void(std::vector<std::string> classes)> delegate__;
};

/**
 * \class ontology_is_subsuperclass_of
 * \brief query if sub class is a super class of param 
 * \version 0.7.0
 * \date September 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class ontology_is_subsuperclass_of : public http_request
{
public:
    /**
     * \brief query if a class is the superclass of a subclass
     * \param parent class queried
     * \param child class queried
     * \param recursive defines a recursive procedure
     * \param callback is the functor that will receive the classes discovered
     * \param token is the rapp authentication token
     */
    ontology_is_subsuperclass_of(
                                   const std::string parent_class,
                                   const std::string child_class,
                                   bool recursive,
                                   std::function<void(bool result)> callback
                                );

    /**
     * \brief handle and parse JSON reply
     */
    void deserialise(std::string json)const;

private:
    /// The callback called upon completion of receiving the detected faces
    std::function<void(bool result)> delegate__;
};
}
}
#endif
