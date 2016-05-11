from RappCloud.Objects import (
    File,
    Payload)

from CloudObjects.py import (
    CloudObject,
    CloudRequest,
    CloudResponse)


class FaceDetection(CloudObject):

    class Request(CloudRequest):
        def __init__(self, **kwargs):
            self.image = ''
            self.fast = False
            super(Request, self).__init__(**kwargs)


        def make_payload(self):
            return Payload()

        def make_files(self):
            return [File(self.image, postfield='file')]


    class Response(CloudResponse):
        def __init__(self, **kwargs):
            self.qr_centers = {}
            self.qr_messages = {}
            self.error = ''
            super(Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        self.req = FaceDetection.Request()
        self.resp = FaceDetection.Response()
        self._svcname = 'qr_detection'
        super(FaceDetection, self).__init__(**kwargs)


