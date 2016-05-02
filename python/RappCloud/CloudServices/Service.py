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
#  @copyright Rapp Projecty EU 2016
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#

from RappCloud.ServiceController import ServiceControllerSync
from RappCloud.Objects import (
        CloudResponse,
        CloudRequest
        )


class Service(object):
    """ Service Base class """

    def __init__(self, svcname='', **kwargs):
        """!
        Constructor

        @param (Optional) svcname The Web Service name.
        @param **kwargs - Keyword arguments. Apply values to the request attributes.
        """
        for key, value in kwargs.iteritems():
            if hasattr(self, key):
                setattr(self, key, value)

        ## Service Name
        self.__svcname = svcname
        ## Service Url path.
        self.__urlpath = ''
        # Create service controller object. Pass the service instance
        # for the service controller to hold.
        ## A Cloud Service holds a ServiceController instance.
        self.__controller = ServiceControllerSync(self)


    @property
    def svcname(self):
        """! Service service name getter """
        return self.__svcname


    @property
    def url(self):
        """! Service urlpath getter """
        return self.__urlpath


    @url.setter
    def url(self, val):
        """! Service urlpath setter """
        self.__urlpath = val


    @property
    def req(self):
        """! Service request object getter """
        return self.__cloudReq


    @req.setter
    def req(self, val):
        """! Service request object setter """
        self.__cloudReq = val


    @req.deleter
    def req(self):
        """! Service request object deleter """
        del self.__cloudReq


    @property
    def resp(self):
        """! Service response object getter """
        return self.__cloudResp


    @resp.setter
    def resp(self, val):
        """! Service response object setter """
        self.__cloudResp = val


    @resp.deleter
    def resp(self):
        """! Service response object deleter """
        del self.__cloudResp


    def call(self):
        """! Call the Platform Service """
        self._make_request_obj()
        cloudResponseDic = self.__controller.run_job()
        self.__cloudResp = CloudResponse(cloudResponseDic)
        return self.__cloudResp


    def _make_request_obj(self):
        """! Create/Make Service request object """
        _payload = self._make_payload()
        _files = self._make_files()
        self.__cloudReq = CloudRequest(payload=_payload, files=_files)


    def _make_payload(self):
        return Payload()


    def _make_files(self):
        return []


