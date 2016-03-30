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
import time

from RAPPAuth import RAPPAuth
from requests.adapters import HTTPAdapter
from Adapters import TLSAdapter as SSLAdapter


## @class CloudInterface
#
#  Cloud Interface class. Service controller for HOP Web Services requests
#  Static class.
#
class ServiceControllerSync(ServiceControllerBase):

  def __init__(self, connect, timeout=None, token="", \
          persistent_connection=True):
    self.timeout_ = timeout
    super(ServiceControllerSync, self).__init__()

    self.connection_['ipaddr'] = connect['ipaddr']
    self.connection_['port'] = connect['port']
    self.connection_['protocol'] = connect['protocol']
    self.token_ = "1234"
    self.persistentConn_ = persistent_connection
    if self.persistentConn_:
        # Initialize the Session object to be used for the http
        #  persistent connection
        self.__http_persistent_connection()


  ## Performs Platform's HOP Web Service request.
  #
  #   @param basicAuth Basic http authentication credentials
  #       {'username': '', 'password': ''}
  #   @param url Post request destination Url.
  #   @param payload data payload of the post request.
  #   @param files multipart post file field.
  #
  #   @return Rapp Platform Service response object.
  #
  def run_job(self, svcUrlName, payload, files):
    url = self._svc_url(svcUrlName)

    if self.persistentConn_:
        resp = self.__post_persistent(url, payload, files)
    else:
        resp = self.__post_session_once(url, payload, files)
    return resp


  ##
  #  @brief Create instance Session Object. The Session object is stored
  #   as a member variable. Used to perform http persistent connections
  #   connection: 'heep-alive'
  ##
  def __http_persistent_connection(self):
    self.session_ = requests.Session()
    self.__mount_adapters(self.session_)



  ##
  #  @brief General member method to perform a .post request to the
  #    Platform service.
  #    If files are specified, then multipart/form-data form is used.
  #    Otherwhise, x-www-urlencoded form is used.
  #
  #  @param session The session oject to use for this request.
  #  @param urlpath The complete urlpath of the request.
  #  @param data The data to send. Literal.
  #  @param files Files to send.
  #
  def post_request(self, session, urlpath, data={}, files=[]):
    payload = self._make_payload_dic(data)
    _files = []
    for f in files:
      try:
        fTuble = self._make_file_tuple(f['path'], f['field_name'])
      except Exception as e:
        print e
      else:
        _files.append(fTuble)

    # print payload
    # payload = data
    try:
        resp = session.post(url=urlpath, data=payload, files=_files, \
          timeout=self.timeout_, verify=False, auth=RAPPAuth(self.token_))
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
          'error': 'Connection Error. Service does not exist...is uknown!'
        }
      else:
        resp = {
          'payload': resp.content,
          'error': 'Non application/json response'
        }
    return resp


  def __post_session_once(self, urlpath, data, files):
    with requests.Session() as session:
      self.__mount_adapters(self.session_)
      resp = self.post_request(session, urlpath, data, files)
    return resp


  def __post_persistent(self, urlpath, data, files):
    return self.post_request(self.session_, urlpath, data, files)


  def __mount_adapters(self, session):
    session.mount("http://", HTTPAdapter())
    session.mount("https://", SSLAdapter())

  ##
  #  @brief Load Platform application token by path.
  #  @TODO
  ##
  def __load_token(self, tokenpath):
    pass


  ##
  #  @brief handles exceptions and return an error message that complies to the
  #   Exception caught.
  #
  #  @param exc Exception
  ##
  def handle_exception(self, exc):
    errorMsg = ''
    if type(exc) is ConnectionError:
      errorMsg = "Connection Error"
    elif "401" in str(exc):
      """ Unauthorized 401 HTTP Error """
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
