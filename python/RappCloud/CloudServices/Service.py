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


from abc import abstractmethod

from RappCloud.ServiceController import ServiceControllerSync
from RappCloud.Objects import (
        CloudResponse,
        CloudRequest
        )


##
#  @brief Base Service Class.
#
class Service(object):
    def __init__(self, urlname=''):
        self._controller = ServiceControllerSync(urlname=urlname)
        self.__svcName = urlname
        self.__urlpath = self._controller.get_svc_urlpath()
        self.__cloudResp = CloudResponse({})
        self.__cloudReq = CloudRequest()


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
        self.__make_request_obj()
        cloudResponse = self._controller.run_job( \
                self.__svcName,
                self.__cloudReq)

        self.__cloudResp = CloudResponse(cloudResponse)
        return self.__cloudResp


    ##
    #  @brief Create/Make Cloud Request Object.
    #
    def __make_request_obj(self):
        _payload = self._make_payload()
        _files = self._make_files()
        self.__cloudReq = CloudRequest(payload=_payload, files=_files)


    @abstractmethod
    def _make_payload(self):
        raise NotImplementedError()


    @abstractmethod
    def _make_files(self):
        raise NotImplementedError()


