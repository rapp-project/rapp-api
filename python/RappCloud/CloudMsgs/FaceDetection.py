from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class FaceDetection(CloudMsg):
    """ Face Detection CloudMsg object"""

    class Request(CloudRequest):
        """ Face Detection Cloud Request object. FaceDetection.Request """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref imageFilepath
                - @ref fast
            """

            ## File path to the image to load. This is the image to perform
            # face-detection on.
            self.imageFilepath = ''
            ## If true, detection will take less time but it will be less
            # accurate
            self.fast = False
            # Apply passed keyword arguments to the Request object.
            super(FaceDetection.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(fast=self.fast)

        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return [File(self.imageFilepath, postfield='file')]


    class Response(CloudResponse):
        """ Face Detection Cloud Response object. FaceDetection.Response """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref faces
            """

            ## Error message
            self.error = ''
            ## Detected faces. Array of face objects. TODO create face object.
            self.faces = []
            ## Apply passed keyword arguments to the Request object.
            super(FaceDetection.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
          - @ref Request.fast
          - @ref Request.imageFilepath
        """

        # Create and hold the Request object for this CloudMsg
        self.req = FaceDetection.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = FaceDetection.Response()
        super(FaceDetection, self).__init__(svcname='face_detection', **kwargs)


