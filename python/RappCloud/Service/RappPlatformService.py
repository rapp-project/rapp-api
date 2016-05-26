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

import yaml
from os import path
from RappCloud.ServiceController import ServiceControllerSync


class RappPlatformService(object):
    """ Service class """

    def __init__(self, msg=None, persistent=True, timeout=None,
                 address=None, port=None,
                 protocol=None, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
        """

        # Load Default RAPP PLatform parameters from configuration file
        # ~/.congig/rapp_platform_python_api/config
        self.__load_platform_cfg()

        if address is not None:
            self.__platformParams['address'] = address
        if port is not None:
            self.__platformParams['port'] = port
        if protocol is not None:
            self.__platformParams['protocol'] = protocol

        ## Cloud Object passed to the RappPlatformService.
        self.__cloudObj = msg
        ## Persistent connection value (Boolean)
        self.__persistent = persistent
        # Client timeout value (Number)
        self.__timeout = timeout

        ## Service Name
        if msg is not None:
            self.__svcname = msg.svcname
            self.__urlpath = self._make_url(msg.svcname)
        else:
            ## Platform Service name
            self.__svcname = ''
            ## Platform Service Url path
            self.__urlpath = ''

        # Create service controller object. Pass the service instance
        # for the service controller to hold.
        # A Cloud Service holds a ServiceController instance.
        ## Service Controller
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


    def _make_url(self, svcUrlName):
        """! Craft patform service full url path.

        @param svcUrlName string - The service urlname, i.e 'face_detection'

        @returns string - The full service url path.
        """
        return ''.join((self.__platformParams['protocol'], '://',
                        self.__platformParams['address'], ':',
                        self.__platformParams['port'], '/hop/',
                        svcUrlName))


    def call(self, msg=None):
        """! Call the RAPP Platform Service """
        if msg is not None:
            self.__cloudObj = msg
            self.__svcname = msg.svcname
            self.__urlpath = self._make_url(msg.svcname)
        if self.__cloudObj is None:
            raise AttributeError('Missing Cloud Message object!')
        cloudResponseDic = self.__controller.run_job()
        for key, val in cloudResponseDic.iteritems():
            self.resp.set(key, val)
        return self.resp


    def __load_platform_cfg(self):
        _filepath = path.expanduser(
            '~/.config/rapp_platform_python_api/config')

        try:
            f = open(_filepath, 'r')
            _params = yaml.load(f)

        except (IOError, yaml.YAMLError) as exc:
            print str(exc)
            print "Using default parameters:"
            print " * address: 'localhost'"
            print " * port: '9001'"
            print " * protocol: 'http'"
            # If config file does not exist or an exception is raised,
            # fallback to use default parameters.
            _params = {
                'address': 'localhost',
                'port': '9001',
                'protocol': 'http'
            }
        self.__platformParams = _params

