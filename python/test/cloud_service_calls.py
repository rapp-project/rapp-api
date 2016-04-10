#!/usr/bin/env python

import unittest
import time
import inspect
from os import path

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


    def test_face_detection(self):
        from RappCloud import FaceDetection
        fast = True
        imagepath = path.join(testdatadir, 'Lenna.png')
        faceDetector = FaceDetection(image=imagepath)
        resp = faceDetector.call()
        self.assertEqual(resp.error, '')


    def test_qr_detection(self):
        from RappCloud import QrDetection
        imagepath = path.join(testdatadir, 'qrcode.png')
        qrDetector = QrDetection(image=imagepath)
        resp = qrDetector.call()
        self.assertEqual(resp.error, '')


    def test_speech_detection_sphinx4(self):
        from RappCloud import SpeechDetectionSphinx4
        audiofile = path.join(testdatadir, 'nao_wav_d05_a1.wav_mono16k.wav')
        speechDetector = SpeechDetectionSphinx4()
        speechDetector.language = 'en'
        speechDetector.audio_source = 'nao_wav_1_ch'
        speechDetector.audiofile = audiofile
        speechDetector.words = ["test"]
        resp = speechDetector.call()
        self.assertEqual(resp.error, '')


    def test_speech_detection_google(self):
        from RappCloud import SpeechDetectionGoogle
        audiofile = path.join(testdatadir, 'silence_sample.wav')
        speechDetector = SpeechDetectionGoogle()
        speechDetector.language = 'en'
        speechDetector.audio_source = 'nao_wav_1_ch'
        speechDetector.audiofile = audiofile
        resp = speechDetector.call()
        self.assertEqual(resp.error, '')


    def test_set_noise_profile(self):
        from RappCloud import SetNoiseProfile
        audiofile = path.join(testdatadir, 'denoise_source.wav')
        denoiser = SetNoiseProfile()
        denoiser.audio_source = 'nao_wav_1_ch'
        denoiser.audiofile = audiofile
        resp = denoiser.call()
        self.assertEqual(resp.error, '')


    def test_ontology_subclassesof(self):
        from RappCloud import OntologySubclassesof
        ontologyQ = OntologySubclassesof(query='Oven')
        resp = ontologyQ.call()
        self.assertEqual(resp.error, '')


    def test_ontology_superclassesof(self):
        from RappCloud import OntologySuperclassesof
        ontologyQ = OntologySuperclassesof(query='Oven')
        resp = ontologyQ.call()
        self.assertEqual(resp.error, '')


    def test_ontology_is_subsuperclass(self):
        from RappCloud import OntologyIsSubsuperclass
        ontologyQ = OntologyIsSubsuperclass()
        ontologyQ.parent_class = 'SpatialThing'
        ontologyQ.child_class = 'Oven'
        ontologyQ.recursive = True
        resp = ontologyQ.call()
        print resp.serialize()
        self.assertEqual(resp.error, '')



if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(TestServiceCalls)
    unittest.TextTestRunner(verbosity=0).run(suite)
