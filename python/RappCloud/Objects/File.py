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


## @file Objects/File.py
#
#  @copyright Rapp Projecty EU 2016
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#

from RappCloud.Utils import RandStrGen
from os import path


class File(object):
    """ File object class """

    def __init__(self, filepath="", postfield="", boundary_size=30):
        """! Constructor

        @param path str -The filepath
        @param postField str - The post field name.
        @param boundary_size int - Size of random boundary string for the
            filename to add on the post field.
        """

        self.__boundarySize = boundary_size
        if filepath is not "":
            self.__path = path.expanduser(path.normpath(filepath))
        else:
            self.__path = ""

        if postfield is not "":
            self.__postfield = postfield
        else:
            # Default data post field name.
            self.__postfield = "file"


    def __eq__(self, other):
        """! Equality method """
        return self.serialize() == other.serialize()


    @property
    def path(self):
        """! file path getter

        @return string - The file path.
        """
        return self.__path


    @path.setter
    def path(self, filepath):
        """! file path setter

        @param path (String) - The file path.
        """
        absPath = path.expanduser(path.normpath(filepath))
        self.__path = absPath


    @property
    def postfield(self):
        """! Post field name getter

        @return string - The post field name.
        """
        return self.__postfield


    @postfield.setter
    def postfield(self, fieldname):
        """! Post field name setter

        @param fieldname (String) - The post field name.
        """
        self.__postfield = fieldname


    def serialize(self):
        return {'path': self.__path, 'field_name': self.__postfield}


    def make_tuple(self):
        # Raise Exception if the file does not exist
        if not path.isfile(self.__path):
            raise Exception('File not found: {0}'.format(self.__path))
        randStr = RandStrGen.create(self.__boundarySize)
        name, ext = path.splitext(path.basename(self.__path))
        filename = ''.join((''.join((name, '-', randStr)), ext))
        return (self.__postfield, (filename, open(self.__path)))

