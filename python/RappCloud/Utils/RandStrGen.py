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


## @file RandStrGen/RandStrGen.py
#
#  @copyright Rapp Projecty EU 2015
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


import random
import string


class RandStrGen:
  """ Random String Generator static class (Namespace).

  Generates random string boundaries.
  """

  @staticmethod
  def create(size):
    """! Generate a nwe random string

    @param size string - Number of characters for the random string to generate
    """
    randStr = ''.join(
        random.SystemRandom().choice(
        string.ascii_uppercase + string.ascii_lowercase + string.digits)
        for _ in range(size))

    return randStr
