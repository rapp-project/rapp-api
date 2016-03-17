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
from requests.adapters import HTTPAdapter
from requests.packages.urllib3.poolmanager import PoolManager
import ssl  # Python 2.7 ssl library. Instead, use pyopenssl library.
from OpenSSL import SSL

import requests

# Tell urllib3 to switch the ssl backend to PyOpenSSL
import urllib3.contrib.pyopenssl
urllib3.contrib.pyopenssl.inject_into_urllib3()

# Disable Insecure Request Warning caused due to missing https cert verification
requests.packages.urllib3.disable_warnings()



# @brief An HTTPS Transport Adapter that uses SSL3 version.'''
class SSLAdapter(HTTPAdapter):
  def __init__(self, ssl_version=None, **kwargs):
    self.ssl_version = ssl_version
    super(SSLAdapter, self).__init__(**kwargs)


  def init_poolmanager(self, connections, maxsize, block=False):
    self.poolmanager = PoolManager(num_pools=connections,
                                   maxsize=maxsize,
                                   block=block,
                                   ssl_version=self.ssl_version)


class TLSAdapter(SSLAdapter):
    def __init__(self, **kwargs):
        super(TLSAdapter, self).__init__(ssl_version=None, \
                                         **kwargs)


class TLS1Adapter(SSLAdapter):
    def __init__(self, **kwargs):
        super(TLS1Adapter, self).__init__(ssl_version=SSL.TLSv1_METHOD, \
                                         **kwargs)


class TLS11Adapter(SSLAdapter):
    def __init__(self, **kwargs):
        super(TLS11Adapter, self).__init__(ssl_version=SSL.TLSv1_1_METHOD, \
                                         **kwargs)


class TLS12Adapter(SSLAdapter):
    def __init__(self, **kwargs):
        super(TLS12Adapter, self).__init__(ssl_version=SSL.TLSv1_2_METHOD, \
                                         **kwargs)


class SSL2Adapter(SSLAdapter):
    def __init__(self, **kwargs):
        super(SSL2Adapter, self).__init__(ssl_version=SSL.SSLv2_METHOD, \
                                         **kwargs)

class SSL3Adapter(SSLAdapter):
    def __init__(self, **kwargs):
        super(SSL3Adapter, self).__init__(ssl_version=SSL.SSLv3_METHOD, \
                                         **kwargs)

class SSL23Adapter(SSLAdapter):
    def __init__(self, **kwargs):
        super(SSL23Adapter, self).__init__(ssl_version=SSL.SSLv23_METHOD, \
                                         **kwargs)
