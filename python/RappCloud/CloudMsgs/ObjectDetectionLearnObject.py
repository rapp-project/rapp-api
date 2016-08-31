from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class ObjectDetectionLearnObject(CloudMsg):
    """ Object Detection - Learn Object CloudMsg object"""

    class Request(CloudRequest):
        """ Object Detection - Learn Object Cloud Request object. ObjectDetectionLearnObject.Request """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref fname
                - @ref name
            """

            ## File path to the image to load. This is the sample object image.
            self.fname = ''
            ## Model name
            self.name = ''
            # Apply passed keyword arguments to the Request object.
            super(ObjectDetectionLearnObject.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(name=self.name)

        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return [File(self.fname, postfield='file')]


    class Response(CloudResponse):
        """ Object Detection - Learn Object Cloud Response object. ObjectDetectionLearnObject.Response """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref result
            """

            ## Error message
            self.error = ''
            self.result = 0
            ## Apply passed keyword arguments to the Request object.
            super(ObjectDetectionLearnObject.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
          - @ref Request.fname
          - @ref Request.name
        """

        # Create and hold the Request object for this CloudMsg
        self.req = ObjectDetectionLearnObject.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = ObjectDetectionLearnObject.Response()
        super(ObjectDetectionLearnObject, self).__init__(svcname='object_detection_learn_object', **kwargs)


