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


## @file RappCloud.py
#
#  @copyright Rapp Project EU 2015
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#

from RappCloud.CloudMsgs import FaceDetection
from RappCloud.CloudMsgs import QrDetection
from RappCloud.CloudMsgs import HumanDetection
from RappCloud.CloudMsgs import HazardDetectionDoor
from RappCloud.CloudMsgs import HazardDetectionLight
from RappCloud.CloudMsgs import ObjectRecognitionCaffe
from RappCloud.CloudMsgs import SetNoiseProfile
from RappCloud.CloudMsgs import SpeechRecognitionSphinx
from RappCloud.CloudMsgs import SpeechRecognitionGoogle
from RappCloud.CloudMsgs import OntologySubclasses
from RappCloud.CloudMsgs import OntologySuperclasses
from RappCloud.CloudMsgs import OntologyIsSubsuperclass
from RappCloud.CloudMsgs import CognitiveExerciseSelect
from RappCloud.CloudMsgs import CognitiveGetHistory
from RappCloud.CloudMsgs import CognitiveGetScores
from RappCloud.CloudMsgs import CognitiveRecordPerformance
from RappCloud.CloudMsgs import EmailFetch
from RappCloud.CloudMsgs import EmailSend
from RappCloud.CloudMsgs import WeatherReportCurrent
from RappCloud.CloudMsgs import WeatherReportForecast
from RappCloud.CloudMsgs import PathPlanningPlan2D
from RappCloud.CloudMsgs import PathPlanningUploadMap
from RappCloud.CloudMsgs import TextToSpeech
from RappCloud.CloudMsgs import NewsExplore
from RappCloud.CloudMsgs import Geolocation

from RappCloud import RappPlatformService

class RappPlatformAPI():
    def __init__(self):
        self.svc_caller = RappPlatformService()

    def faceDetection(self, imageFilepath, fast):
        msg = FaceDetection()
        msg.req.imageFilepath = imageFilepath
        response = self.svc_caller.call(msg)
        return [response.faces, response.error]
