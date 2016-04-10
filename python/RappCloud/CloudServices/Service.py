#!/usr/bin/env python


# Copyright 2016 RAPP

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

    #http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Authors: Konstantinos Panayiotou
# contact: klpanagi@gmail.com


## @file RappCloud/CloudServices/Service.py
#
#  @copyright Rapp Projecty EU 2015
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#

from RappCloud.ServiceController import ServiceControllerSync
from RappCloud.Objects import (
        CloudResponse,
        CloudRequest
        )


##
#  @brief Base Service Class.
#
class Service(object):
    def __init__(self, svcname='', **kwargs):
        for key, value in kwargs.iteritems():
            if hasattr(self, key):
                setattr(self, key, value)

        self.svcname = svcname
        self.urlpath = ''
        # Create service controller object. Pass the service instance
        # for the service controller to hold.
        self._controller = ServiceControllerSync(self)


    ##
    #  @brief Return Cloud Response object
    #
    def response(self):
        return self.__cloudResp


    ##
    #  @brief Return Cloud Response object
    #
    def request(self):
        return self.__cloudReq


    ##
    #  @brief Call Cloud Service.
    #
    def call(self):
        self.make_request_obj()
        cloudResponse = self._controller.run_job()
        self.__cloudResp = CloudResponse(cloudResponse)
        return self.__cloudResp


    ##
    #  @brief Create/Make Cloud Request Object.
    #
    def make_request_obj(self):
        _payload = self._make_payload()
        _files = self._make_files()
        self.__cloudReq = CloudRequest(payload=_payload, files=_files)


    def _make_payload(self):
        return Payload()


    def _make_files(self):
        return []


