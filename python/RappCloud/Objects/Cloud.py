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


## @file Objects/Cloud.py
#
#  @copyright Rapp Projecty EU 2015
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#

from RappCloud.Objects import (
    File,
    Payload
    )



class CloudRequest(object):
  """ Cloud Request object class """

  def __init__(self, payload=None, files=[]):
    """! Constructor

    @param payload Payload - The request payload data.
    @param files Array - Array of File objects to attach to the request.
    """

    if (type(payload).__name__ is not 'Payload') and (payload is not None):
      raise TypeError("Argument payload is not of type Payload")
    for f in files or []:
      if type(f).__name__ is not 'File':
        raise TypeError("Value of argument files is not of type File")

    # Private to protect overwrite
    self.__payload = payload
    self.__files = files


  @property
  def payload(self):
    """! Request Payload getter

    @return Payload: The request payload object.
    """
    return self.__payload


  @property
  def files(self):
    """! Request Files getter

    @return Array: Array of File objects of the request.
    """
    return self.__files


  def unpack(self):
    """! Return payload and files objects [payload, files]

    @return Returns Payload and Array of File objects attached
    to the request.
    """
    return self.__payload, self.__files



class CloudResponse(object):
  """ Cloud Response object class """

  def __init__(self, respDic):
    """! Constructor

    @param respDic dict: Response key-value pairs.
    """
    for key, value in respDic.iteritems():
      setattr(self, key, value)


  def serialize(self):
    """! Serialize CloudResponse object to a dict.

    @return dictionary: Serialized response to dictionary.
    """
    return self.__dict__
