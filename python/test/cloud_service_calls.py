#!/usr/bin/env python
# -*- coding: utf-8 -*-


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


    def test_qr_detection(self):
        from RappCloud import QrDetection
        imagepath = path.join(testdatadir, 'qrcode.png')
        qrDetector = QrDetection(image=imagepath)
        resp = qrDetector.call()


    def test_speech_detection_sphinx4(self):
        from RappCloud import SpeechDetectionSphinx4
        audiofile = path.join(testdatadir, 'nao_wav_d05_a1.wav_mono16k.wav')
        speechDetector = SpeechDetectionSphinx4()
        speechDetector.language = 'en'
        speechDetector.audio_source = 'nao_wav_1_ch'
        speechDetector.audiofile = audiofile
        speechDetector.words = ["test"]
        resp = speechDetector.call()


    def test_speech_detection_google(self):
        from RappCloud import SpeechDetectionGoogle
        audiofile = path.join(testdatadir, 'silence_sample.wav')
        speechDetector = SpeechDetectionGoogle()
        speechDetector.language = 'en'
        speechDetector.audio_source = 'nao_wav_1_ch'
        speechDetector.audiofile = audiofile
        resp = speechDetector.call()


    def test_set_noise_profile(self):
        from RappCloud import SetNoiseProfile
        audiofile = path.join(testdatadir, 'denoise_source.wav')
        denoiser = SetNoiseProfile()
        denoiser.audio_source = 'nao_wav_1_ch'
        denoiser.audiofile = audiofile
        resp = denoiser.call()


    def test_ontology_subclassesof(self):
        from RappCloud import OntologySubclassesof
        ontologyQ = OntologySubclassesof(query='Oven')
        resp = ontologyQ.call()


    def test_ontology_superclassesof(self):
        from RappCloud import OntologySuperclassesof
        ontologyQ = OntologySuperclassesof(query='Oven')
        resp = ontologyQ.call()


    def test_ontology_is_subsuperclass(self):
        from RappCloud import OntologyIsSubsuperclass
        ontologyQ = OntologyIsSubsuperclass()
        ontologyQ.parent_class = 'SpatialThing'
        ontologyQ.child_class = 'Oven'
        ontologyQ.recursive = True
        resp = ontologyQ.call()


    def test_text_to_speech(self):
        from RappCloud import TextToSpeech
        tts = TextToSpeech(language='el', text='Καλησπέρα είμαι πουτανάκι')
        tts.call()
        tts.store_audio('~/tmp/test.wav')



    def test_human_detection(self):
        from RappCloud import HumanDetection
        imagepath = path.join(testdatadir, 'Lenna.png')
        humanDetector = HumanDetection(image=imagepath)
        resp = humanDetector.call()


    def test_cognitive_test_select(self):
        from RappCloud import CognitiveTestSelect
        cogSel = CognitiveTestSelect(test_type='')
        resp = cogSel.call()


    def test_cognitive_record_performance(self):
        from RappCloud import CognitiveRecordPerformance
        cogRec = CognitiveRecordPerformance(
            test_instance='ReasoningCts_rlvFJyrl',
            score="100"
            )
        resp = cogRec.call()


    def test_cognitive_get_history(self):
        from RappCloud import CognitiveGetHistory
        cog = CognitiveGetHistory(test_type='', time_from=0, time_to=10000000)
        resp = cog.call()


    def test_cognitive_get_scores(self):
        from RappCloud import CognitiveGetScores
        cog = CognitiveGetScores(test_type='', time_to=10000000)
        resp = cog.call()


    def test_email_send(self):
        from RappCloud import EmailSend
        attachPath = path.join(testdatadir, 'Lenna.png')
        svc = EmailSend(
            email='glagloui@gmail.com',
            password='',
            server='smtp.gmail.com',
            port='587',
            recipients=['glagloui@gmail.com', 'klpanagi@gmail.com'],
            body='Rapp Send Email Test',
            subject='Rapp Send Email Test',
            attach_file=attachPath)
        resp = svc.call()


    def test_email_fetch(self):
        from RappCloud import EmailFetch
        svc = EmailFetch(
            email='glagloui@gmail.com',
            password='',
            server='imap.gmail.com',
            port='',
            date_from=0,
            date_to=100000000,
            email_status='',
            num_emails=1
            )
        resp = svc.call()


    def test_news_explore(self):
        from RappCloud import NewsExplore
        ne = NewsExplore(num_news=25)
        resp = ne.call()


    def test_geolocation(self):
        from RappCloud import Geolocation
        ne = Geolocation()
        ne.ipaddr = '155.207.33.180'
        resp = ne.call()


    def test_weather_report_current(self):
        from RappCloud import WeatherReportCurrent
        wr = WeatherReportCurrent(city='Athens')
        resp = wr.call()



    def test_weather_report_forecast(self):
        from RappCloud import WeatherReportForecast
        wr = WeatherReportForecast(city='Athens')
        resp = wr.call()


    def test_object_recognition(self):
        from RappCloud import ObjectRecognition
        imagepath = path.join(testdatadir, 'Lenna.png')
        objectDet = ObjectRecognition(image=imagepath)
        resp = objectDet.call()


    def test_hazard_detection_light_check(self):
        from RappCloud import HazardDetectionLightCheck
        imagepath = path.join(testdatadir, 'Lenna.png')
        hazardDet = HazardDetectionLightCheck(image=imagepath)
        resp = hazardDet.call()



    def test_hazard_detection_door_check(self):
        from RappCloud import HazardDetectionDoorCheck
        imagepath = path.join(testdatadir, 'Lenna.png')
        hazardDet = HazardDetectionDoorCheck(image=imagepath)
        resp = hazardDet.call()


    def test_path_planning_upload_map(self):
        from RappCloud import PathPlanningUploadMap
        yamlFile = path.join(testdatadir, 'Lenna.png')
        pngFile = path.join(testdatadir, 'Lenna.png')
        ppUpMap = PathPlanningUploadMap(map_name='mitsos')
        ppUpMap.png_file = pngFile
        ppUpMap.yaml_file = yamlFile
        resp = ppUpMap.call()


    def test_path_planning_plan2d(self):
        from RappCloud import PathPlanningPlan2D
        ppUpMap = PathPlanningPlan2D(
            map_name='mitsos',
            robot_type='NAO')
        resp = ppUpMap.call()




if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(TestServiceCalls)
    unittest.TextTestRunner(verbosity=0).run(suite)
