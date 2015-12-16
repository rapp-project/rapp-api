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


## @file RappCloud/RappCloud.py
#
#  @copyright Rapp Projecty EU 2015
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#

import json
import os
import sys
from CloudInterface import CloudInterface
from RandStrGen import RandStrGen
from ConfigParser import SafeConfigParser
import yaml
import base64
#import magic

__path__ = os.path.dirname(__file__)


## @class RappCloud
#
#  Rapp Platform API class. API calls for Platform HOP Web Services.
#
class RappCloud:

    ##  Default constructor.
    def __init__(self):
        # --- Load Rapp Platform parameters --- #
        self.cfgFileDir_ = os.path.join(__path__, 'config')
        self.cfgParser_ = SafeConfigParser()
        self.platform_params_ = None
        self.platformIP_ = ''
        self.servicePort_ = ''
        self.services_ = []
        self.serviceUrl_ = {}
        self.auth_ = {}
        self.__parse_platform_cfg()
        self.__parse_services_cfg()
        self.__parse_auth_cfg()
        self.__randStrSize = 5


    ## Parse and load Rapp Platform authentication parameters.
    #
    #  @param self The object pointer.
    #
    def __parse_auth_cfg(self):
        cfgFilePath = os.path.join(self.cfgFileDir_, 'auth.cfg')
        section = 'Auth'
        try:
            self.cfgParser_.read(cfgFilePath)
        except Exception as e:
            print "Could not load user authentication parameters from file [%s]" \
                % cfgFilePath
            print e
            sys.exit(1)
        if not self.cfgParser_.has_section(section):
            print "\033[0mCfg file {%s} is missing section [%s]\033[0m" \
                % (cfgFilePath, section)
            sys.exit(1)

        if self.cfgParser_.has_option(section, 'username'):
            self.auth_['username'] = self.cfgParser_.get(section, 'username')
        else:
            print "Cfg file [%s] is missing option <username>"
            sys.exit(1)

        if self.cfgParser_.has_option(section, 'password'):
            self.auth_['password'] = self.cfgParser_.get(section, 'password')
        else:
            print "Cfg file [%s] is missing option <password>"
            sys.exit(1)


    ## Parse and load Rapp Platform Web Services info.
    #
    #  @param self The object pointer.
    #
    def __parse_services_cfg(self):
        cfgFilePath = os.path.join(self.cfgFileDir_, 'services.yaml')
        srvList = []
        with open(cfgFilePath, 'r') as ymlfile:
            cfg = yaml.safe_load(ymlfile)

        if 'services' in cfg:
            services = cfg['services']
            if 'list' in services:
                srvList = services['list']

        for service in srvList:
            self.services_.append(service)
            self.serviceUrl_[service] = 'http://' + self.platformIP_ + \
                ':' + str(self.servicePort_) + '/hop/' + service


    ## Parse and load Rapp Platform parameters.
    #
    #  @param self The object pointer.
    #
    def __parse_platform_cfg(self):
        cfgFilePath = os.path.join(self.cfgFileDir_, 'platform.cfg')
        section = 'RAPP Platform'
        ## Catch exceptions on loading configuration file ##
        ## TODO Enhance Exception handling
        try:
            self.cfgParser_.read(cfgFilePath)
        except Exception as e:
            print "Could not load RAPP Platform parameters from .cfg file."
            print e
            sys.exit(1)
        if not self.cfgParser_.has_section(section):
            print "\033[0mCfg file {%s} is missing section [%s]\033[0m" \
                % (cfgFilePath, section)
            sys.exit(1)

        if self.cfgParser_.has_option(section, 'use'):
            useSection = self.cfgParser_.get(section, 'use')
        else:
            print "Missing option under [RAPP Platform] section" + \
                " in cfg file {%s}" % cfgFilePath
            sys.exit(1)

        if not self.cfgParser_.has_section(useSection):
            print "Given value for option <use> in [RAPP Platform] Section" + \
                " does not correspond to a defined Section in cfg file"
            sys.exit(1)

        if self.cfgParser_.has_option(useSection, 'ipv4_addr') and \
                self.cfgParser_.has_option(useSection, 'port'):
            self.platformIP_ = self.cfgParser_.get(useSection, 'ipv4_addr')
            self.servicePort_ = self.cfgParser_.get(useSection, 'port')
        else:
            print "Missing options {ipv4_addr} and {port} in cfg file [%s]" \
                % cfgFilePath
            sys.exit(1)


    ## Append a random string as a postFix to the input filePath.
    #
    #  @param self The object pointer.
    #  @param filePath File's system path to append the random postfix string.
    #
    #  @return The new file name.
    #
    def __appendRandStr(self, filePath):
        randStr = RandStrGen.create(self.__randStrSize)
        splStr = filePath.split('/')
        splStr = splStr[len(splStr) - 1].split('.')
        newName = splStr[0] + '-' + randStr + '.' + splStr[1]
        return newName


    ## Call different services throught a single method. Not implemented yet!
    #    This method will be fully implemented on v0.6.0
    #
    #  @param self The object pointer.
    #  @param service_name The Rapp Platform Service to call.
    #  @param args
    #
    def call_service(self, service_name, args):
        print '[%s] service request' % service_name
        # --- Validate existence for the requested service. --- #
        if service_name in self.services_:
            pass
        else:
            # --- Throw an excetion --- #
            print "Service [%s] does not exist" % service_name


    ## Returns a list with the available RAPP Platform services
    #
    #  @param self The object pointer
    #
    #  @return The Platform Services supported by the Rapp-API
    #
    def get_platform_services(self):
        return self.services_


    ## API call for Speech-Detection-Sphinx4 RAPP Platform front-end service.
    #
    #  @param self The object pointer.
    #  @param language Language to be used by the speech_detection_sphinx4
    #    module. Currently valid language values are ‘gr’ for Greek and
    #    ‘en’ for English.
    #  @param audio_source A value that presents the information for the
    #    audio source data. e.g "nao_wav_1_ch".
    #  @param words A vector that carries the "under-detection" words.
    #  @param sentences The under consideration sentences.
    #  @param grammar Grammar to be used.
    #  @param file_uri Path to the audio/speech file to be given as input
    #    to the speech_detection_sphinx4 Platform Service.
    #  @param user User's name, a.k.a username.
    #
    #  @return Rapp Platform Service response object.
    #
    def speech_detection_sphinx4(self, language, audio_source, words, \
                                 sentences, grammar, file_uri, user):
        # -- Craft the data payload for the post request
        payload = {
            'language':language,
            'audio_source':audio_source,
            'words':json.dumps(words),
            'sentences':json.dumps(sentences),
            'grammar':json.dumps(grammar),
            'user': user
        }

        fileName = self.__appendRandStr(file_uri)
        # -- Files to be added into to post request
        files = {
            'file_uri': (fileName, open(file_uri, 'rb'))
        }
        url = self.serviceUrl_['speech_detection_sphinx4']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData


    ## API call for Speech-Detection-Google RAPP Platform front-end service.
    #
    #  @param self The object pointer.
    #  @param language Language to be used by the speech_detection_sphinx4
    #    module. Currently valid language values are ‘gr’ for Greek and
    #    ‘en’ for English.
    #  @param audio_source A value that presents the information for the
    #    audio source data. e.g "nao_wav_1_ch".
    #  @param file_uri Path to the audio/speech file to be given as input
    #    to the speech_detection_google Platform Service.
    #  @param user User's name, a.k.a username.
    #
    #  @return Rapp Platform Service response object.
    #
    def speech_detection_google(self, file_uri, audio_source, user, language):
        # -- Craft the data payload for the post request
        payload = {
            'audio_source': audio_source,
            'user': user,
            'language': language
        }

        fileName = self.__appendRandStr(file_uri)
        # -- Files to be added into to post request
        files = {
            'file_uri': (fileName, open(file_uri, 'rb'))
        }
        url = self.serviceUrl_['speech_detection_google']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData


    ## API call for Set-Noise-Profile RAPP Platform front-end service.
    #
    #  @param self The object pointer.
    #  @param audio_source A value that presents the information for the
    #    audio source data. e.g "nao_wav_1_ch".
    #  @param file_uri Path to the audio/speech file to be given as input
    #    to the speech_detection_google Platform Service.
    #  @param user User's name, a.k.a username.
    #
    #  @return Rapp Platform Service response object.
    #
    def set_noise_profile(self, file_uri, audio_source, user):
        fileName = self.__appendRandStr(file_uri)
        # -- Craft the data payload for the post request
        payload = {
            'user': user,
            'audio_source': audio_source
        }
        # -- Files to be added into to poset request
        files = {
            'file_uri': (fileName, open(file_uri, 'rb'))
        }
        url = self.serviceUrl_['set_noise_profile']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData


    ## API call for Qr-Detection RAPP Platform front-end service.
    #
    #  @param self The object pointer.
    #  @param file_uri Path to the image file to be given as input
    #    to the qr_detection Platform Service.
    #
    #  @return Rapp Platform Service response object.
    #
    def qr_detection(self, file_uri):
        fileName = self.__appendRandStr(file_uri)
        files = {
            'file_uri': (fileName, open(file_uri, 'rb'))
        }

        payload = {}
        url = self.serviceUrl_['qr_detection']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData


    ## API call for Face-Detection RAPP Platform front-end service.
    #
    #  @param self The object pointer.
    #  @param file_uri Path to the image file to be given as input
    #    to the face_detection Platform Service.
    #
    #  @return Rapp Platform Service response object.
    #
    def face_detection(self, file_uri, fast = False):
        fileName = self.__appendRandStr(file_uri)
        files = {
            'file_uri': (fileName, open(file_uri, 'rb'))
        }
        payload = {
            'fast': bool(fast)
        }
        url = self.serviceUrl_['face_detection']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData



    ## API call for Ontology-Subclasses-Of RAPP Platform front-end service.
    #
    #  @param self The object pointer.
    #  @param query Ontology query string.
    #
    #  @return Rapp Platform Service response object.
    #
    def ontology_subclasses_of(self, query):
        payload = {
            'query': query,
        }
        files = {}
        url = self.serviceUrl_['ontology_subclasses_of']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData


    ## API call for Ontology-Superclasses-Of RAPP Platform front-end service.
    #
    #  @param self The object pointer.
    #  @param query Ontology query string.
    #
    #  @return Rapp Platform Service response object.
    #
    def ontology_superclasses_of(self, query):
        payload = {
            'query': query,
        }
        files = {}
        url = self.serviceUrl_['ontology_superclasses_of']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData


    ## API call for Ontology-Subsuperclass-Of RAPP Platform front-end service.
    #
    #  @param self The object pointer.
    #  @param parent_class Ontology parent class name.
    #  @param child_class Ontology child calss name.
    #  @param recursive Defines if a recursive procedure will be used (bool).
    #
    #  @return Rapp Platform Service response object.
    #
    def ontology_is_subsuperclass_of(self, parent_class, child_class, recursive):
        rec = False
        if recursive != None:
            rec = recursive

        payload = {
            'parent_class': parent_class,
            'child_class': child_class,
            'recursive': rec
        }
        files = {}
        url = self.serviceUrl_['ontology_is_subsuperclass_of']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData


    ## NOT SUPPORTED. DEPRECATED!!!
    def detect_objects(self, fileUri, limit):
        fileName = self.__appendRandStr(fileUri)
        # -- Files to be added into to poset request
        files = {
            'file_uri': (fileName, open(fileUri, 'rb'))
        }
        payload = {
            'limit': int(limit)
        }
        url = self.serviceUrl_['detect_objects']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData


    ## API call for Ontology-Subsuperclass-Of RAPP Platform front-end service.
    #
    #  @param self The object pointer.
    #
    #  @return Rapp Platform Service response object.
    #
    def available_services(self):
        #  There seems to be an error with Hop-server on empty payload post
        #  requests. The use of the dummyVar into the payload field resolves
        #  the bug.
        #  TODO Report this bug to HOP developers/maintainers

        payload = {
            'dummyVar': ''
        }
        files = {}
        url = self.serviceUrl_['available_services']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData


    ## API call for Text-To-Speech RAPP Platform front-end service.
    #
    #  @param self The object pointer.
    #  @param text String to perform TTS on.
    #  @param language Supported translation language. 'el' -> Greek,
    #   'en' -> English.
    #  @param dest If provided the returned audio data will be stored in this
    #   destination file. Otherwise the audio data are returned as part of
    #   return object.
    #
    #  @return Rapp Platform Service API call response object.
    #
    def text_to_speech(self, text, language, dest):
        files = {}
        payload = {
            'text': text,
            'language': language
        }
        url = self.serviceUrl_['text_to_speech']

        response = CloudInterface.callService(url, payload, files, self.auth_)
        returnData = {}
        # Parse response error field.
        if response['error']:
            returnData['error'] = response['error']
            return returnData
        else:
            try:
                # Decode base64 encoded payload
                audioRawData = base64.b64decode(response['payload'])
            except Exception as e:
                returnData['error'] = 'Failed to base64.decode payload data'
                print e
                return returnData
            finally:
                pass
        returnData['error'] = ''
        # Parse dest parameter.
        if not dest:
            returnData['audioData'] = audioRawData
            returnData['basename'] = response['basename']
            #returnData['mime'] = magic.from_buffer(returnData['audioData'],
            #                                       mime=True)
        else:
            try:
                # Write audio data to given destination file path.
                with open(dest, 'wb') as f1:
                    f1.write(audioRawData)
            except Exception as e:
                returnData['error'] = \
                    'Failed to write data at destination file [%s]' % dest
            finally:
                pass
        return returnData



    # ======================= Cognitive Exercises ========================= #
    #=======================================================================#

    ## API call for Cognitive-Test-Chooser RAPP Platform front-end service.
    #
    #  @param self The object pointer.
    #  @param testType Cognitive Test Type. ArithmeticCts, AwarenessCts,
    #    ReasoningCts.
    #  @param user User's name, a.k.a username.
    #
    #  @return Rapp Platform Service API call response object.
    #
    def cognitive_test_chooser(self, user, testType):
        files = {}
        payload = {
            'user': user,
            'test_type': testType
        }
        url = self.serviceUrl_['cognitive_test_chooser']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData


    ## API call for Record-Cognitive-Test-Performance RAPP Platform
    #    front-end service
    #
    #  @param self The object pointer.
    #  @param user User's name, a.k.a username.
    #  @param test Test full name as obtained from a call to
    #    cognitive_test_chooser Platform service.
    #  @param score User's score for given test in range [0-100].
    #
    #  @return Rapp Platform Service API call response object.
    #
    def record_cognitive_test_performance(self, user, test, score):
        files = {}
        payload = {
            'user': user,
            'test_instance': test,
            'score': score
        }
        url = self.serviceUrl_['record_cognitive_test_performance']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData

    def cognitive_get_scores(self, username, upToTime):
        files = {}
        payload = {
            'user': username,
            'up_to_time': upToTime
        }
        url = self.serviceUrl_['cognitive_get_scores']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData
