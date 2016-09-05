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
                    )
    : http_request("POST /hop/ontology_subclasses_of HTTP/1.1\r\n"), 
      delegate__(callback)
    {
        http_request::make_multipart_form();
        std::string fname = rapp::misc::random_boundary()+"."+image.type();

		json json_doc = {{"file", fname}};
        http_request::add_content("json", json_doc.dump(-1), true);
        // add picture bytes
        http_request::add_content("file", fname, image.bytearray());
        http_request::close();

    }
	/**
	 * \brief handle the rapp-platform JSON reply
	 */
    void deserialise(std::string json) const
    {
        if (json.empty()) {
            throw std::runtime_error("empty json reply");
        }
        nlohmann::json json_f;
        try {
            json_f = json::parse(json);
        }
        catch (std::exception & e) {
            std::cerr << e.what() << std::endl;
        }
        auto error = misc::get_json_value<std::string>("error", json_f);
        if (!error.empty()) {
            std::cerr << "error JSON: " << error << std::endl;
        }
        else {
            delegate_(json_f["object_class"]);
        }    
    }

private:
    /// The callback called upon completion of receiving the detected faces
    std::function<void(std::string)> delegate__;
};


}
}
