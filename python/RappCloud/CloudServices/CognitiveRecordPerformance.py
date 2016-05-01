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


## @file RappCloud/CloudServices/CognitiveRecordPerformance.py
#
#  @copyright Rapp Projecty EU 2016
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


from Service import *
from RappCloud.Objects import (
    File,
    Payload
    )


class CognitiveRecordPerformance(Service):
  """ CognitiveRecordPerformance Cloud Service class. """

  def __init__(self, **kwargs):
    """!
    Constructor

    @param **kwargs - Keyword arguments. Apply values to the request attributes.
      - @ref test_instance
      - @ref score
    """

    # Cloud Service request arguments
    # -------------------------------------------------------------
    ## Cognitive Exercise test instance. The full cognitive test entry name.
    self.test_instance = ''
    ## User's performance score to record, on given test instance entry.
    self.score = 0
    # -------------------------------------------------------------

    super(CognitiveRecordPerformance, self).__init__(
        svcname='cognitive_record_performance', **kwargs)


  def _make_payload(self):
    """ Make request payload object """
    return Payload(
        test_instance=self.test_instance,
        score=self.score)


  def _make_files(self):
    """ Create array of file object(s) """
    return []
