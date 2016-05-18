from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class HumanDetection(CloudMsg):
    """ Human Detection Cloud Message object"""

    class Request(CloudRequest):
        """ Human Detection Cloud Request object. HumanDetection.Request """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref imageFilepath
            """
            ## File path to the image to load. This is the image to perform
            # qr-detection on.
            self.imageFilepath = ''
            super(HumanDetection.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload()


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return [File(self.imageFilepath, postfield='file')]


    class Response(CloudResponse):
        """ Human Detection Cloud Response object. HumanDetection.Response """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref humans
            """

            ## Error message
            self.error = ''
            ## Array of detected humans
            # TODO Create human objects
            self.humans = []
            super(HumanDetection.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
            - @ref Request.imageFilepath
        """

        # Create and hold the Request object for this CloudMsg
        self.req = HumanDetection.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = HumanDetection.Response()
        super(HumanDetection, self).__init__(svcname='human_detection', **kwargs)


