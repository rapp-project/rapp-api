#!/usr/bin/env python
# -*- coding: utf-8 -*-


# Copyright 2016 RAPP

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


## @file ServiceController/RAPPAuth.py
#
#  @copyright Rapp Projecty EU 2016
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


from requests.auth import AuthBase
from os import path


class RAPPAuth(AuthBase):
  """ RAPP Authentication Class

  Implements the RAPP Authentication mechanism for Platform requests.
  """

  def __init__(self, token='', svcname=''):
    """! Constructor

    @param string token
    @param string svcname - The service/application name.
    """
    # The application tokens storage directory.
    self._tokenStoreDir = path.expanduser('~/.config/rapp_platform/tokens')

    if token is not '':
      self._token = token
    else:
      self.__load_token()


  def __call__(self, r):
    """! Append the application token to the HTTP application protocol header.

    Modify the request object. Append token string to the Accept-Token
    field of the request header.
    """
    r.headers['Accept-Token'] = self._token
    return r


  def __load_token(self, svcname=""):
    """! Load the RAPP Platform authentication token.

    Currently only one application token exists, giving access to all the
    RAPP Platform services!!
    """
    ## TODO Load different tokens per application request.
    self.__read_token_from_file(path.join(self._tokenStoreDir, 'app'))


  def __read_token_from_file(self, filepath):
    """! Read and token string stored in a file.

    @param filepath string - The token file path.
    """
    with open(filepath, 'r') as tokenF:
      self._token = str(tokenF.read()).replace('\n', '')


