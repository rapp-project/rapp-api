from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudObject,
    CloudRequest,
    CloudResponse)


class FaceDetection(CloudObject):

    class Request(CloudRequest):
        def __init__(self, **kwargs):
            self.image = ''
            self.fast = False
            super(FaceDetection.Request, self).__init__(**kwargs)


        def make_payload(self):
            return Payload(fast=self.fast)

        def make_files(self):
            return [File(self.image, postfield='file')]


    class Response(CloudResponse):
        def __init__(self, **kwargs):
            self.error = ''
            self.faces = []
            super(FaceDetection.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        self.req = FaceDetection.Request()
        self.resp = FaceDetection.Response()
        self._svcname = 'face_detection'
        super(FaceDetection, self).__init__(**kwargs)


