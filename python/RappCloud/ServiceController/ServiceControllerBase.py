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
# from requests.auth import HTTPBasicAuth  # Http basic authentication
from requests.exceptions import *  # Requests Exceptions
import json
from os import path


class ServiceControllerBase(object):
  ##
  #  TODO
  ##
  def __init__(self):
    self.connection_= {
        "protocol": "http",  # Default
        "ipaddr": "155.207.33.185",
        "port": "9001"
    }


  ##
  #  Check if a dic is represented in json string format.
  #  @param obj dictionary
  ##
  def is_json(self, obj):
    try:
      json.loads(obj)
    except ValueError:
      return False
    return True


  ##
  #  Make file tuples for multipart/form-data http/s requests.
  #  @param filepath The path to the file.
  #  @param optional Http field name value.
  #
  #  {httpFieldName: {filename: '', file descriptor: }}
  ##
  def _make_file_tuple(self, filepath, httpField='file' ):
    filename = self.__basename(filepath)
    tuple_ = (httpField, (filename, open(filepath, 'rb')))
    return tuple_


  ##
  #  @brief Make payload tuple for multipart/form-data http/s requests.
  #  @param payload Data payload - dictionary.
  #  @param httpField Optional http field name value.
  #
  #  {httpFieldName: {filename: '', file descriptor: }}
  ##
  def _make_payload_dic(self, payload, httpField='' ):
    if httpField == '':
      httpField = 'json'
    dic = {httpField: json.dumps(payload)}
    return dic


  def run_job(self):
    raise ValueError('Base ServiceController class method not implemented')


  ##
  # Return the bassename of input filepath.
  ##
  def __basename(self, filepath):
    return path.basename(filepath)


  ##
  #  Craft patform service full url path.
  ##
  def _svc_url(self, svcUrlName):
    return self.connection_['protocol'] + '://' + self.connection_['ipaddr'] + \
        ':' + self.connection_['port'] + '/hop/' + svcUrlName


