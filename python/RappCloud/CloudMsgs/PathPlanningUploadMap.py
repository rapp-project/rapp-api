from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class PathPlanningUploadMap(CloudMsg):
    """ Path Planning Upload Map Cloud Message object"""

    class Request(CloudRequest):
        """ Path Planning Upload Map Cloud Request object.

        PathPlanningUploadMap.Request
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref map_name
                - @ref png_file
                - @ref yaml_file
            """

            ## The map name.
            self.map_name = ''
            ## Path to the map image png file.
            self.png_file = ''
            ## Path to the map description yaml file.
            self.yaml_file = ''
            super(PathPlanningUploadMap.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(map_name=self.map_name)


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return [
                File(self.png_file, 'png_file'),
                File(self.yaml_file, 'yaml_file')]


    class Response(CloudResponse):
        """ Path Planning Upload Map Cloud Response object.

        PathPlanningUploadMap.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
            """

            ## Error message
            self.error = ''
            super(PathPlanningUploadMap.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
            - @ref Request.map_name
            - @ref Request.png_file
            - @ref Request.yaml_file
        """

        # Create and hold the Request object for this CloudMsg
        self.req = PathPlanningUploadMap.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = PathPlanningUploadMap.Response()
        super(PathPlanningUploadMap, self).__init__(
            svcname='path_planning_upload_map', **kwargs)


