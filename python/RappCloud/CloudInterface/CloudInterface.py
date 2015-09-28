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

import requests  # Import global module scope

from requests.auth import HTTPBasicAuth  # Http basic authentication
from requests.exceptions import *  # Requests Exceptions
import magic
import json

class CloudInterface:

    ##
    #   @brief TODO
    #   @param basicAuth Basic http authentication credentials
    #       {'username': '', 'password': ''}
    #   @param url Post request destination Url.
    #   @param payload data payload of the post request.
    #   @param files multipart post file field.
    ##
    @staticmethod
    def callService(url, payload, files, basicAuth):
        try:
            response = requests.post(url, data=payload, files=files,  \
                    auth=HTTPBasicAuth(basicAuth['username'], \
                                       basicAuth['password']))
            print response.headers
        except ConnectionError as e:
            print "Cannot resolve domain name [%s]" % url
            print e
            returnData = {
                'error': str(e.message)
            }
        except HTTPError as e:
            print "HTTP Error: %s" % e.message
            returnData = {
                'error': str(e.mesasge)
            }
        except Exception as e: # Catch all exceptions
            returnData = {
                'error': str(e)
            }
        else:
            if CloudInterface.isJson(response.content):
                returnData = json.loads(response.content)
            else:  # Check if binary data (responseFile)
                # Return file type too
                returnData = {
                    'data': response.content,
                    'format': CloudInterface.dataType(response.content),
                    'error': ''
                }
        return returnData
    #============================================================================

    ##
    #   @brief Check if data are in json format.
    #   @return True if data are in json format. False otherwise.
    ##
    @staticmethod
    def isJson(data):
        try:
            json.loads(data)
        except ValueError:
            return False
        return True
    #============================================================================

    ##
    #   @brief Return type of binary data (image/png, image/jpg, etc)
    #   @return Data type
    ##
    @staticmethod
    def dataType(data):
        return magic.from_buffer(data, mime=True)


