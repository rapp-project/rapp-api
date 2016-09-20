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

#include <rapp/cloud/service_controller.hpp>
#include <rapp/cloud/vision_detection.hpp>
#include <rapp/objects/picture.hpp>
#include <boost/asio.hpp>
#include <functional>
#include <iostream>

int main() 
{
    boost::asio::io_service io_service;
    boost::asio::deadline_timer timer(io_service, boost::posix_time::seconds(1));

    /*
     * Construct the platform info setting the hostname/IP, port and authentication token
     * Then proceed to create a cloud controller.
     * We'll use this object to create cloud calls to the platform.
     */
    rapp::cloud::platform info = {"rapp.ee.auth.gr", "9001", "rapp_token"}; 
    rapp::cloud::service_controller ctrl(info);

    /*
     * Construct a std::function which is going to be in charge of make the call
	 * reinitialize the timer and call the own function a second later to make an
	 * infinite loop.
     */
	std::function<void(const boost::system::error_code&)> func = [&](const auto & err) {
		auto pic = rapp::object::picture("data/object_classes_picture_1.png");
		auto callback = [&](std::vector<rapp::object::face> faces) { 
			std::cout << "Found " << faces.size() << " faces!" << std::endl;
		};
		ctrl.make_call<rapp::cloud::face_detection>(pic, false, callback);
		timer.expires_at(timer.expires_at() + boost::posix_time::seconds(1));
		timer.async_wait(func);
	};

	/* 
 	 * Asynchronously wait
	 */
	timer.async_wait(func);

    /* 
	 * The timer will fire for the first time 1 second from now
	 */
    io_service.run();
    return 0;
}
