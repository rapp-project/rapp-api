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


class Service(object):
    """ Service class """

    def __init__(self, cloud_object=None, persistent=True, timeout=None,
                 **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
        """
        for key, value in kwargs.iteritems():
            pass

        self.__cloudObj = cloud_object
        self._persistent = persistent
        self._timeout = timeout

        ## Service Name
        if cloud_object is not None:
            self.__svcname = cloud_object.svcname
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
        """! Service service name getter """
        return self.__svcname

    @property
    def persistent(self):
        """! Service persistent connection value getter """
        return self._persistent

    @property
    def timeout(self):
        """! Service timeout value getter """
        return self._timeout

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
        return self.__cloudObj.req


    @property
    def resp(self):
        """! Service response object getter """
        return self.__cloudObj.resp


    @resp.setter
    def resp(self, val):
        """! Service response object setter """
        self.__cloudObj.resp = val



    def call(self, cloud_object=object):
        """! Call the Platform Service """
        self.svcname = self.__cloudObj.svcname
        cloudResponseDic = self.__controller.run_job()
        ## TODO Append values to the self.__cloudObj.resp object
