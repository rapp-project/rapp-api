from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class VisualLocalizationInit(CloudMsg):
    """ Visual Localization Init CloudMsg object"""

    class Request(CloudRequest):
        """ Visual Localization Init Cloud Request object. ObjectDetectionFindObjects.Request """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref map
            """

            ## File path to the image to load. This is the image to perform
            # object detection on.
            self.map = ''
            # Apply passed keyword arguments to the Request object.
            super(VisualLocalizationInit.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(map=self.map)

        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return []


    class Response(CloudResponse):
        """ Object Detection - Find Objects Cloud Response object. ObjectDetectionFindObjects.Response """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref id
            """

            ## Error message
            self.id = 0
            self.error = ''
            ## Apply passed keyword arguments to the Request object.
            super(VisualLocalizationInit.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
          - @ref Request.map
        """

        # Create and hold the Request object for this CloudMsg
        self.req = VisualLocalizationInit.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = VisualLocalizationInit.Response()
        super(VisualLocalizationInit, self).__init__(svcname='visual_localization_init', **kwargs)


