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

  def __init__(self, service, connection=None, timeout=None):
    """! Constructor

    @param service Service: Service instance
    @param connection dictionary: Connection information.
    @param timeout int: Connection Timeout value.
    """
    ## Hold the Cloud Service instance.
    self._service = service
    ## Connection timeout value
    self._timeout = timeout

    self.__cfgDir = path.join(path.dirname(__file__), '../config')
    self._connection = {
        "protocol": "",
        "ipaddr": "",
        "port": ""
    }

    if connection is not None:
        self._connection = connection
    else:
        self.__parse_platform_cfg()

    # Assign urlpath value to the Cloud Service object
    self._service.url = self._svc_url(self._service.svcname)


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


  def _svc_url(self, svcUrlName):
    """! Craft patform service full url path.

    @param svcUrlName string - The service urlname, i.e 'face_detection'
    """

    return self._connection['protocol'] + '://' + self._connection['ipaddr'] + \
          ':' + self._connection['port'] + '/hop/' + svcUrlName


  def __parse_platform_cfg(self):
    """! Parse and load Rapp Platform parameters from config file. """

    cfgFilePath = path.join(self.__cfgDir, 'platform.cfg')
    section = 'RAPP Platform'
    cfgParser = SafeConfigParser()

    try:
      cfgParser.read(cfgFilePath)
    except Exception as e:
      print "Could not load RAPP Platform parameters from .cfg file."
      print e
      sys.exit(1)
    if not cfgParser.has_section(section):
      print "\033[0mCfg file {%s} is missing section [%s]\033[0m" \
        % (cfgFilePath, section)
      sys.exit(1)

    if cfgParser.has_option(section, 'use'):
      useSection = cfgParser.get(section, 'use')
    else:
      print "Missing option under [RAPP Platform] section" + \
                " in cfg file {%s}" % cfgFilePath
      sys.exit(1)

    if not cfgParser.has_section(useSection):
      print "Given value for option <use> in [RAPP Platform] Section" + \
                " does not correspond to a defined Section in cfg file"
      sys.exit(1)

    if cfgParser.has_option(useSection, 'ipv4_addr') and \
            cfgParser.has_option(useSection, 'port'):
      self._connection['ipaddr'] = cfgParser.get(useSection, 'ipv4_addr')
      self._connection['port'] = cfgParser.get(useSection, 'port')
    else:
      print "Missing options {ipv4_addr} and {port} in cfg file [%s]" \
          % cfgFilePath
      sys.exit(1)

    if cfgParser.has_option(useSection, 'protocol'):
      self._connection['protocol'] = cfgParser.get(useSection, 'protocol')
    else:
      print "Missing {protocol} option in platform cfg file." + \
                "Falling back to default {http}"
      self._connection['protocol'] = 'http'


