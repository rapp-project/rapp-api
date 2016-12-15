#ifndef RAPP_ASIO_TIMER
#define RAPP_ASIO_TIMER
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
#include <boost/asio.hpp>
namespace rapp{
namespace cloud {
/**
 * \class asio_response
 * \version 0.7.0
 * \date 12 August 2016 
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 * \brief used by asio_handler to detect connection time-outs 
 */
class asio_timer
{
public:
    /** 
	 * \brief construct
	 * \param callback will be executed if theres a timeout
	 */
    asio_timer(boost::asio::io_service &);

    /// \brief set the timer with \param seconds
    void set_timeout(unsigned int arg);

	/// \brief reset the timer
    void reset();

private:

	/// \brief check if timer has timed out
    void check_timeout();

	//std::function<void()> callback_;
    boost::asio::deadline_timer timer_;
};
}
}
#endif
