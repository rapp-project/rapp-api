#ifndef RAPP_ASIO_HTTP_HEADER
#define RAPP_ASIO_HTTP_HEADER
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
 * \class http_header
 * \version 0.7.0
 * \date August 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 * \brief class encapsulates the HTTP Header 1.1 standard
 */
class http_header
{
public:
    /** 
	 * \brief constructor of the http_header
	 * \brief set the \param uri 
	 * \warning requires newline
	 */
    http_header(std::string uri);

    /**
     * \brief make this header a `multipart/form-data`
     * \warning it will modify the HTTP Header
     */
    void make_multipart_form();
    
    /**
	 * \brief complete the rest of parameters that we need for the http_header and 
     * \return all of them in a string
     * \param endpoint contains the data of the platform
     * \param length is the size of the content
	 */
    std::string to_string(rapp::cloud::platform endpoint, unsigned int length);

    /**
	 * \brief get boundary
	 * \return boundary string without they hyphens (--)
	 */
    std::string get_boundary() const;

private:    
    /// URI
	std::string uri_;
	std::string user_agent_;
	std::string connection_;
	std::string content_length_;
	std::string content_type_;
    std::string boundary_;
};
}
}
#endif
