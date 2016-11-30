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


## @file RappCloud/RappPlatformApi.py
#
#  @copyright Rapp Project EU 2015
#  @author Konstantinos Panayiotou, Manos Tsardoulias
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
from CloudMsgs import ObjectDetectionFindObjects
from CloudMsgs import ObjectDetectionClearModels
from CloudMsgs import ObjectDetectionLoadModels
from CloudMsgs import ObjectDetectionLearnObject
from CloudMsgs import VisualLocalization
from CloudMsgs import VisualLocalizationInit
from CloudMsgs import UserPersonalInfo

from Service import RappPlatformService


class RappPlatformAPI():
    """ RAPP Platform simple API implementation """
    def __init__(self, *args, **kwargs):
        self.svc_caller = RappPlatformService(*args, **kwargs)

    def faceDetection(self, imageFilepath, fast=False):
        """! Face detection API service call.

        @type imageFilepath: string
        @param imageFilepath: Path to the image file.

        @type fast: bool
        @param fast: Perform fast detection. If true, detection will take
            less time but it will be less accurate.

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'faces': [], 'error': ''}
        """
        msg = FaceDetection()
        try:
            msg.req.imageFilepath = imageFilepath
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = FaceDetection.Response(error=str(e))
        return {
            'faces': response.faces,
            'error': response.error
        }

    def qrDetection(self, imageFilepath):
        """! QR code detection API service call.

        @type imageFilepath: string
        @param imageFilepath: Path to the image file.

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'qr_centers': [], 'qr_messages': [], 'error': ''}
        """
        msg = QrDetection()
        try:
            msg.req.imageFilepath = imageFilepath
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = QrDetection.Response(error=str(e))
        return {
            'qr_centers': response.qr_centers,
            'qr_messages': response.qr_messages,
            'error': response.error
        }

    def humanDetection(self, imageFilepath):
        """! Human detection API service call.

        @type imageFilepath: string
        @param imageFilepath: Path to the image file.

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'humans': [], 'error': ''}
        """

        msg = HumanDetection()
        try:
            msg.req.imageFilepath = imageFilepath
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = HumanDetection.Response(error=str(e))
        return {
            'humans': response.humans,
            'error': response.error
        }

    def hazardDetectionDoor(self, imageFilepath):
        """! Hazard detection door check API service call.

        @type imageFilepath: string
        @param imageFilepath: Path to the image file.

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'door_angle': 0.0, 'error': ''}
        """
        msg = HazardDetectionDoor()
        try:
            msg.req.imageFilepath = imageFilepath
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = HazardDetectionDoor.Response(error=str(e))
        return {
            'door_angle': response.door_angle,
            'error': response.error
        }

    def hazardDetectionLights(self, imageFilepath):
        """! Hazard detection light check API service call.

        @type imageFilepath: string
        @param imageFilepath: Path to the image file.

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'light_level': 0, 'error': ''}
        """
        msg = HazardDetectionLight()
        try:
            msg.req.imageFilepath = imageFilepath
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = HazardDetectionLight.Response(error=str(e))
        return {
            'light_level': response.light_level,
            'error': response.error
        }

    def objectRecognitionCaffe(self, imageFilepath):
        """! Object Recognition Caffe API service call.

        @type imageFilepath: string
        @param imageFilepath: Path to the image file.

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'object_class': '', 'error': ''}
        """
        msg = ObjectRecognitionCaffe()
        try:
            msg.req.imageFilepath = imageFilepath
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = ObjectRecognitionCaffe.Response(error=str(e))
        return {
            'object_class': response.object_class,
            'error': response.error
        }

    def setNoiseProfile(self, audiofile, audio_source):
        """! Set Noise Profile API service call.

        @type audiofile: string
        @param audiofile: Path to the audio file.

        @type audio_source: string
        @param audio_source: Audio source format. e.g. 'nao_wav_1_ch'

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'error': ''}
        """
        msg = SetNoiseProfile()
        try:
            msg.req.audiofile = audiofile
            msg.req.audio_source = audio_source
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = SetNoiseProfile.Response(error=str(e))
        return {
            'error': response.error
        }

    def speechRecognitionSphinx(self, audiofile, audio_source, language, words,
                                sentences=[], grammar=[]):
        """! Speech recognition Sphinx API service call.

        @type audiofile: string
        @param audiofile: Path to the audio file.

        @type audio_source: string
        @param audio_source: Audio source format. e.g. 'nao_wav_1_ch'

        @type language: string
        @param language: Language to use for speech recognition.

        @type words: list
        @param words: To recognize words.

        @type sentences: list
        @param sentences: Under consideration sentences. Same as
            @ref words by default.

        @type grammar: list
        @param grammar: Grammar to use. Defaults to none.

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'words': [], 'error': ''}
        """
        msg = SpeechRecognitionSphinx()
        try:
            msg.req.audiofile = audiofile
            msg.req.audio_source = audio_source
            msg.req.language = language
            msg.req.words = words
            msg.req.sentences = sentences
            if sentences == []:
                msg.req.sentences = words
            msg.req.grammar = grammar
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = SpeechRecognitionSphinx.Response(error=str(e))
        return {
            'words': response.words,
            'error': response.error
        }

    def speechRecognitionGoogle(self, audiofile, audio_source, language):
        """! Speech recognition Google API service call.

        @type audiofile: string
        @param audiofile: Path to the audio file.

        @type audio_source: string
        @param audio_source: Audio source format. e.g. 'nao_wav_1_ch'

        @type language: string
        @param language: Language to use for speech recognition.

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'words': [], 'alternatives': [], 'error': ''}
        """
        msg = SpeechRecognitionGoogle()
        try:
            msg.req.audiofile = audiofile
            msg.req.audio_source = audio_source
            msg.req.language = language
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = SpeechRecognitionGoogle.Response(error=str(e))
        return {
            'words': response.words,
            'alternatives': response.alternatives,
            'error': response.error
        }

    def ontologySubclasses(self, ontology_class, recursive=False):
        """! Ontology subclasses-of API service call.

        @type ontology_class: string
        @param ontology_class: The ontology class.

        @type recursive: bool
        @param recursive: Recursive search. Defaults to False.

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'results': [], 'error': ''}
        """
        msg = OntologySubclasses()
        try:
            msg.req.ontology_class = ontology_class
            msg.req.recursive = recursive
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = OntologySubclasses.Response(error=str(e))
        return {
            'results': response.results,
            'error': response.error
        }

    def ontologySuperclasses(self, ontology_class, recursive=False):
        """! Ontology superclasses-of API service call.

        @type ontology_class: string
        @param ontology_class: The ontology class.

        @type recursive: bool
        @param recursive: Recursive search. Defaults to False.

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'results': [], 'error': ''}
        """
        msg = OntologySuperclasses()
        try:
            msg.req.ontology_class = ontology_class
            msg.req.recursive = recursive
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = OntologySuperclasses.Response(error=str(e))
        return {
            'results': response.results,
            'error': response.error
        }

    def ontologyIsSubsuperclass(self, parent_class, child_class,
                                recursive=False):
        """! Ontology is-supsuperclass-of API service call.

        @type parent_class: string
        @param parent_class: The ontology parent class name.

        @type child_class: string
        @param child_class: The ontology child class name.

        @type recursive: bool
        @param recursive: Recursive search. Defaults to False.

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'result': False, 'error': ''}
        """
        msg = OntologyIsSubsuperclass()
        try:
            msg.req.parent_class = parent_class
            msg.req.child_class = child_class
            msg.req.recursive = recursive
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = OntologyIsSubsuperclass.Response(error=str(e))
        return {
            'result': response.result,
            'error': response.error
        }

    def cognitiveExerciseSelect(self, test_type='', test_subtype='',
                                test_diff=-1, test_index=-1):
        """! Cognitive Exercise selection (chooser) API service call.

        @type test_type: string
        @param test_type: Cognitive Exercise test type. Defaults to empty.

        @type test_subtype: string
        @param test_subtype: Force exercise selection from this subtype.
            Defaults to empty.

        @type test_diff: int
        @param test_diff: Force exercise selection from this difficulty.
            Defaults to empty.

        @type test_index: int
        @param test_diff: Force exercise selection from this difficulty.
            Defaults to empty.

        @rtype: dict
        @return: Returns a dictionary of the service call response.
        """
        msg = CognitiveExerciseSelect()
        try:
            msg.req.test_type = test_type
            msg.req.test_subtype = test_subtype
            if test_diff != -1:
                msg.req.test_diff = test_diff
            if test_index != -1:
                msg.req.test_index = test_index
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = CognitiveExerciseSelect.Response(error=str(e))
        return {
            'test_type': response.test_type,
            'test_subtype': response.test_subtype,
            'test_instance': response.test_instance,
            'questions': response.questions,
            'possib_ans': response.possib_ans,
            'correct_ans': response.correct_ans,
            'lang': response.lang,
            'error': response.error
        }

    def cognitiveGetHistory(self, test_type='', time_from=0, time_to=0):
        """! Gognitive get history records API service call.

        @type test_type: string
        @param test_type: Cognitive Exercise test type. Defaults to empty.

        @type time_from: int
        @param time_from: Retrieve history records from this timestamp value.
            Unix timestamp. Defaults to zero (0).

        @type time_to: int
        @param time_from: Retrieve history records up to this timestamp value.
            Unix timestamp. Defaults to zero (0).

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'records': {}, 'error': ''}
        """
        msg = CognitiveGetHistory()
        try:
            msg.req.test_type = test_type
            msg.req.time_from = time_from
            msg.req.time_to = time_to
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = CognitiveGetHistory.Response(error=str(e))
        return {
            'records': response.records,
            'error': response.error
        }

    def cognitiveGetScores(self, test_type='', time_to=0):
        """! Gognitive get score records API service call.

        @type test_type: string
        @param test_type: Cognitive Exercise test type. Defaults to empty.

        @type time_to: int
        @param time_from: Retrieve score records up to this timestamp value.
            Unix timestamp. Defaults to zero (0).

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'test_classes': [], 'scores': [], 'error': ''}
        """
        msg = CognitiveGetScores()
        try:
            msg.req.test_type = test_type
            msg.req.time_to = time_to
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = CognitiveGetScores.Response(error=str(e))
        return {
            'test_classes': response.test_classes,
            'scores': response.scores,
            'error': response.error
        }

    def cognitiveRecordPerformance(self, test_instance, score):
        """! Gognitive record performance of an exercise API service call.

        @type test_instance: string
        @param test_instance: Performed cognitive exercise test instance.
            The full cognitive test entry name as obtained from
            CognitiveExerciseSelect API service call

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'performance_entry': '', 'error': ''}
        """
        msg = CognitiveRecordPerformance()
        try:
            msg.req.test_instance = test_instance
            msg.req.score = score
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = CognitiveRecordPerformance.Response(error=str(e))
        return {
            'performance_entry': response.performance_entry,
            'error': response.error
        }

    def emailFetch(self, email, password, server, port, date_from, date_to,
                   email_status='UNSEEN', num_emails=1):
        """! Email fetch API service call.

        @type email: string
        @param email: User's email username

        @type password: string
        @param password: User's email password

        @type server: string
        @param server: The email provider imap address.

        @type port: string
        @param port: The email provider imap port.

        @type date_from: int
        @param date_from: Fetch emails since this timestamp value.
            Unix timestamp.

        @type date_to: int
        @param date_to: Fetch emails up to this timestamp value.
            Unix timestamp.

        @type email_status: string
        @param email_status: Email status (ALL, UNSEEN). Defaults to 'UNSEEN'

        @type num_emails: int
        @param num_emails: Maximum number of emails to fetch.

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'emails': [], 'error': ''}
        """
        msg = EmailFetch()
        try:
            msg.req.email = email
            msg.req.password = password
            msg.req.server = server
            msg.req.port = port
            msg.req.date_from = date_from
            msg.req.date_to = date_to
            msg.req.email_status = email_status
            msg.req.num_emails = num_emails
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = EmailFetch.Response(error=str(e))
        return {
            'emails': response.emails,
            'error': response.error
        }

    def emailSend(self, email, password, server, port, recipients, body,
                  subject, attach_file=''):
        """! Email fetch API service call.

        @type email: string
        @param email: User's email username

        @type password: string
        @param password: User's email password

        @type server: string
        @param server: The email provider imap address.

        @type port: string
        @param port: The email provider imap port.

        @type recipients: list
        @param recipients: List of recipients email addresses.

        @type body: string
        @param body: The body of the email.

        @type subject: string
        @param subject: The email subject.

        @type attach_file: string
        @param attach_file: Attachment file (path). Attachment file can be a
            .zip file containing multiple attachment files.

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'error': ''}
        """
        msg = EmailSend()
        try:
            msg.req.email = email
            msg.req.password = password
            msg.req.server = server
            msg.req.port = port
            msg.req.recipients = recipients
            msg.req.body = body
            msg.req.subject = subject
            msg.req.attach_file = attach_file
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = EmailSend.Response(error=str(e))
        return {
            'error': response.error
        }

    def weatherReportCurrent(self, city, weather_reporter='forecastio',
                             metric=0):
        """! Weather report current API service call

        @type city: string
        @param city: City location.

        @type weather_reporter: string
        @param weather_reporter: The weather reporter API to use.
            Defaults to 'forecast.io'

        @type metric: int
        @param metric: Value units (0:Celcius, 1:Fahrenheit)
            Defaults to 0 (Celcius)

        @rtype: dict
        @return: Returns a dictionary of the service call response.
        """
        msg = WeatherReportCurrent()
        try:
            msg.req.city = city
            msg.req.weather_reporter = weather_reporter
            msg.req.metric = metric
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = WeatherReportCurrent.Response(error=str(e))
        return {
            'date': response.date,
            'temperature': response.temperature,
            'weather_description': response.weather_description,
            'humidity': response.humidity,
            'visibility': response.visibility,
            'pressure': response.pressure,
            'wind_speed': response.wind_speed,
            'wind_temperature': response.wind_temperature,
            'wind_direction': response.wind_direction,
            'error': response.error
        }

    def weatherReportForecast(self, city, weather_reporter='forecastio',
                              metric=0):
        """! Weather report forecast API service call

        @type city: string
        @param city: City location.

        @type weather_reporter: string
        @param weather_reporter: The weather reporter API to use.
            Defaults to 'forecast.io'

        @type metric: int
        @param metric: Value units (0:Celcius, 1:Fahrenheit)
            Defaults to 0 (Celcius)

        @rtype: dict
        @return: Returns a dictionary of the service call response.
        """
        msg = WeatherReportForecast()
        try:
            msg.req.city = city
            msg.req.weather_reporter = weather_reporter
            msg.req.metric = metric
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = WeatherReportForecast.Response(error=str(e))
        return {
            'forecast': response.forecast,
            'error': response.error
        }

    def pathPlanningPlan2D(self, map_name, robot_type, pose_start,
                           pose_goal, algorithm='dijkstra'):
        """! Path planning plan path 2D API service call

        @type map_name: string
        @param map_name: The map name.

        @type robot_type: string
        @param robot_type: The robot type. e.g 'NAO'

        @type pose_start: dict
        @param pose_start: Start pose of the robot.

        @type pose_goal: dict
        @param pose_goal: Goal pose of the robot.

        @type algorithm: string
        @param algorithm: Path planning algorithm to apply.
            Defaults to 'dijkstra'

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'plan_found': 0, 'path': [], 'error': ''}
        """

        msg = PathPlanningPlan2D()
        try:
            msg.req.map_name = map_name
            msg.req.robot_type = robot_type
            msg.req.algorithm = algorithm
            msg.req.pose_start = pose_start
            msg.req.pose_goal = pose_goal
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = PathPlanningPlan2D.Response(error=str(e))
        return {
            'plan_found': response.plan_found,
            'path': response.path,
            'error': response.error
        }

    def pathPlanningUploadMap(self, map_name, png_file, yaml_file):
        """! Path planning upload map API service call

        @type map_name: string
        @param map_name: The map name

        @type png_file: string
        @param png_file: Path to the map png file

        @type yaml_file: string
        @param yaml_file: Path to the map descriptor yaml file.

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'error': ''}
        """
        msg = PathPlanningUploadMap()
        try:
            msg.req.map_name = map_name
            msg.req.png_file = png_file
            msg.req.yaml_file = yaml_file
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = PathPlanningUploadMap.Response(error=str(e))
        return {
            'error': response.error
        }

    def textToSpeech(self, text, language, audio_file):
        """! Text to Speech API service call

        @type text: string
        @param text: Input text to translate to audio.

        @type language: string
        @param language: Text language.

        @type audio_file: string
        @param audio_file: File path to store the audio data.

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'error': ''}
        """
        msg = TextToSpeech()
        try:
            msg.req.text = text
            msg.req.language = language
            response = self.svc_caller.call(msg)

            if response.error == u"":
                response.store_audio(audio_file)
        except Exception as e:
            response = TextToSpeech.Response(error=str(e))
        return {
            'error': response.error
        }

    def newsExplore(self, keywords, region='', topic='', news_engine='',
                    num_news=1, exclude_titles=[]):
        """! News Explorer API service call

        @type keywords: list
        @param keywords: Desired keywords.

        @type region: string
        @param region: language/region

        @type topic: string
        @param topic: Main topic. e.g. 'sports', 'politics', etc

        @type news_engine: string
        @param news_engine: The news search engine to use. Optional

        @type num_news: string
        @param num_news: Number of news stories to request.

        @type exclude_titles: list
        @param exclude_titles: Exclude these titles

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'news_stories': [], 'error': ''}
        """
        msg = NewsExplore()
        try:
            msg.req.news_engine = news_engine
            msg.req.keywords = keywords
            msg.req.exclude_titles = exclude_titles
            msg.req.region = region
            msg.req.topic = topic
            msg.req.num_news = num_news
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = NewsExplore.Response(error=str(e))
        return {
            'news_stories': response.news_stories,
            'error': response.error
        }

    def geolocation(self, ipaddr, engine='ip-api'):
        """! Geolocation API service call

        @type ipaddr: string
        @param ipaddr: The machine's ipv4 address.

        @type engine: string
        @param engine: Engine to use. Defaults to 'ip-api'.

        @rtype: dict
        @return: Returns a dictionary of the service call response.
        """
        msg = Geolocation()
        try:
            msg.req.ipaddr = ipaddr
            msg.req.engine = engine
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = Geolocation.Response(error=str(e))
        return {
            'city': response.city,
            'country': response.country,
            'country_code': response.country_code,
            'latitude': response.latitude,
            'longtitude': response.longtitude,
            'region': response.region,
            'timezone': response.timezone,
            'zip': response.zip,
            'error': response.error
        }

    def objectDetectionFindObjects(self, fname, limit=1):
        """! Object detection API service call.

        @type fname: string
        @param fname: Path to the image file.

        @type limit: int
        @param limit: Limit results to this number of objects

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {
               'found_names': [], 'found_centers': [],
               'found_scores': [], 'result': 0, 'error': ''
            }
        """
        msg = ObjectDetectionFindObjects()
        try:
            msg.req.fname = fname
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = ObjectDetectionFindObjects.Response(error=str(e))
        return {
            'found_names': response.found_names,
            'found_centers': response.found_centers,
            'found_scores': response.found_scores,
            'result': response.result,
            'error': response.error
        }

    def objectDetectionClearModels(self):
        """! Object detection - clear models API service call.

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'result': 0, 'error': ''}
        """
        msg = ObjectDetectionClearModels()
        try:
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = ObjectDetectionClearModels.Response(error=str(e))
        return {
            'result': response.result,
            'error': response.error
        }

    def objectDetectionLoadModels(self, names=[]):
        """! Object detection - load models API service call.

        @type names: list
        @param names: Model names to load

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'result': 0, 'error': ''}
        """
        msg = ObjectDetectionLoadModels()
        try:
            msg.req.names = names
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = ObjectDetectionLoadModels.Response(error=str(e))
        return {
            'result': response.result,
            'error': response.error
        }

    def objectDetectionLearnObject(self, fname, name=''):
        """! Object detection - load models API service call.

        @type fname: string
        @param fname: Path to the image file.

        @type name: string
        @param name: Model name

        @rtype: dict
        @return: Returns a dictionary of the service call response.
            {'result': 0, 'error': ''}
        """
        msg = ObjectDetectionLearnObject()
        try:
            msg.req.fname = fname
            msg.req.name = name
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = ObjectDetectionLearnObject.Response(error=str(e))
        return {
            'result': response.result,
            'error': response.error
        }

    def visualLocalizationInit(self, mapname):
        msg = VisualLocalizationInit()
        try:
            print("visualLocalizationInit")
            msg.req.map = mapname
            response = self.svc_caller.call(msg)
        except Exception as e:
            print("Exc: ", str(e))
            response = VisualLocalizationInit.Response(error=str(e))
        return {
            'id': response.id,
            'error': response.error
        }

    def visualLocalization(self, fname, pose_delta, client_id):
        msg = VisualLocalization()
        try:
            msg.req.fname = fname
            msg.req.pose_delta = pose_delta
            msg.id = client_id
            response = self.svc_caller.call(msg)
        except Exception as e:
            response = VisualLocalization.Response(error=str(e))
        return {
            'belief': response.belief,
            'best_pose': response.best_pose,
            'status': response.status,
            'error': response.error
        }

    def userPersonalInfo(self):
        """! Fetch User's personal info from Platform DB call

        @rtype: dict
        @return: Returns a dictionary of the service call response.
        """

        msg = UserPersonalInfo()
        response = self.svc_caller.call(msg)
        return response.serialize()
