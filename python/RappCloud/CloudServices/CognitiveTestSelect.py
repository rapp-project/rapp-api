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


## @file RappCloud/CloudServices/CognitiveTestSelect.py
#
#  @copyright Rapp Projecty EU 2016
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


from Service import *
from RappCloud.Objects import (
    File,
    Payload
    )


class CognitiveTestSelect(Service):
  """ CognitiveTestSelect Cloud Service class. """

  def __init__(self, **kwargs):
    """!
    Constructor

    @param **kwargs - Keyword arguments. Apply values to the request attributes.
      - @ref test_type
    """

    # Cloud Service request arguments
    # -------------------------------------------------------------
    ## Cognitive Exercise test type. Can be one of:
    # - 'ArithmeticCts'
    # - 'AwarenessCts'
    # - 'ReasoningCts'
    # - ''
    #
    # If left blank, the exercise will be selected based on user's
    # performance history.
    self.test_type = ''
    # Test Subtype according to the test type.
    self.test_subtype = ''
    # Test difficulty
    self.test_diff = ''
    # Test Index
    self.test_index = ''
    # -------------------------------------------------------------

    super(CognitiveTestSelect, self).__init__(
        svcname='cognitive_test_chooser',
        **kwargs
        )


  def _make_payload(self):
    """ Make request payload object """
    return Payload(
        test_type=self.test_type,
        test_subtype=self.test_subtype,
        test_diff=self.test_diff,
        test_index=self.test_index)


  def _make_files(self):
    """ Create array of file object(s) """
    return []
