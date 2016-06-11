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


## @file ServiceController/ServiceControllerSync.py
#
#  @copyright Rapp Projecty EU 2015
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


from ServiceControllerBase import *

# high-level interface for asynchronously executing callables.
from concurrent.futures import ThreadPoolExecutor, as_completed



class ServiceControllerAsync(ServiceControllerBase):
    """ Synchronous service controller class implementation. """

    def __init__(self, service, max_workers=8):
        """! Constructor

        @param service Service - Service instance.
        @param max_workers - Number of maximum workers to spawn
        """
        # Create a thread pool manager
        self.__threadPool = ThreadPoolExecutor(max_workers=max_workers)

        super(ServiceControllerAsync, self).__init__(service)


    def run_job(self, msg, url, clb=None):
        """! Run the service

        Submit callback function to the worker thread and return the future.
        @param clb Function - Callback function to execute on arrival of
            the response.

        @returns _future - The future.
        """
        _future = self.__threadPool.submit(self._worker_exec, msg, url, clb=clb)
        return _future


    def _worker_exec(self, msg, url, clb=None):
        # Unpack payload and file objects from cloud service object
        payload = msg.req.make_payload()
        files = msg.req.make_files()

        if self._service.persistent:
            resp = self._post_persistent(url, payload, files)
        else:
            resp = self._post_session_once(url, payload, files)

        for key, val in resp.iteritems():
            msg.resp.set(key, val)
        if clb is not None:
            clb(msg.resp)
        return msg.resp
