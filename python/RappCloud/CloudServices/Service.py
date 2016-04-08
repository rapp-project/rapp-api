#!/usr/bin/env python


# Copyright 2015 RAPP

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


class Service(object):
    def __init__(self, **kwargs):
        self._controller = ServiceControllerSync()
        self._svcName = ''
        self._reqPayload = {}
        self._reqFiles = []
        self._cloudResp = CloudResponse({})
        self._cloudReq = CloudRequest()

        for key, value in kwargs.iteritems():
            # If object has attribute set value.
            if hasattr(self, key):
                setattr(self, key, value)


    def get_response(self):
        return self._cloudResp


    def get_request(self):
        return self._cloudReq


    def set_service_name(self, name):
        self._svcName = name


    ##
    #  @brief Call Cloud Service.
    #
    def call(self):
        self._make_payload()
        self._make_files()
        cloudResponse = self._controller.run_job( \
                self._svcName,
                self._reqPayload,
                self._reqFiles)
        print cloudResponse
        self._cloudResp = CloudResponse(cloudResponse)
        return self._cloudResp


    @abstractmethod
    def _make_payload(self):
        raise NotImplementedError()


    @abstractmethod
    def _make_files(self):
        raise NotImplementedError()


