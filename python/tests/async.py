#!/usr/bin/env python
# -*- coding: utf-8 -*-


import unittest
import time
import inspect
import sys, os
from os import path

from RappCloud.CloudMsgs import FaceDetection
from RappCloud import RappPlatformService as Service

global testdatadir
testdatadir = path.realpath(
    path.join(path.dirname(path.realpath(__file__)), '../../testdata')
    )


class NullDevice():
    def write(self, s):
        pass


class AsyncCallsTest(unittest.TestCase):
    def blockPrint(self):
        sys.stdout = NullDevice()
        sys.stderr = NullDevice()


    def enablePrint(self):
        sys.stdout = sys.__stdout__
        sys.stderr = sys.__stderr__


    def setUp(self):
        self.startTime = time.time()
        self.msg = FaceDetection()
        self.msg.req.imageFilepath = path.join(testdatadir, 'Lenna.png')
        self.msg.req.fast = False
        self.svc = Service(msg=self.msg, persistent=True, timeout=15000)


    def tearDown(self):
        t = time.time() - self.startTime
        print "%s: %.3f" % (self.id(), t)


    def test_simple(self):
        sh = self.svc.call_async(self.msg, self.clb1)
        sh.wait()


    def test_wait(self):
        sh = self.svc.call_async(self.msg, self.clb1)
        resp = sh.wait()
        self.assertIsInstance(resp, FaceDetection.Response)


    def test_wait_no_callback(self):
        sh = self.svc.call_async(self.msg)
        resp = sh.wait()
        self.assertIsInstance(resp, FaceDetection.Response)


    def test_async_multi_calls_x2(self):
        n = 2
        asyncH = []
        for i in range(0, n):
            asyncH.append(self.svc.call_async(self.msg, self.clb1))
        for h in asyncH:
            h.wait()


    def clb1(self, resp):
        self.assertIsInstance(resp, FaceDetection.Response)


if __name__ == '__main__':
    unittest.main(verbosity=2)
    # suite = unittest.TestLoader().loadTestsFromTestCase(AsyncCallsTest)
    # unittest.TextTestRunner(verbosity=0).run(suite)
