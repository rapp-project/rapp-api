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


class ServiceTest(unittest.TestCase):
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
        self.msg.req.fast = True
        self.svc = Service()


    def tearDown(self):
        t = time.time() - self.startTime
        print "%s: %.3f" % (self.id(), t)


    def test_constructor_pass_cloud_object(self):
        self.svc = Service(msg=self.msg, persistent=False, timeout=15000)
        self.assertIsInstance(self.svc.req, FaceDetection.Request)
        self.assertIsInstance(self.svc.resp, FaceDetection.Response)


    def test_constructor_arguments(self):
        self.svc = Service(msg=self.msg, persistent=False, timeout=15000,
                           address='155.207.19.229', port='9002',
                           protocol='https')
        self.assertEqual(self.svc.timeout, 15000)
        self.assertEqual(self.svc.persistent, False)
        self.assertEqual(self.svc.req, self.msg.req)
        self.assertEqual(self.svc.resp, self.msg.resp)


    def test_explicit_set_attributes(self):
        self.svc.persistent = False
        self.svc.timeout = 15000
        self.assertEqual(self.svc.timeout, 15000)
        self.assertEqual(self.svc.persistent, False)


    def test_request_object_getter(self):
        self.svc = Service(msg=self.msg)
        _req = self.svc.req
        self.assertIsInstance(_req, FaceDetection.Request)
        self.assertEqual(_req, self.msg.req)


    def test_response_object_getter(self):
        self.svc = Service(msg=self.msg)
        _resp = self.svc.resp
        self.assertIsInstance(_resp, FaceDetection.Response)
        self.assertEqual(_resp, self.msg.resp)


    def test_call_response(self):
        self.svc = Service(msg=self.msg)
        self.blockPrint()
        _resp = self.svc.call(self.msg)
        self.enablePrint()
        self.assertIsInstance(_resp, FaceDetection.Response)
        self.assertIsInstance(_resp.faces, list)
        self.assertIsInstance(_resp.error, basestring)


    def test_call_multi(self):
        self.svc = Service(msg=self.msg)
        self.blockPrint()
        _resp = self.svc.call(self.msg)
        for _ in range(10):
            _respTemp = self.svc.call(self.msg)
            self.assertEqual(_resp, _respTemp)
            _resp = _respTemp
        self.enablePrint()


if __name__ == '__main__':
    unittest.main(verbosity=2)
    # suite = unittest.TestLoader().loadTestsFromTestCase(ServiceTest)
    # unittest.TextTestRunner(verbosity=0).run(suite)
