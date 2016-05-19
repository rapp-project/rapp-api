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


## @file RappCloud/Service/RappPlatformService.py
#
#  @copyright Rapp Projecty EU 2016
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#

from RappCloud.ServiceController import ServiceControllerSync


class RappPlatformService(object):
    """ Service class """

    def __init__(self, msg=None, persistent=True, timeout=None,
                 **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
        """
        for key, value in kwargs.iteritems():
            pass

        # Cloud Object passed to the RappPlatformService.
        self.__cloudObj = msg
        # Persistent connection value (Boolean)
        self.__persistent = persistent
        # Client timeout value (Number)
        self.__timeout = timeout

        ## Service Name
        if msg is not None:
            self.__svcname = msg.svcname
        else:
            self.__svcname = ''
        ## Service Url path. Will be applied by the ServiceController
        self.__urlpath = ''
        # Create service controller object. Pass the service instance
        # for the service controller to hold.
        ## A Cloud Service holds a ServiceController instance.
        self.__controller = ServiceControllerSync(self)


    @property
    def svcname(self):
        """! Service name getter """
        return self.__svcname

    @property
    def persistent(self):
        """! Service persistent connection value getter """
        return self.__persistent

    @persistent.setter
    def persistent(self, val):
        """! Service persistent connection value setter """
        self.__persistent = val


    @property
    def timeout(self):
        """! Service timeout value getter """
        return self.__timeout


    @timeout.setter
    def timeout(self, val):
        """! Service timeout value setter """
        self.__timeout = val


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
        return self.__cloudObj.req if self.__cloudObj is not None else None


    @property
    def resp(self):
        """! Service response object getter """
        return self.__cloudObj.resp if self.__cloudObj is not None else None


    @resp.setter
    def resp(self, val):
        """! Service response object setter """
        self.__cloudObj.resp = val



    def call(self, msg=None):
        """! Call the RAPP Platform Service """
        if msg is not None:
            self.__cloudObj = msg
            self.__svcname = msg.svcname
        if self.__cloudObj is None:
            raise AttributeError('Missing Cloud Message object!')
        cloudResponseDic = self.__controller.run_job()
        for key, val in cloudResponseDic.iteritems():
            self.resp.set(key, val)
        return self.resp
