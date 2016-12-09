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


## @file Utils/Net.py
#
#  @copyright Rapp Projecty EU 2016
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#

from urllib2 import urlopen
import json


class Net(object):
    """ Provide Network related static methods """

    ## Hacky method to get the actual public ip.
    #
    @staticmethod
    def ipaddr_connected():
        """! Prepare a dummy socket to google.com and see what the socket name is.

        @return string - The ipv4 address of the machine.
        """

        url = "http://ip.jsontest.com/"
        info = json.loads(urlopen(url).read().decode('utf-8'))
        return info['ip']
