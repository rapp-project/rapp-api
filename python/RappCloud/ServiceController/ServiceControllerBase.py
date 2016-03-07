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
import json
from os import path

class ServiceControllerBase(object):
  ##
  #  TODO
  ##
  def __init__(self):
    pass


  ##
  #  TODO
  ##
  def callService(self):
    pass


  ##
  #  TODO
  ##
  def is_json(self, obj):
    try:
      json.loads(obj)
    except ValueError:
      return False
    return True


  ##
  #  TODO
  ##
  def make_file_tuple(self, filepath, boundaryName ):
    filename = self.basename(filepath)
    tuple_ = (boundaryName, (filename, open(filepath, 'rb')))
    return tuple_


  def post_request(self, url, payload, files, basicAuth):
    pass


  def basename(self, filepath):
    return path.basename(filepath)

