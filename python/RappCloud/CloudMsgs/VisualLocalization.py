from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class VisualLocalization(CloudMsg):
    """ Visual Localization CloudMsg object"""

    class Request(CloudRequest):
        """ Visual Localization Cloud Request object. ObjectDetectionFindObjects.Request """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref fname
                - @ref pose_delta
                - @ref id
            """

            ## File path to the image to load. This is the image to perform
            # object detection on.
            self.fname = ''
            # pose delta
            self.pose_delta = {"x": 0, "y": 0, "theta": 0}
            ## Limit results to this number of objects
            self.id = 0
            # Apply passed keyword arguments to the Request object.
            super(VisualLocalization.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(pose_delta=self.pose_delta, id=self.id)

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
                - @ref belief
                - @ref best_pose
                - @ref status
            """

            ## Error message
            self.error = ''
            ## Detected object names. 
            self.belief = 0
            ## Detected object centers. 
            self.best_pose = {"x": 0, "y": 0, "theta": 0}
            ## Detected object scores. 
            self.status = 0
            ## Apply passed keyword arguments to the Request object.
            super(VisualLocalization.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
          - @ref Request.pose_delta
          - @ref Request.fname
          - @ref Request.id
        """

        # Create and hold the Request object for this CloudMsg
        self.req = VisualLocalization.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = VisualLocalization.Response()
        super(VisualLocalization, self).__init__(svcname='visual_localization', **kwargs)


