from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class HazardDetectionDoor(CloudMsg):
    """ Hazard Detection Light Check Cloud Message object"""

    class Request(CloudRequest):
        """ Hazard Detection Door Check Cloud Request object.

        HazardDetectionDoor.Request
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
            super(HazardDetectionDoor.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload()


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return [File(self.imageFilepath, postfield='file')]


    class Response(CloudResponse):
        """ Hazard Detection Door Check Cloud Response object.

        HazardDetectionDoor.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref door_angle
            """

            ## Error message.
            self.error = ''
            ## The angle of the detected door.
            self.door_angle = 0.0
            super(HazardDetectionDoor.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
            - @ref Request.imageFilepath
        """

        # Create and hold the Request object for this CloudMsg
        self.req = HazardDetectionDoor.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = HazardDetectionDoor.Response()
        super(HazardDetectionDoor, self).__init__(
            svcname='hazard_detection_door_check', **kwargs)


