#!/usr/bin/env python


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

# Authors: Konstantinos Panayiotou
# contact: klpanagi@gmail.com


## @file RappCloud/CloudServices/Service.py
#
#  @copyright Rapp Projecty EU 2015
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#

from Service import *
from RappCloud.Objects import File


class FaceDetection(Service):
    def __init__(self, **kwargs):
        # Cloud Service requst arguments
        self.fast = bool()
        self.imageFile = str()
        ###############################

        # Call to set kwargs as class attributes
        super(FaceDetection, self).__init__(**kwargs)
        self.set_service_name('face_detection')


    def _make_payload(self):
        self._reqPayload = {
          'fast': self.fast
        }


    def _make_files(self):
        _file = File(self.imageFile, 'file')
        self._reqFiles = [_file.serialize()]



## TEST!! Move to IntegrationTests
#if __name__ == "__main__":
#  face = FaceDetection(fast=False, imageFile="/home/klpanagi/rapp_platform/rapp-platform-catkin-ws/src/rapp-platform/rapp_testing_tools/test_data/face_samples/etsardou_medium.jpg")
#  resp = face.call()
#  print resp.faces
