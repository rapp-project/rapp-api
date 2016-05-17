#!/usr/bin/env python
# -*- coding: utf-8 -*-


import unittest
import time
import inspect
from os import path

# from RappCloud import CloudMsgs
from RappCloud.CloudMsgs import FaceDetection
from RappCloud.Objects import (
    Payload,
    File)

global testdatadir
testdatadir = path.realpath(
    path.join(path.dirname(path.realpath(__file__)), '../../testdata')
    )



class CloudMsgTest(unittest.TestCase):
    # Overwrite
    def setUp(self):
        self.msg = FaceDetection()
        self.startTime = time.time()


    def test_request_object_instance(self):
        self.msg.req.imageFilepath = '../../testdata/Lenna.png'
        self.msg.req.fast = True
        self.assertIsInstance(self.msg.req, FaceDetection.Request)


    def test_set_req_properties(self):
        self.msg.req.imageFilepath = '../../testdata/Lenna.png'
        self.msg.req.fast = True
        self.assertEqual(self.msg.req.imageFilepath, '../../testdata/Lenna.png')
        self.assertEqual(self.msg.req.fast, True)
        self.msg.req.fast = False
        self.assertEqual(self.msg.req.fast, False)


    @unittest.expectedFailure
    def test_attribute_error(self):
        msg = FaceDetection(
            filepath='../../testdata/Lenna.png', fast=True)


    def test_request_serialize(self):
        self.msg.req.imageFilepath = '../../testdata/Lenna.png'
        self.msg.req.fast = True
        _expected = {
            'imageFilepath': '../../testdata/Lenna.png',
            'fast': True
        }
        self.assertEqual(self.msg.req.serialize(), _expected)


    def test_response_serialize(self):
        self.assertEqual(self.msg.resp.faces, [])
        self.assertEqual(self.msg.resp.error, '')
        _expected = {
            'faces': [],
            'error': ''
        }
        self.assertEqual(self.msg.resp.serialize(), _expected)



    def test_make_payload(self):
        self.msg.req.imageFilepath = '../../testdata/Lenna.png'
        self.msg.req.fast = True
        _payload = self.msg.req.make_payload()
        self.assertIsInstance(_payload, Payload)
        self.assertIsInstance(_payload.serialize(), dict)
        self.assertEqual(_payload.serialize(), {'fast': True})
        self.assertEqual(_payload.make_json(), '{"fast": true}')


    def test_make_files(self):
        self.msg.req.imageFilepath = '../../testdata/Lenna.png'
        self.msg.req.fast = True

        _files = self.msg.req.make_files()
        self.assertIsInstance(_files, list)
        self.assertEqual(len(_files), 1)
        self.assertIsInstance(_files[0], File)
        self.assertIsInstance(_files[0].serialize(), dict)
        self.assertEqual(_files[0].postfield, 'file')
        self.assertEqual(_files[0].path, path.expanduser(
            path.realpath('../../testdata/Lenna.png')))
        self.assertIsInstance(_files[0].make_tuple(), tuple)



if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(CloudMsgTest)
    unittest.TextTestRunner(verbosity=2).run(suite)
