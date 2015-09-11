#!/usr/bin/env python
# -*- coding: utf-8 -*-

##
# MIT License (MIT)

# Copyright (c) <2014> <Rapp Project EU>

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

# Authors: Konstantinos Panayiotou, Manos Tsardoulias
# contact: klpanagi@gmail.com, etsardou@iti.gr
##

import json
import os
import sys
from CloudInterface import CloudInterface
from RandStrGen import RandStrGen
from ConfigParser import SafeConfigParser
import yaml

#  Set and hold RappCloud directory path
__path__ = os.path.dirname(__file__)


class RappCloud:

    ##
    #   @brief default constructor
    ##
    def __init__(self):
        # --- Load Rapp Platform parameters --- #
        self.cfgFileDir_ = __path__ + '/config/'
        self.parameters_file_path_ = __path__ + '/config/platform_parameters.json'
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
        # ------------------------------------- #
    #============================================================================


    def __parse_auth_cfg(self):
        cfgFilePath = self.cfgFileDir_ + 'auth.cfg'
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
    #============================================================================



    def __parse_services_cfg(self):
        cfgFilePath = self.cfgFileDir_ + 'services.yaml'
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
    #============================================================================


    def __parse_platform_cfg(self):
        cfgFilePath = self.cfgFileDir_ + 'platform.cfg'
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
    #============================================================================

    def __appendRandStr(self, filePath):
        randStr = RandStrGen.create(self.__randStrSize)
        splStr = filePath.split('/')
        splStr = splStr[len(splStr) - 1].split('.')
        newName = splStr[0] + '-' + randStr + '.' + splStr[1]
        return newName



    ##
    #   @brief Call different services throught a single method
    #   @TODO Implement!!!
    ##
    def call_service(self, service_name, args):
        print '[%s] service request' % service_name
        # --- Validate existence for the requested service. --- #
        if service_name in self.services_:
            pass
        else:
            # --- Throw an excetion --- #
            print "Service [%s] does not exist" % service_name

    #============================================================================


    ##
    #   @brief Returns a list with the available RAPP Platform services
    ##
    def get_platform_services(self):
        return self.services_



    ##
    #   @brief Calls set_denoise_profile() RAPP Platform front-end service.
    #   @return Return answer from RAPP Platform.
    ##
    def speech_detection_sphinx4(self, language, audio_source, words, \
                                 sentences, grammar, fileUri, user):

        # -- Craft the data payload for the post request
        payload = {
            'language':language,
            'audio_source':audio_source,
            'words':json.dumps(words),
            'sentences':json.dumps(sentences),
            'grammar':json.dumps(grammar),
            'user': user
        }

        fileName = self.__appendRandStr(fileUri)
        # -- Files to be added into to post request
        files = {
            'file_uri': (fileName, open(fileUri, 'rb'))
        }
        url = self.serviceUrl_['speech_detection_sphinx4']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData
    #============================================================================

    def speech_detection_google(self, fileUri):

        # -- Craft the data payload for the post request
        payload = {
        }

        fileName = self.__appendRandStr(fileUri)
        # -- Files to be added into to post request
        files = {
            'file_uri': (fileName, open(fileUri, 'rb'))
        }
        url = self.serviceUrl_['speech_detection_google']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData
    #============================================================================



    ##
    #   @brief Calls set_denoise_profile() RAPP Platform front-end service.
    #   @return Return answer from RAPP Platform.
    ##
    def set_denoise_profile(self, fileUri, audio_file_type, user):
        fileName = self.__appendRandStr(fileUri)
        # -- Craft the data payload for the post request
        payload = {
            'user': user,
            'audio_source': audio_file_type
        }
        # -- Files to be added into to poset request
        files = {
            'file_uri': (fileName, open(fileUri, 'rb'))
        }
        url = self.serviceUrl_['set_denoise_profile']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData
    #============================================================================


    ##
    #   @brief Calls qr_detection() RAPP Platform front-end service.
    #   @return Return answer from RAPP Platform.
    ##
    def qr_detection(self, fileUri):
        fileName = self.__appendRandStr(fileUri)
        files = {
            'file_uri': (fileName, open(fileUri, 'rb'))
        }

        payload = {}
        url = self.serviceUrl_['qr_detection']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData
    #============================================================================


    ##
    #   @brief Calls face_detection() RAPP Platform front-end service.
    #   @return Return answer from RAPP Platform.
    ##
    def face_detection(self, fileUri):
        fileName = self.__appendRandStr(fileUri)
        files = {
            'file_uri': (fileName, open(fileUri, 'rb'))
        }
        payload = {}
        url = self.serviceUrl_['face_detection']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData
    #============================================================================


    ##
    #   @brief Calls the ontology_subclasses_of() RAPP Platform
    #       front-end service.
    #   @return Return answer from RAPP Platform.
    ##
    def ontology_subclasses_of(self, query):
        payload = {
            'query': query,
        }
        files = {}
        url = self.serviceUrl_['ontology_subclasses_of']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData
    #============================================================================


    ##
    #   @brief Calls the ontology_superclasses_of() RAPP Platform
    #       front-end service.
    #   @return Return answer from RAPP Platform.
    ##
    def ontology_superclasses_of(self, query):
        payload = {
            'query': query,
        }
        files = {}
        url = self.serviceUrl_['ontology_superclasses_of']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData
    #============================================================================


    ##
    #   @brief Calls the ontology_is_subsuperclass_of() RAPP Platform
    #       front-end service.
    #   @return Return answer from RAPP Platform.
    ##
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
    #============================================================================



    ##
    #   @brief Calls the detect_objects() RAPP Platform front-end service.
    #   @return Return answer from RAPP Platform.
    ##
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
    #============================================================================


    ##
    #   @brief Calls the available_services() RAPP Platform front-end service.
    #   @return Return answer from RAPP Platform.
    ##
    def available_services(self):

        ##
        #   There seems to be an error with Hop-server on empty payload post
        #   requests. The use of the dummyVar into the payload field resolves
        #   the bug.
        #   TODO Report this bug to HOP developers/maintainers
        ##
        payload = {
            'dummyVar': ''
        }
        files = {}
        url = self.serviceUrl_['available_services']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData

