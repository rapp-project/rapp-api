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


## @file RappCloud/CloudServices/SetNoiseProfile.py
#
#  @copyright Rapp Projecty EU 2015
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


from Service import *
from RappCloud.Objects import (
    File,
    Payload
    )


class SetNoiseProfile(Service):
  """ SetNoiseProfile Cloud Service class """

  def __init__(self, **kwargs):
    """!
    Constructor

    @param **kwargs - Keyword arguments. Apply values to the request attributes.
      - @ref audio_source
      - @ref audiofile
    """

    # Cloud Service request arguments
    # -------------------------------------------------------------
    ##  Audio source data format. e.g "nao_wav_1_ch".
    self.audio_source = ''
    ## Path to the audio file.
    self.audiofile = ''
    # -------------------------------------------------------------

    super(SetNoiseProfile, self).__init__(
        svcname='set_noise_profile',
        **kwargs
        )


  def _make_payload(self):
    """ Make request payload object """
    return Payload(audio_source = self.audio_source)


  def _make_files(self):
    """ Create array of file object(s) """
    return [File(self.audiofile, 'file')]
