#ifndef RAPP_OBJECT_MSG_METADATA
#define RAPP_OBJECT_MSG_METADATA
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
#include <rapp/objects/time.hpp>
namespace rapp {
namespace object {
/**
 * \class msg_metadata
 * \brief encapsulates metadata of another class (e.g. pose)
 * \version 0.6.0
 * \date 25 August 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
class msg_metadata
{
public:
    /**
     * \brief Consruct using sequence nr, time stamp and frameid
     * \param seq defines data sequence
     * \param stamp is message data generation time stamp
     * \param frameid is data coordination frame
     */
    msg_metadata(
					int seq,
					rapp::object::time stamp,
					std::string frameid
				  );
    
    /// \brief disable Empty Consructor
    msg_metadata() = default;
    
    /// \brief default copy Conatructor
    msg_metadata(const rapp::object::msg_metadata &) = default;

	/// \brief construct using `json for modern C++`
    msg_metadata(const json::const_iterator & metadata);
       
    /// \return a json object
    json::object_t to_json() const; 

    /// return the param stamp_
    rapp::object::time get_time() const;

    /// \return the param seq_
    int get_seq() const;

    /// \return the param frameid_
    std::string get_frame() const;

    /** 
     * \brief equality operator
     * \note compare all components
     */
    bool operator==(const rapp::object::msg_metadata & rhs) const;

private:
	/// members
	int seq_ = 0;
	rapp::object::time stamp_;
    std::string frameid_ = "map";
};
}
}
#endif
