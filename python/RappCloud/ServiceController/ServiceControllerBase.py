#!/usr/bin/env python
# -*- coding: utf-8 -*-


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

# Authors: Konstantinos Panayiotou, Manos Tsardoulias
# contact: klpanagi@gmail.com, etsardou@iti.gr


## @file ServiceController/ServiceControllerBase.py
#
#  @copyright Rapp Projecty EU 2015
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


import json
from os import path
import sys

import requests
from requests.auth import HTTPBasicAuth  # Http basic authentication
from requests.exceptions import *  # Requests Exceptions

from RAPPAuth import RAPPAuth
from requests.adapters import HTTPAdapter
from Adapters import TLSAdapter as SSLAdapter



class ServiceControllerBase(object):
    """ Service Controller base class implementation """

    def __init__(self, service):
        """! Constructor

        @param service Service: Service instance
        @param connection dictionary: Connection information.
        @param timeout int: Connection Timeout value.
        """
        ## Cloud Service instance.
        self._service = service

        if self._service.persistent:
            # Hold a session for keep-alive connections.
            self.__session = requests.Session()
            self.__mount_adapters(self.__session)

        self.__auth = RAPPAuth()

        self.__customHeaders = {
            'user-agent': 'rapp-platform-api/python'
        }


    def is_json(self, obj):
        """! Check if it is a json string.

        @param obj string
        @return - True if is a json. False otherwise.
        """
        try:
            json.loads(obj)
        except ValueError:
            return False
        return True


    def run_job(self):
        raise NotImplementedError()


    def basename(self, filepath):
        """! Return the basename of input filepath. """
        return path.basename(filepath)


    def post_request(self, session, url, payload={}, files=[]):
        """! General member method to perform a .post request to the

        Platform service.
        If files are specified, then multipart/form-data form is used.
         Otherwhise, x-www-urlencoded form is used.

        @param session The session oject to use for this request.
        @param urlpath The complete urlpath of the request.
        @param data The data to send. Literal.
        @param files Files to send.

        @return dictionary - Platform Service response.
        """

        _payload = {'json': payload.make_json()}
        _files = []
        for f in files:
          _files.append(f.make_tuple())

        response = {'error': ''}

        try:
            resp = session.post(url=url, data=_payload, files=_files,
                                headers=self.__customHeaders,
                                timeout=self._service.timeout,
                                verify=False, auth=self.__auth)

            # Raise Exception for response status code.
            resp.raise_for_status()
        except Exception as e:
            errorMsg = self.handle_exception(e)
            response = {
                'error': errorMsg
            }
        else:
            # If response Content-Type is set to application/json.
            if "application/json" in resp.headers['content-type']:
                response = json.loads(resp.content)
            elif "This service is unknown!" in resp.content:
                response = {
                    'error': 'Connection Error. Connection could not be established at %s' %self._service.url
                }
            else:
                # Uknown for the API response.
                response = {
                    'payload': resp.content,
                    'error': 'Non application/json response'
                }

        return response


    def _post_session_once(self, url, data, files):
        """! Post Request while initiating a new session

        @param data dictionary - the data payload to send.
        @param files Array - Array of serialized File objects to send.
        """
        with requests.Session() as session:
            self.__mount_adapters(self.__session)
            resp = self.post_request(session, url, data, files)
            return resp


    def _post_persistent(self, url, data, files):
        """! Post Request using active session - persistent connection.

        @param data dictionary - the data payload to send.
        @param files Array - Array of serialized File objects to send.
        """
        return self.post_request(self.__session, url, data, files)


    def __mount_adapters(self, session):
        """! Mount http and https Transport Adapters to the session

        @param session Session - The session to mount the adapters.
        """
        session.mount("http://", HTTPAdapter())
        session.mount("https://", SSLAdapter())


    def handle_exception(self, exc):
        """! Handles exceptions and return an error message that complies to
        the Exception caught.

        @param exc Exception of any type
        """

        print exc
        errorMsg = ''
        if type(exc) is ConnectionError:
            errorMsg = "Connection Error"
        elif "401" in str(exc):
            # Unauthorized 401 HTTP Error
            errorMsg = str(exc)
        elif "500" in str(exc):
            # Internal Server Error
            errorMsg = str(exc)
        elif "404" in str(exc):
            # Client Error. Requested url does not exist!
            errorMsg = str(exc)
        elif type(exc) is HTTPError:
            errorMsg = str(exc)
        elif type(exc) is ConnectTimeout:
            errorMsg = "The request timed out while trying to connect to the remote server"
        elif type(exc) is ReadTimeout:
            errorMsg = "The server did not send any data in the allotted amount of time."
        elif type(exc) is Timeout:
            errorMsg = "Connection Timeout exception."
        else:
            errorMsg = "Catched Exception %s" %exc

        return errorMsg
