#!/usr/bin/env python
# -*- coding: utf-8 -*-

#MIT License (MIT)

#Copyright (c) <2014> <Rapp Project EU>

#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:

#The above copyright notice and this permission notice shall be included in
#all copies or substantial portions of the Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#THE SOFTWARE.

# Authors: Konstantinos Panayiotou, Manos Tsardoulias
# contact: klpanagi@gmail.com, etsardou@iti.gr


import json
import os
from CloudInterface import CloudInterface

#  Set and hold RappCloud directory path
__path__ = os.path.dirname(__file__)


class RappCloud:

    ##
    #   @brief default constructor
    ##
    def __init__(self):
        # --- Load Rapp Platform parameters --- #
        self.platform_params_ = None
        self.platformIp_ = ''
        self.servicePort_ = ''
        self.services_ = []
        self.serviceUrl_ = {}
        self.auth_ = {}
        self.__load_platform_params()
        # ------------------------------------- #
    #============================================================================


    ##
    #   @brief load server parameters from parameters.json file
    ##
    def __load_platform_params(self):
        parameters_file_path = __path__ + '/config/platform_parameters.json'
        #print parameters_file_path
        with open(parameters_file_path) as json_file:
            params = json.load(json_file)

        self.platform_params_ = params['platform']
        self.platformIP_ = self.platform_params_['host_ip']
        self.servicePort_ = self.platform_params_['services']['port']
        self.auth_['username'] = self.platform_params_['auth']['username']
        self.auth_['password'] = self.platform_params_['auth']['password']

        for service in self.platform_params_['services']['name']:
            self.services_.append(service)
            self.serviceUrl_[service] = 'http://' + self.platformIP_ + ':' + str(self.servicePort_) + '/hop/' + \
                service


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

        # -- Files to be added into to poset request
        files = {'file_uri': open(fileUri, 'rb')}
        url = self.serviceUrl_['speech_detection_sphinx4']

        returnData = CloudInterface.callService(url, payload, files, self.auth_)
        return returnData
    #============================================================================


    ##
    #   @brief Calls set_denoise_profile() RAPP Platform front-end service.
    #   @return Return answer from RAPP Platform.
    ##
    def set_denoise_profile(self, noise_audio_fileUri, audio_file_type, user):
        # -- Craft the data payload for the post request
        payload = {
            'user': user,
            'audio_source': audio_file_type
        }
        # -- Files to be added into to poset request
        files = {
            'file_uri': open(noise_audio_fileUri, 'rb')
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
        files = {
            'file_uri': open(fileUri, 'rb'),
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
        files = {
            'file_uri': open(fileUri, 'rb')
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
        # -- Files to be added into to poset request
        files = {
            'file_uri': open(fileUri, 'rb')
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

