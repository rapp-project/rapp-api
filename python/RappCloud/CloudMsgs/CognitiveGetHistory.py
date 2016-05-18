from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class CognitiveGetHistory(CloudMsg):
    """ Cognitive Get History Cloud Message object """

    class Request(CloudRequest):
        """ Cognitive Get History Cloud Request object.

        CognitiveGetHistory.Request
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref test_type
                - @ref time_from
                - @ref time_to
            """

            ## Cognitive Exercise test type. Can be one of:
            # - 'ArithmeticCts'
            # - 'AwarenessCts'
            # - 'ReasoningCts'
            # - ''
            #
            # If left empty, history of all test types will be returned.
            self.test_type = ''
            ## Unix timestamp.
            self.time_from = 0
            ## Unix timestamp.
            self.time_to = 0
            super(CognitiveGetHistory.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(
                from_time=self.time_from,
                to_time=self.time_to,
                test_type=self.test_type)


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return []


    class Response(CloudResponse):
        """ Cognitive Get History Cloud Response object.

        CognitiveGetHistory.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref records
            """

            ## Error message
            self.error = ''
            ## Users history records.
            self.records = {}
            super(CognitiveGetHistory.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword argumen.ts. Apply values to the request attributes.
            - @ref Request.test_type
            - @ref Request.time_from
            - @ref Request.time_to
        """

        # Create and hold the Request object for this CloudMsg
        self.req = CognitiveGetHistory.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = CognitiveGetHistory.Response()
        super(CognitiveGetHistory, self).__init__(
            svcname='cognitive_get_history', **kwargs)


