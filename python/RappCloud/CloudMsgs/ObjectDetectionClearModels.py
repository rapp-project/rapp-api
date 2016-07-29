from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class ObjectDetectionClearModels(CloudMsg):
    """ Object Detection - Clear Models CloudMsg object"""

    class Request(CloudRequest):
        """ Object Detection - Clear Models Cloud Request object. ObjectDetectionClearModels.Request """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
            """

            # Apply passed keyword arguments to the Request object.
            super(ObjectDetectionClearModels.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload()

        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return []


    class Response(CloudResponse):
        """ Object Detection - Clear Models Cloud Response object. ObjectDetectionClearModels.Response """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref result
            """

            ## Error message
            self.error = ''
            ## Error code
            self.result = 0
            ## Apply passed keyword arguments to the Request object.
            super(ObjectDetectionClearModels.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
        """

        # Create and hold the Request object for this CloudMsg
        self.req = ObjectDetectionClearModels.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = ObjectDetectionClearModels.Response()
        super(ObjectDetectionClearModels, self).__init__(svcname='object_detection_clear_models', **kwargs)


