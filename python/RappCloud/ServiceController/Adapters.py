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


## @file RappCloud/ServiceController/Adapters.py
#
#  @copyright Rapp Projecty EU 2016
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#




import sys
import requests
from requests.adapters import HTTPAdapter
from urllib3.poolmanager import PoolManager



class SSLDef:
    """ SSL/TLS Definitions namespace

    SSL/TLS protocol versions definitions
    """
    TLSv1 = None
    TLSv1_1 = None
    TLSv1_2 = None
    SSLv2 = None
    SSLv3 = None
    SSLv2_3 = None


if sys.version_info[:3] >= (2, 7, 9):
    """
    ssl module in Python 2.7.9 or later supports TLS versions 1.1 and 1.2
    """
    import ssl  # Python 2.7 ssl library
    print "\n--> Using python's ssl module with support to TLS v1_1 and 1_2"
    SSLDef.TLSv1 = ssl.PROTOCOL_TLSv1
    SSLDef.TLSv1_1 = ssl.PROTOCOL_TLSv1_1
    SSLDef.TLSv1_2 = ssl.PROTOCOL_TLSv1_2
    SSLDef.SSLv2 = ssl.PROTOCOL_SSLv2
    SSLDef.SSLv3 = ssl.PROTOCOL_SSLv3
    SSLDef.SSLv2_3 = ssl.PROTOCOL_SSLv23
else:
    """ Else import pyopenssl and load tls1_1 and tls_1_2 if available.
    Need to build pyOpenSSL on top of OpenSSL 1.0.1 to
    get TLSv1.1 and 1.2 support
    """
    try:
        from OpenSSL import SSL
        """ Tell urllib3 to switch the ssl backend to PyOpenSSL """
        import urllib3.contrib.pyopenssl
        urllib3.contrib.pyopenssl.inject_into_urllib3()
        """
          Disable Insecure Request Warning caused due to
           missing https cert verification
        """
        requests.packages.urllib3.disable_warnings()

        SSLDef.TLSv1 = SSL.TLSv1_METHOD
        SSLDef.TLSv1_1 = SSL.TLSv1_1_METHOD
        SSLDef.TLSv1_2 = SSL.TLSv1_2_METHOD
        SSLDef.SSLv2 = SSL.SSLv2_METHOD
        SSLDef.SSLv3 = SSL.SSLv3_METHOD
        SSLDef.SSLv2_3 = SSL.SSLv23_METHOD

        print "\n--> Using pyopenssl module instead of python's ssl library" + \
            " with support to tlsv1_2"

    except ImportError as e:
        import ssl  # Python 2.7 ssl library
        print str(e)
        print "\n--> Falling back to python's ssl library without tlsv1_2 support"
        SSLDef.TLSv1 = ssl.PROTOCOL_TLSv1
        SSLDef.TLSv1_1 = ssl.PROTOCOL_TLSv1
        SSLDef.TLSv1_2 = ssl.PROTOCOL_TLSv1
        SSLDef.SSLv2 = ssl.PROTOCOL_SSLv2
        SSLDef.SSLv3 = ssl.PROTOCOL_SSLv3
        SSLDef.SSLv2_3 = ssl.PROTOCOL_SSLv23


    except AttributeError as e:
        print "--> pyOpenSSL does not allow support for tls1_1 and tls1_2." + \
            " PyOpenSSL needs to be build against openssl-1.0.1 to get " + \
            " TLSv1.1 and 1.2 support"
        print "--> Falling back to TLSv1"

        SSLDef.TLSv1 = SSL.TLSv1_METHOD
        SSLDef.TLSv1_1 = SSL.TLSv1_METHOD
        SSLDef.TLSv1_2 = SSL.TLSv1_METHOD
        SSLDef.SSLv2 = SSL.SSLv2_METHOD
        SSLDef.SSLv3 = SSL.SSLv3_METHOD
        SSLDef.SSLv2_3 = SSL.SSLv23_METHOD



class SSLAdapter(HTTPAdapter):
    """ SSL Default transport Adapter """
    def __init__(self, ssl_version=None, **kwargs):
        self.ssl_version = ssl_version
        super(SSLAdapter, self).__init__(**kwargs)


    def init_poolmanager(self, connections, maxsize, block=False):
        self.poolmanager = PoolManager(num_pools=connections,
                                       maxsize=maxsize,
                                       block=block,
                                       ssl_version=self.ssl_version)


class TLSAdapter(SSLAdapter):
    """ TLS Default transport Adapter """
    def __init__(self, **kwargs):
        super(TLSAdapter, self).__init__(ssl_version=None, **kwargs)


class TLS1Adapter(SSLAdapter):
    """ TLSv1 Default transport Adapter """
    def __init__(self, **kwargs):
        super(TLS1Adapter, self).__init__(ssl_version=SSLDef.TLSv1, **kwargs)


class TLS11Adapter(SSLAdapter):
    """ TLSv1.1 Default transport Adapter """
    def __init__(self, **kwargs):
        super(TLS11Adapter, self).__init__(ssl_version=SSLDef.TLSv1_1, **kwargs)


class TLS12Adapter(SSLAdapter):
    """ TLSv1.2 Default transport Adapter """
    def __init__(self, **kwargs):
        super(TLS12Adapter, self).__init__(ssl_version=SSLDef.TLSv1_2, **kwargs)


class SSL2Adapter(SSLAdapter):
    """ SSLv2 Default transport Adapter """
    def __init__(self, **kwargs):
        super(SSL2Adapter, self).__init__(ssl_version=SSLDef.SSLv2,
                                          **kwargs)

class SSL3Adapter(SSLAdapter):
    """ SSLv3 Default transport Adapter """
    def __init__(self, **kwargs):
        super(SSL3Adapter, self).__init__(ssl_version=SSLDef.SSLv3,
                                          **kwargs)

class SSL23Adapter(SSLAdapter):
    """ SSLv2_3 Default transport Adapter """
    def __init__(self, **kwargs):
        super(SSL23Adapter, self).__init__(ssl_version=SSLDef.SSLv2_3,
                                           **kwargs)
