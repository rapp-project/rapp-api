#!/usr/bin/env python
# -*- coding: utf-8 -*-


import unittest
import time
import inspect
from os import path

from RappCloud import CloudObjects
from RappCloud.Objects.Cloud import FaceDetection

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


    def test_face_detection_request(self):
        msg = CloudObjects.FaceDetection(
            image='/tmp/test', fast=True)

        self.assertEqual(msg.req.image, '/tmp/test')
        self.assertEqual(msg.req.fast, True)
        self.assertEqual(msg.req.serialize(),
                         {
                            'image': '/tmp/test',
                            'fast': True
                         })


    def test_face_detection_response(self):
        msg = CloudObjects.FaceDetection(
            image='/tmp/test', fast=True)

        self.assertEqual(msg.resp.faces, [])
        self.assertEqual(msg.resp.error, '')
        self.assertEqual(msg.resp.serialize(),
                         {
                             'faces': [],
                             'error': ''
                         })



    def test_face_detection_attribute_error(self):
        try:
            msg = FaceDetection(
                filepath='/tmp/test', fast=True)
        except AttributeError as e:
            pass
            


if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(TestServiceCalls)
    unittest.TextTestRunner(verbosity=0).run(suite)
