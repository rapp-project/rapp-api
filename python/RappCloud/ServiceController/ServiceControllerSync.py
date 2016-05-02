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


## @file ServiceController/ServiceControllerSync.py
#
#  @copyright Rapp Projecty EU 2015
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


import requests
from requests.auth import HTTPBasicAuth  # Http basic authentication
from requests.exceptions import *  # Requests Exceptions
from ServiceControllerBase import *

import json

from RAPPAuth import RAPPAuth
from requests.adapters import HTTPAdapter
from Adapters import TLS12Adapter as SSLAdapter


class ServiceControllerSync(ServiceControllerBase):
  """ Synchronous service controller class implementation. """

  def __init__(self, service, connect=None, timeout=None, \
        persistent_connection=True):
    """! Constructor

    @param service Service - Service instance.
    @param connect dictionary - Connection information.
    @param timeout int - Connection timeout value
    @param persistent_connection Boolean - Set by default to True. Set to False
    to disable persistent connections to the server.
    """

    super(ServiceControllerSync, self).__init__(service, timeout=timeout)

    self.persistentConn_ = persistent_connection
    if self.persistentConn_:
      self.__http_persistent_connection()


  def run_job(self):
    """! Run the service"""
    # Unpack payload and file objects from cloud service object
    payload, files  = self._service.req.unpack()

    # Serialize file objects to dictionaries
    _files = []
    for f in files:
      _files.append(f.serialize())
    # ----------------------------------------

    # Serialize payload object to dictionary
    _payload = payload.serialize()

    if self.persistentConn_:
      resp = self.__post_persistent(_payload, _files)
    else:
      resp = self.__post_session_once(_payload, _files)
    return resp


  def __http_persistent_connection(self):
    """! Instantiate a session for this Service instance.

    Forcing to connection: 'keep-alive' and establish http persistent
    connections to the server.
    """
    self.session_ = requests.Session()
    self.__mount_adapters(self.session_)



  def post_request(self, session, data={}, files=[]):
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

    _payload = self._make_payload_dic(data)
    _files = []
    for f in files:
      try:
        fTuble = self._make_file_tuple(f['path'], f['field_name'])
      except Exception as e:
        # Maybe raise exception here to allow external handle
        resp = {
          'error': str(e)
        }
        return resp
      else:
        _files.append(fTuble)

    try:
      resp = session.post(
        url=self._service.url,
        data=_payload,
        files=_files,
        timeout=self._timeout,
        verify=False,
        auth=RAPPAuth()
      )
      # Raise Exception for response status code.
      resp.raise_for_status()
      header = resp.headers
    except Exception as e:
      errorMsg = self.handle_exception(e)
      resp = {
        'error': errorMsg
      }
    else:
      if self.is_json(resp.content):
        resp = json.loads(resp.content)
      elif "This service is unknown!" in resp.content:
        resp = {
          'error': 'Connection Error. Cloud Service does not exist'
        }
      else:
        resp = {
          'payload': resp.content,
          'error': 'Non application/json response'
        }
    return resp


  def __post_session_once(self, data, files):
    """! Post Request while initiating a new session

    @param data dictionary - the data payload to send.
    @param files Array - Array of serialized File objects to send.
    """

    with requests.Session() as session:
      self.__mount_adapters(self.session_)
      resp = self.post_request(session, data, files)
    return resp


  def __post_persistent(self, data, files):
    """! Post Request using active session - persistent connection.

    @param data dictionary - the data payload to send.
    @param files Array - Array of serialized File objects to send.
    """
    return self.post_request(self.session_, data, files)


  def __mount_adapters(self, session):
    """! Mount http and https Transport Adapters to the session

    @param session Session - The session to mount the adapters.
    """

    session.mount("http://", HTTPAdapter())
    session.mount("https://", SSLAdapter())


  def handle_exception(self, exc):
    """! Handles exceptions and return an error message that complies to the Exception caught.

    @param exc Exception of any type
    """

    print exc
    errorMsg = ''
    if type(exc) is ConnectionError:
      errorMsg = "Connection Error"
    elif "401" in str(exc):
      # Unauthorized 401 HTTP Error
      errorMsg = str(exc)
    elif type(exc) is HTTPError:
      errorMsg = "An HTTP error occured"
    elif type(exc) is ConnectTimeout:
      errorMsg = "The request timed out while trying to connect to the remote server"
    elif type(exc) is ReadTimeout:
      errorMsg = "The server did not send any data in the allotted amount of time."
    elif type(exc) is Timeout:
      errorMsg = "Connection Timeout exception."
    else:
      errorMsg = "Catched Exception %s" %exc

    return errorMsg
