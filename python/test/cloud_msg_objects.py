import unittest
import time
import inspect
from os import path
import json

# from RappCloud import CloudMsgs
from RappCloud.CloudMsgs import (
    FaceDetection,
    QrDetection,
    SpeechRecognitionSphinx)

from RappCloud.Objects import (
    Payload,
    File)


class FaceDetectionTest(unittest.TestCase):
    # Overwrite
    def setUp(self):
        self.msg = FaceDetection()
        self.msg.req.imageFilepath = '../../testdata/Lenna.png'
        self.msg.req.fast = True
        self.startTime = time.time()


    def test_request_object(self):
        self.assertIsInstance(self.msg.req, FaceDetection.Request)
        self.assertEqual(self.msg.req.imageFilepath, '../../testdata/Lenna.png')
        self.assertEqual(self.msg.req.fast, True)


    @unittest.expectedFailure
    def test_attribute_error(self):
        self.msg.filepath


    def test_request_serialize(self):
        _expected = {
            'imageFilepath': '../../testdata/Lenna.png',
            'fast': True
        }
        self.assertEqual(self.msg.req.serialize(), _expected)


    def test_make_payload(self):
        _payload = self.msg.req.make_payload()
        self.assertIsInstance(_payload, Payload)
        self.assertIsInstance(_payload.serialize(), dict)
        self.assertEqual(_payload.serialize(), {'fast': True})
        self.assertEqual(_payload.make_json(), '{"fast": true}')



class QrDetectionTest(unittest.TestCase):
    # Overwrite
    def setUp(self):
        self.msg = QrDetection()
        self.msg.req.imageFilepath = '../../testdata/qrcode.png'
        self.startTime = time.time()


    def test_request_object(self):
        self.assertIsInstance(self.msg.req, QrDetection.Request)
        self.assertEqual(self.msg.req.imageFilepath, '../../testdata/qrcode.png')


    @unittest.expectedFailure
    def test_attribute_error(self):
        self.msg.filepath


    def test_request_serialize(self):
        _expected = {
            'imageFilepath': '../../testdata/qrcode.png'
        }
        self.assertEqual(self.msg.req.serialize(), _expected)


    def test_make_payload(self):
        _payload = self.msg.req.make_payload()
        self.assertIsInstance(_payload, Payload)
        self.assertEqual(_payload.serialize(), {})
        self.assertIsInstance(_payload.serialize(), dict)
        self.assertEqual(_payload.make_json(), '{}')



class SpeechRecognitionSphinxTest(unittest.TestCase):
    # Overwrite
    def setUp(self):
        self.msg = SpeechRecognitionSphinx()
        self.msg.req.words = ['test', 'testing']
        self.msg.req.grammar = []
        self.msg.req.sentences = ['test', 'testing']
        self.msg.req.language = 'el'
        self.msg.req.audio_source = 'nao_wav_1_ch'
        self.msg.req.audiofile = '../../testdata/silence_sample.wav'
        self.startTime = time.time()


    def test_request_object(self):
        self.assertIsInstance(self.msg.req, SpeechRecognitionSphinx.Request)


    @unittest.expectedFailure
    def test_attribute_error(self):
        _msg = SpeechRecognitionSphinx(
            filepath='../../testdata/qrcode.png', fast=True)


    def test_request_serialize(self):
        _expected = {
            'audiofile': '../../testdata/silence_sample.wav',
            'words': ['test', 'testing'],
            'grammar': [],
            'sentences': ['test', 'testing'],
            'language': 'el',
            'audio_source': 'nao_wav_1_ch'
        }
        self.assertEqual(self.msg.req.serialize(), _expected)


    def test_make_payload(self):
        _expected = {
            'words': ['test', 'testing'],
            'grammar': [],
            'sentences': ['test', 'testing'],
            'language': 'el',
            'audio_source': 'nao_wav_1_ch'
        }
        _payload = self.msg.req.make_payload()
        self.assertIsInstance(_payload, Payload)
        self.assertEqual(_payload.serialize(), _expected)
        self.assertIsInstance(_payload.serialize(), dict)



if __name__ == '__main__':
    unittest.main(verbosity=2)
    # suite = unittest.TestLoader().loadTestsFromTestCase(FaceDetectionTest)
    # unittest.TextTestRunner(verbosity=2).run(suite)
