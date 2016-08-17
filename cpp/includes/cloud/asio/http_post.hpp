#ifndef RAPP_ASIO_HTTP_POST
#define RAPP_ASIO_HTTP_POST
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
namespace types {    
typedef char byte;
}
namespace cloud {
/**
 * \class http_post 
 * \brief use to store and pass POST data and realted info  
 * \version 0.7.0
 * \date August 2016
 * \author Maria Ramos<m.ramos@ortelio.co.uk>
 */
class http_post
{
public:
	/**
	 * \brief preferred constructor
	 * \param boundary must be obtained from `http_header::get_boundary()` 
	 * \see http_header
	 */
    http_post(std::string boundary);
    
    /**
	 * \brief add multipart/form-data content to the POST data
     * \param name of the form
     * \param content is the value
     * \param newline adds newline return at the end of content
	 */
    void add_content(
                     const std::string name, 
                     const std::string content,
                     bool newline
                    );

	/**
	 * \brief adding content to the POST data
     * \param name is the name of the string variable
     * \param filename which want to use
     * \param vector contains the data of the file in binary type  
	 * \warning it will add newline return after the bytes
	 */
    void add_content(
                      const std::string name,
                      const std::string filename,
                      const std::vector<rapp::types::byte> bytes
                    );
       
    /// \brief call once, closes the POST boundary
    void end();

    /// \brief get the POST
    std::string to_string() const;

    /// \brief get POST data `Content-Length`
    unsigned int size() const;

private:
    /// POST data
    std::string data_;
    std::string boundary_;
    std::atomic<bool> open_ = {true};
};
}
}
#endif
