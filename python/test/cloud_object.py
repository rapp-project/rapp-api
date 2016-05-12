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


    def test_cloud_object_request(self):
        msg = CloudObjects.FaceDetection(
            image='/tmp/test', fast=True)

        self.assertEqual(msg.req.image, '/tmp/test')
        self.assertEqual(msg.req.fast, True)
        self.assertEqual(msg.req.serialize(),
                         {
                            'image': '/tmp/test',
                            'fast': True
                         })


    def test_cloud_object_response(self):
        msg = CloudObjects.FaceDetection(
            image='/tmp/test', fast=True)

        self.assertEqual(msg.resp.faces, [])
        self.assertEqual(msg.resp.error, '')
        self.assertEqual(msg.resp.serialize(),
                         {
                             'faces': [],
                             'error': ''
                         })


    def test_cloud_object_attribute_error(self):
        try:
            msg = FaceDetection(
                filepath='../../testdata/Lenna.png', fast=True)
        except AttributeError as e:
            pass


    def test_cloud_object_make_payload(self):
        from RappCloud.Objects import Payload
        _msg = CloudObjects.FaceDetection(
            image='../../testdata/Lenna.png', fast=True)

        _payload = _msg.req.make_payload()
        self.assertIsInstance(_payload, Payload)
        self.assertIsInstance(_payload.serialize(), dict)
        self.assertEqual(_payload.serialize(), {'fast': True})
        self.assertEqual(_payload.make_json(), '{"fast": true}')


    def test_cloud_object_make_files(self):
        from RappCloud.Objects import File
        _msg = CloudObjects.FaceDetection(
            image='../../testdata/Lenna.png', fast=True)

        _files = _msg.req.make_files()
        self.assertIsInstance(_files, list)
        self.assertEqual(len(_files), 1)
        self.assertIsInstance(_files[0], File)
        self.assertIsInstance(_files[0].serialize(), dict)
        self.assertEqual(_files[0].postfield, 'file')
        self.assertEqual(_files[0].path, path.expanduser(
            path.realpath('../../testdata/Lenna.png')))
        self.assertIsInstance(_files[0].make_tuple(), tuple)



if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(TestServiceCalls)
    unittest.TextTestRunner(verbosity=0).run(suite)
