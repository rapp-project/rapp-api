from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class ObjectDetectionLoadModels(CloudMsg):
    """ Object Detection - Load Models CloudMsg object"""

    class Request(CloudRequest):
        """ Object Detection - Load Models Cloud Request object. ObjectDetectionLoadModels.Request """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref names
            """

            ## Model names to be loaded
            self.names = []
            # Apply passed keyword arguments to the Request object.
            super(ObjectDetectionLoadModels.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(names=self.names)

        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return []


    class Response(CloudResponse):
        """ Object Detection - Load Models Cloud Response object. ObjectDetectionLoadModels.Response """
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
            super(ObjectDetectionLoadModels.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
          - @ref Request.names
        """

        # Create and hold the Request object for this CloudMsg
        self.req = ObjectDetectionLoadModels.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = ObjectDetectionLoadModels.Response()
        super(ObjectDetectionLoadModels, self).__init__(svcname='object_detection_load_models', **kwargs)


