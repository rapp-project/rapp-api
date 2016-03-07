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
from RAPPAuth import RAPPAuth
import json


## @class CloudInterface
#
#  Cloud Interface class. Service controller for HOP Web Services requests
#  Static class.
#
class ServiceControllerSync(ServiceControllerBase):

  def __init__(self):
    ServiceControllerBase.__init__(self)
    self.protocol = "https"

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
  def run_job(self, url, payload, files):
      #  Python-Requests module does not support empty parameter fields.
      #  Passing empty parameter ('param1': '') will result in a corrupted
      #  payload definition.
      #  Referenced issue on github:
      #      https://github.com/kennethreitz/requests/issues/2651
      #  Below we provide a temporary fix to this issue.
      #      Deleting values from payload literal does the job!

    multiFiles = []
    for f in files:
      fTuple = self.make_file_tuple(f, 'file_uri')
      multiFiles.append(fTuple)

    toRemove = []
    for param in payload:
      if not payload[param]:
        toRemove.append(param)
    for i in toRemove:
      del payload[i]

    resp = self.post_request(url, payload, multiFiles)
    return resp


  def post_request(self, svcUrlName, payload, files):
    svcUrl = self.svc_url(svcUrlName)
    print svcUrl
    try:
      response = requests.post(url=svcUrl, data=payload, files=files,  \
          auth=RAPPAuth("1234"), verify=False)
    except ConnectionError as e:
      print "Cannot resolve domain name [%s]" % url
      print e
      returnData = {
        'error': str(e.message)
      }
    except HTTPError as e:
      print "HTTP Error: %s" % e.message
      returnData = {
        'error': str(e.mesasge)
      }
    except Exception as e: # Catch all exceptions
      returnData = {
        'error': str(e)
      }
    else:
      if self.is_json(response.content):
        returnData = json.loads(response.content)
      else:  # Check if binary data (responseFile)
        # Return file type too
        returnData = {
          'payload': response.content,
          'error': 'Non JSON Response!!!!'
        }
    return returnData

