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


## @file Objects/Payload.py
#
#  @copyright Rapp Projecty EU 2016
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#

import json

class Payload(object):
    """ Payload object class """
    def __init__(self, **kwargs):
        for key, value in kwargs.iteritems():
            setattr(self, key, value)


    def __eq__(self, other):
        """! Equality method """
        return self.serialize() == other.serialize()


    def append(self, **kwargs):
        """! Append key-value pairs to the request payload.

        @param **kwargs - Keyword arguments. Key-Value pairs to append to the
        payload.
        """
        for key, value in kwargs.iteritems():
            setattr(self, key, value)


    def remove(self, toDelAttr):
        """! Remove payload properties

        @param toDelAttr (Array) - Array of Strings for properties to remove from
        the payload.
        """
        for key in kwargs.iteritems():
            delattr(self, key)


    def serialize(self):
        """! Serialize to Dictionary

        @return dictionary - Request Payload dictionary.
        """
        return { k:v for k,v in vars(self).items() if not k.startswith('_') or callable(v) }


    def make_json(self):
        """! Serialize to Dictionary and create a json string

        @return json - Request Payload json string.
        """
        return json.dumps(self.serialize())

