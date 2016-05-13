from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudObject,
    CloudRequest,
    CloudResponse)


class FaceDetection(CloudObject):
    """ Face Detection Cloud Object """

    class Request(CloudRequest):
        """ Face Detection Cloud Request object. FaceDetection.Request """
        def __init__(self, **kwargs):
            self.image = ''
            self.fast = False
            super(FaceDetection.Request, self).__init__(**kwargs)


        def make_payload(self):
            return Payload(fast=self.fast)

        def make_files(self):
            return [File(self.image, postfield='file')]


    class Response(CloudResponse):
        """ Face Detection Cloud Response object. FaceDetection.Response """
        def __init__(self, **kwargs):
            self.error = ''
            self.faces = []
            super(FaceDetection.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        # Create and hold the Request object for this CloudObject
        self.req = FaceDetection.Request()
        # Create and hold the Response object for this CloudObject
        self.resp = FaceDetection.Response()
        super(FaceDetection, self).__init__(svcname='face_detection', **kwargs)


