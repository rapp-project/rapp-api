from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class ObjectRecognitionCaffe(CloudMsg):
    """ Object Recognition Cloud Message object"""

    class Request(CloudRequest):
        """ Object Recognition (Caffe) Cloud Request object.

        ObjectRecognitionCaffe.Request
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref imageFilepath
            """
            ## File path to the image to load. This is the image to perform
            # qr-detection on.
            self.imageFilepath = ''
            super(ObjectRecognitionCaffe.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload()


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return [File(self.imageFilepath, postfield='file')]


    class Response(CloudResponse):
        """ Object Recognition (Caffe) Cloud Response object.

        ObjectRecognitionCaffe.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref object_class
            """

            ## Error message
            self.error = ''
            ## Recognized object class.
            self.object_class = ''
            super(ObjectRecognitionCaffe.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
            - @ref Request.imageFilepath
        """

        # Create and hold the Request object for this CloudMsg
        self.req = ObjectRecognitionCaffe.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = ObjectRecognitionCaffe.Response()
        super(ObjectRecognitionCaffe, self).__init__(
            svcname='object_recognition_caffe', **kwargs)


