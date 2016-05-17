from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class QrDetection(CloudMsg):
    """ Qr Detection Cloud Message object"""

    class Request(CloudRequest):
        """ Qr Detection Cloud Request object. QrDetection.Request """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref imageFilepath
            """
            ## File path to the image to load. This is the image to perform
            # qr-detection on.
            self.imageFilepath = ''
            super(QrDetection.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload()

        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return [File(self.imageFilepath, postfield='file')]


    class Response(CloudResponse):
        """ Qr Detection Cloud Response object. QrDetection.Response """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref qr_centers
                - @ref qr_messages
            """

            ## Error message
            self.error = ''
            ## Found qr centers. Array of qr_center objects.
            # TODO Create qr_center objects
            self.qr_centers = []
            ## Found qr messages. Array of strings.
            self.qr_messages = []
            super(QrDetection.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
            - @ref Request.imageFilepath
        """

        # Create and hold the Request object for this CloudMsg
        self.req = QrDetection.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = QrDetection.Response()
        super(QrDetection, self).__init__(svcname='qr_detection', **kwargs)


