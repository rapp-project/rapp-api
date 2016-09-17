#ifndef RAPP_CLOUD_CALLER
#define RAPP_CLOUD_CALLER
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
#include "platform.hpp"

namespace rapp {
namespace cloud {
/**
 * \class caller
 * \brief interface class for cloud objects
 * \version 0.7.0
 * \date 12 August 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class caller
{
public:
    /// \brief JSON deserialisation interface
    virtual void deserialise(std::string) const = 0;

	/** 
	 * \brief fill a stream buffer with HTTP and POST data
	 * \param info specifies the connecting endpoint, port and access token \see platform
	 * \return is a boost stream buffer owned by the caller
	 */
	virtual void fill_buffer(
                              boost::asio::streambuf & request,
                              rapp::cloud::platform info
                            )  = 0;
	
};
}
}
#endif
