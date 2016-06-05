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
from ConfigParser import SafeConfigParser



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


  def __basename(self, filepath):
    """! Return the basename of input filepath. """
    return path.basename(filepath)


