from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class HazardDetectionLight(CloudMsg):
    """ Hazard Detection Light Check Cloud Message object"""

    class Request(CloudRequest):
        """ Hazard Detection Light Check Cloud Request object.

        HazardDetectionLight.Request
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
            super(HazardDetectionLight.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload()


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return [File(self.imageFilepath, postfield='file')]


    class Response(CloudResponse):
        """ Hazard Detection Light Check Cloud Response object.

        HazardDetectionLight.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref light_level
            """

            ## Error message
            self.error = ''
            ## The, detected on the image frame, light level.
            self.light_level = 0.0
            super(HazardDetectionLight.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
            - @ref Request.imageFilepath
        """

        # Create and hold the Request object for this CloudMsg
        self.req = HazardDetectionLight.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = HazardDetectionLight.Response()
        super(HazardDetectionLight, self).__init__(
            svcname='hazard_detection_light_check', **kwargs)


