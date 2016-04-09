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


## @file RappCloud/Objects/File.py
#
#  @copyright Rapp Projecty EU 2015
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


class File(object):
    def __init__(self, path="", httpField=""):
        self.__path = path
        if httpField is not "":
            self.__httpField = httpField
        else:
            self.__httpField = "file"


    def set_path(self, path):
        self.__path = path


    def set_httpfield(self, fieldname):
        self.__httpField = fieldname


    def serialize(self):
        return {'path': self.__path, 'field_name': self.__httpField}


