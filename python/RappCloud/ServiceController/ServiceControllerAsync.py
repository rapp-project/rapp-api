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
from concurrent import futures



class ServiceControllerAsync(ServiceControllerBase):
    """ Synchronous service controller class implementation. """

    def __init__(self, service, max_workers=8):
        """! Constructor

        @param service Service - Service instance.
        @param max_workers - Number of maximum workers to spawn
        """
        # Create a thread pool manager
        self.__threadPool = futures.ThreadPoolExecutor(max_workers=max_workers)

        super(ServiceControllerAsync, self).__init__(service)


    def run_job(self, clb, msg, url):
        """! Run the service"""
        _future = self.__threadPool.submit(self._worker_exec, clb, msg, url)



    def _worker_exec(self, clb, msg, url):
        print "_worker execution function here!"
        # Unpack payload and file objects from cloud service object
        payload = msg.req.make_payload()
        files = msg.req.make_files()

        if self._service.persistent:
            resp = self._post_persistent(url, payload, files)
        else:
            resp = self._post_session_once(url, payload, files)

        for key, val in resp.iteritems():
            msg.resp.set(key, val)
        clb(msg.resp)
