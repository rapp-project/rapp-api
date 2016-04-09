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


## @file RappCloud/Objects/Cloud.py
#
#  @copyright Rapp Projecty EU 2015
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#

from RappCloud.Objects import (
    File,
    Payload
    )



class CloudRequest(object):
    def __init__(self, payload=None, files=[]):
        if (type(payload).__name__ is not 'Payload') and \
                (payload is not None):
            raise TypeError("Argument payload is not of type Payload")
        for f in files or []:
            if type(f).__name__ is not 'File':
                raise TypeError(\
                    "Value of argument files is not of type File")
        ## Private to protect overwrite
        self.__payload = payload
        self.__files = files


    ##
    #  @brief Return the payload attached to the request object
    #  @returns RappCloud.Objects.Payload
    #
    def payload(self):
        return self.__payload


    ##
    #  @brief Return the files attached to the request object
    #  @returns Array of RappCloud.Objects.File objects
    #
    def files(self):
        return self.__files


    ##
    #  @brief Return payload and files attributes of the request object
    #
    def unpack(self):
        return self.__payload, self.__files



class CloudResponse(object):
    def __init__(self, respDic):
        for key, value in respDic.iteritems():
            setattr(self, key, value)


    ##
    #  @brief Unpack CloudResponse object to a dict and return.
    #
    def serialize(self):
        return self.__dict__
