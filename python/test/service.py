#!/usr/bin/env python
# -*- coding: utf-8 -*-


import unittest
import time
import inspect
from os import path

from RappCloud import CloudObjects
from RappCloud.Objects.Cloud import FaceDetection
from RappCloud import Service

global testdatadir
testdatadir = path.realpath(
    path.join(path.dirname(path.realpath(__file__)), '../../testdata')
    )



class TestServiceCalls(unittest.TestCase):
    def setUp(self):
        self.startTime = time.time()

    def tearDown(self):
        t = time.time() - self.startTime
        print "%s: %.3f" % (self.id(), t)


    def test_service_instance(self):
        _msg = CloudObjects.FaceDetection(
            image='../../testdata/Lenna.png', fast=True)
        _svc = Service(_msg)
        self.assertEqual(_svc.svcname, 'face_detection')

        _validReq = {}
        self.assertEqual(_svc.req, _msg.req)
        self.assertEqual(_svc.resp, _msg.resp)



if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(TestServiceCalls)
    unittest.TextTestRunner(verbosity=0).run(suite)
