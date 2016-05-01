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


## @file RappCloud/CloudServices/TextToSpeech.py
#
#  @copyright Rapp Projecty EU 2016
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


import base64
from os import path

from Service import *
from RappCloud.Objects import (
    File,
    Payload
    )


class TextToSpeech(Service):
  """ TextToSpeech Cloud Service class """

  def __init__(self, **kwargs):
    """!
    Constructor

    @param **kwargs - Keyword arguments. Apply values to the request attributes.
      - @ref text
      - @ref language
    """

    # Cloud Service request arguments
    # -------------------------------------------------------------
    ## Input text to translate to audio data.
    self.text = ''
    ## Language to use for recognition
    self.language = ''
    # -------------------------------------------------------------

    super(TextToSpeech, self).__init__(
        svcname='text_to_speech',
        **kwargs
        )


  def get_audio_raw(self):
    """! Get audio raw data from response """
    try:
      b64Data = self.resp.payload
      rawData = base64.b64decode(b64Data)
    except TypeError as e:
      print str(e)
      return None
    return rawData


  def store_audio(self, destfile):
    """! Store returned audio data to an audio file given by path

    @param destfile - Destination file path.
    """

    destfile = path.expanduser(destfile)
    rawData = self.get_audio_raw()
    try:
      with open(destfile, 'wb') as f:
        f.write(rawData)
    except IOError as e:
      print str(e)
      return False
    return True


  def _make_payload(self):
    """ Make request payload object """
    return Payload(
        text=self.text,
        language=self.language
        )


  def _make_files(self):
    """ Create array of file object(s) """
    return []
