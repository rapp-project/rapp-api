#ifndef RAPP_HTTP_REQUEST
#define RAPP_HTTP_REQUEST
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
#include "include.ihh"
#include "http_header.hpp"
#include "http_post.hpp"
#include "platform.hpp"

namespace rapp{
namespace cloud{
/**
 * \class http_request
 * \brief wrapper for the classes `http_header` &`http_post` used for cloud requests
 * \version 0.7.0
 * \date 12 August 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 * \see rapp::cloud::http_header
 * \see rapp::cloud::http_post
 */
class http_request : public http_header, public http_post
{
public:
    /**
	 * \brief construct a cloud HTTP request (multipart/form-data)
	 * \param header will contain the URI and setting the multipart boundary
	 * \param post contains the actual POST data
	 * \see rapp::cloud::http_header
	 * \see rapp::cloud::http_post
	 */
    http_request(
				  const rapp::cloud::http_header header, 
				  const rapp::cloud::http_post post
                );

	/**
     * \brief fill the socket streambuf with the request header and post data
     * \param request is a reference to the socket streambuf being modified
     * \param info is the platform endpoint (address, port, etc)
     * \note this method will modify the header by setting the HOST, PORT and TOKEN
	 * \note use this method to satisfy `virtual caller::fill_buffer` polymorphism
	 */
    boost::asio::streambuf fill_buffer(rapp::cloud::platform info);
};
}
}
#endif
