from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class ObjectDetectionFindObjects(CloudMsg):
    """ Object Detection - Find Objects CloudMsg object"""

    class Request(CloudRequest):
        """ Object Detection - Find Objects Cloud Request object. ObjectDetectionFindObjects.Request """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref imageFilepath
                - @ref fast
            """

            ## File path to the image to load. This is the image to perform
            # object detection on.
            self.fname = ''
            ## Limit results to this number of objects
            self.limit = 1
            ## Username 
            self.user = 'rapp'
            # Apply passed keyword arguments to the Request object.
            super(ObjectDetectionFindObjects.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(limit=self.limit,user=self.user)

        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return [File(self.fname, postfield='file')]


    class Response(CloudResponse):
        """ Object Detection - Find Objects Cloud Response object. ObjectDetectionFindObjects.Response """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref found_names
                - @ref found_centers
                - @ref found_scores
                - @ref result
            """

            ## Error message
            self.error = ''
            ## Detected object names. 
            self.found_names = []
            ## Detected object centers. 
            self.found_centers = []
            ## Detected object scores. 
            self.found_scores = []
            ## Error code
            self.result = 0
            ## Apply passed keyword arguments to the Request object.
            super(ObjectDetectionFindObjects.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
          - @ref Request.limit
          - @ref Request.fname
          - @ref Request.user
        """

        # Create and hold the Request object for this CloudMsg
        self.req = ObjectDetectionFindObjects.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = ObjectDetectionFindObjects.Response()
        super(ObjectDetectionFindObjects, self).__init__(svcname='object_detection_find_objects', **kwargs)


