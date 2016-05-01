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


## @file RappCloud/CloudServices/CognitiveGetHistory.py
#
#  @copyright Rapp Projecty EU 2015
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


from Service import *
from RappCloud.Objects import (
    File,
    Payload
    )


class CognitiveGetHistory(Service):
  """ CognitiveGetHistory Cloud Service class. """

  def __init__(self, **kwargs):
    """!
    Constructor

    @param **kwargs - Keyword arguments. Apply values to the request attributes.
      - @ref time_from
      - @ref time_to
      - @ref test_type
    """

    # Cloud Service request arguments
    # -------------------------------------------------------------
    ## Unix timestamp. Retrieve history from this time value.
    self.time_from = 0
    ## Unix timestamp. Retrieve history up to this time value.
    self.time_to = 0
    ## Cognitive Exercise test type. Can be one of:
    # - 'ArithmeticCts'
    # - 'AwarenessCts'
    # - 'ReasoningCts'
    # - '' for all
    self.test_type = ''
    # -------------------------------------------------------------

    super(CognitiveGetHistory, self).__init__(
        svcname='cognitive_get_history', **kwargs)


  def _make_payload(self):
    """ Make request payload object """
    return Payload(
        test_type=self.test_type,
        to_time=self.time_to,
        from_time=self.time_from)


  def _make_files(self):
    """ Create array of file object(s) """
    return []
