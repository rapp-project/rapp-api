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

from CloudMsgs import FaceDetection
from CloudMsgs import QrDetection
from CloudMsgs import HumanDetection
from CloudMsgs import HazardDetectionDoor
from CloudMsgs import HazardDetectionLight
from CloudMsgs import ObjectRecognitionCaffe
from CloudMsgs import SetNoiseProfile
from CloudMsgs import SpeechRecognitionSphinx
from CloudMsgs import SpeechRecognitionGoogle
from CloudMsgs import OntologySubclasses
from CloudMsgs import OntologySuperclasses
from CloudMsgs import OntologyIsSubsuperclass
from CloudMsgs import CognitiveExerciseSelect
from CloudMsgs import CognitiveGetHistory
from CloudMsgs import CognitiveGetScores
from CloudMsgs import CognitiveRecordPerformance
from CloudMsgs import EmailFetch
from CloudMsgs import EmailSend
from CloudMsgs import WeatherReportCurrent
from CloudMsgs import WeatherReportForecast
from CloudMsgs import PathPlanningPlan2D
from CloudMsgs import PathPlanningUploadMap
from CloudMsgs import TextToSpeech
from CloudMsgs import NewsExplore
from CloudMsgs import Geolocation

from Service import RappPlatformService

class RappPlatformAPI():
    def __init__(self):
        self.svc_caller = RappPlatformService()

    def faceDetection(self, imageFilepath, fast = False):
        msg = FaceDetection()
        msg.req.imageFilepath = imageFilepath
        response = self.svc_caller.call(msg)
        return {\
                'faces': response.faces,\
                'error': response.error\
                }

    def qrDetection(self, imageFilepath):
        msg = QrDetection()
        msg.req.imageFilepath = imageFilepath
        response = self.svc_caller.call(msg)
        return {\
                'qr_centers': response.qr_centers,\
                'qr_messages': response.qr_messages,\
                'error': response.error\
                }

    def humanDetection(self, imageFilepath):
        msg = HumanDetection()
        msg.req.imageFilepath = imageFilepath
        response = self.svc_caller.call(msg)
        return {\
                'humans': response.humans,\
                'error': response.error\
                }

    def hazardDetectionDoor(self, imageFilepath):
        msg = HazardDetectionDoor()
        msg.req.imageFilepath = imageFilepath
        response = self.svc_caller.call(msg)
        return {\
                'door_angle': response.door_angle,\
                'error': response.error\
                }

    def hazardDetectionLights(self, imageFilepath):
        msg = HazardDetectionLight()
        msg.req.imageFilepath = imageFilepath
        response = self.svc_caller.call(msg)
        return {\
                'light_level': response.light_level,\
                'error': response.error\
                }

    def objectRecognitionCaffe(self, imageFilepath):
        msg = ObjectRecognitionCaffe()
        msg.req.imageFilepath = imageFilepath
        response = self.svc_caller.call(msg)
        return {\
                'object_class': response.object_class,\
                'error': response.error\
                }

    def setNoiseProfile(self, audiofile, audio_source):
        msg = SetNoiseProfile()
        msg.req.audiofile = audiofile
        msg.req.audio_source = audio_source
        response = self.svc_caller.call(msg)
        return {\
                'error': response.error\
                }

    def speechRecognitionSphinx(self, audiofile, audio_source, language, words, \
            sentences = [], grammar = []):
        msg = SpeechRecognitionSphinx()
        msg.req.audiofile = audiofile
        msg.req.audio_source = audio_source
        msg.req.language = language
        msg.req.words = words
        msg.req.sentences = sentences
        if sentences == []:
            msg.req.sentences = words
        msg.req.grammar = grammar
        response = self.svc_caller.call(msg)
        return {\
                'words': response.words,\
                'error': response.error\
                }

    def speechRecognitionGoogle(self, audiofile, audio_source, language):
        msg = SpeechRecognitionGoogle()
        msg.req.audiofile = audiofile
        msg.req.audio_source = audio_source
        msg.req.language = language
        response = self.svc_caller.call(msg)
        return {\
                'words': response.words,\
                'alternatives': response.alternatives,\
                'error': response.error\
                }

    def ontologySubclasses(self, ontology_class, recursive = False):
        msg = OntologySubclasses()
        msg.req.ontology_class = ontology_class
        msg.req.recursive = recursive
        response = self.svc_caller.call(msg)
        return {\
                'results': response.results,\
                'error': response.error\
                }

    def ontologySuperclasses(self, ontology_class, recursive = False):
        msg = OntologySuperclasses()
        msg.req.ontology_class = ontology_class
        msg.req.recursive = recursive
        response = self.svc_caller.call(msg)
        return {\
                'results': response.results,\
                'error': response.error\
                }

    def ontologyIsSubsuperclass(self, parent_class, child_class, recursive = False):
        msg = OntologyIsSubsuperclass()
        msg.req.parent_class = parent_class
        msg.req.child_class = child_class
        msg.req.recursive = recursive
        response = self.svc_caller.call(msg)
        return {\
                'result': response.result,\
                'error': response.error\
                }

    def cognitiveExerciseSelect(self, test_type = '', test_subtype = '', test_diff = -1, test_index = -1):
        msg = CognitiveExerciseSelect()
        if test_type != '':
            msg.req.test_type = test_type
        if test_subtype != '':
            msg.req.test_subtype = test_subtype
        if test_diff != -1:
            msg.req.test_diff = test_diff
        if test_index != -1:
            msg.req.test_index = test_index
        response = self.svc_caller.call(msg)
        return {\
                'test_type': response.test_type,\
                'test_subtype': response.test_subtype,\
                'test_instance': response.test_instance,\
                'questions': response.questions,\
                'possib_ans': response.possib_ans,\
                'correct_ans': response.correct_ans,\
                'error': response.error\
                }

    def cognitiveGetHistory(self, test_type = '', time_from = -1, time_to = -1):
        msg = CognitiveGetHistory()
        if test_type != '':
            msg.req.test_type = test_type
        if time_from != -1:
            msg.req.time_from = time_from
        if time_to != -1:
            msg.req.time_to = time_to
        response = self.svc_caller.call(msg)
        return {\
                'records': response.records,\
                'error': response.error\
                }

    def cognitiveGetScores(self, test_type = '' , time_to = -1):
        msg = CognitiveGetScores()
        msg.req.test_type = test_type
        msg.req.time_to = time_to
        response = self.svc_caller.call(msg)
        return {\
                'test_classes': response.test_classes,\
                'scores': response.scores,\
                'error': response.error\
                }

    def cognitiveRecordPerformance(self, test_instance, score):
        msg = CognitiveRecordPerformance()
        msg.req.test_instance = test_instance
        msg.req.score = score
        response = self.svc_caller.call(msg)
        return {\
                'performance_entry': response.performance_entry,\
                'error': response.error\
                }

    def emailFetch(self, email, password, server, port, date_from, date_to,\
            email_status, num_emails):
        msg = EmailFetch()
        msg.req.email = email
        msg.req.password = password
        msg.req.server = server
        msg.req.port = port
        msg.req.date_from = date_from
        msg.req.date_to = date_to
        msg.req.email_status = email_status
        msg.req.num_emails = num_emails
        response = self.svc_caller.call(msg)
        return {\
                'emails': response.emails,\
                'error': response.error\
                }

    def emailSend(self, email, password, server, port, recipients, body,\
            subject, attach_file):
        msg = EmailSend()
        msg.req.email = email
        msg.req.password = password
        msg.req.server = server
        msg.req.port = port
        msg.req.recipients = recipients
        msg.req.body = body
        msg.req.subject = subject
        msg.req.attach_file = attach_file
        response = self.svc_caller.call(msg)
        return {\
                'error': response.error\
                }

    def weatherReportCurrent(self, city, weather_reporter, metric):
        msg = WeatherReportCurrent()
        msg.req.city = city
        msg.req.weather_reporter = weather_reporter
        msg.req.metric = metric
        response = self.svc_caller.call(msg)
        return {\
                'date': response.date,\
                'temperature': response.temperature,\
                'weather_description': response.weather_description,\
                'humidity': response.humidity,\
                'visibility': response.visibility,\
                'pressure': response.pressure,\
                'wind_speed': response.wind_speed,\
                'wind_temperature': response.wind_temperature,\
                'wind_direction': response.wind_direction,\
                'error': response.error\
                }

    def weatherReportForecast(self, city, weather_reporter, metric):
        msg = WeatherReportForecast()
        msg.req.city = city
        msg.req.weather_reporter = weather_reporter
        msg.req.metric = metric
        response = self.svc_caller.call(msg)
        return {\
                'forecast': response.forecast,\
                'error': response.error\
                }

    def pathPlanningPlan2D(self, map_name, robot_type, algorithm, pose_start, \
            pose_goal):
        msg = PathPlanningPlan2D()
        msg.req.map_name = map_name
        msg.req.robot_type = robot_type
        msg.req.algorithm = algorithm
        msg.req.pose_start = pose_start
        msg.req.pose_goal = pose_goal
        response = self.svc_caller.call(msg)
        return {\
                'plan_found': response.plan_found,\
                'path': response.path,\
                'error': response.error\
                }

    def pathPlanningUploadMap(self, map_name, png_file, yaml_file):
        msg = PathPlanningUploadMap()
        msg.req.map_name = map_name
        msg.req.png_file = png_file
        msg.req.yaml_file = yaml_file
        response = self.svc_caller.call(msg)
        return {\
                'error': response.error\
                }

    def textToSpeech(self, text, language, audio_file):
        msg = TextToSpeech()
        msg.req.text = text
        msg.req.language = language
        response = self.svc_caller.call(msg)

        if response.error is "":
            response.store_audio(audio_file)

        return {\
                'encoding': response.encoding,\
                'basename': response.basename,\
                'error': response.error\
                }

    def newsExplore(self, news_engine, keywords, exclude_titles, region, \
            topic, num_news):
        msg = NewsExplore()
        msg.req.news_engine = news_engine
        msg.req.keywords = keywords
        msg.req.exclude_titles = exclude_titles
        msg.req.region = region
        msg.req.topic = topic
        msg.req.num_news = num_news
        response = self.svc_caller.call(msg)
        return {\
                'news_stories': response.news_stories,\
                'error': response.error\
                }

    def geolocation(self, ipaddr, engine):
        msg = Geolocation()
        msg.req.ipaddr = ipaddr
        msg.req.engine = engine
        response = self.svc_caller.call(msg)
        return {\
                'city': response.city,\
                'country': response.country,\
                'country_code': response.country_code,\
                'latitude': response.latitude,\
                'longtitude': response.longtitude,\
                'region': response.region,\
                'timezone': response.timezone,\
                'zip': response.zip,\
                'error': response.error\
                }
