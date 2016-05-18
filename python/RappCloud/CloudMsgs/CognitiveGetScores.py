from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class CognitiveGetScores(CloudMsg):
    """ Cognitive Get Scores Cloud Message object """

    class Request(CloudRequest):
        """ Cognitive Get Scores Cloud Request object.

        CognitiveGetScores.Request
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref test_type
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
            ## Unix timestamp. Retrieve scores up to this timestamp value.
            self.time_to = 0
            super(CognitiveGetScores.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(
                up_to_time=self.time_to,
                test_type=self.test_type)


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return []


    class Response(CloudResponse):
        """ Cognitive Get Scores Cloud Response object.

        CognitiveGetScores.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref test_classes
                - @ref scores
            """

            ## Error message
            self.error = ''
            ## Array of the test classes indexes.
            self.test_classes = []
            ## Array of scores. Each array index corresponds to the test class
            # in @ref test_classes
            self.scores = []
            super(CognitiveGetScores.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword argumen.ts. Apply values to the request attributes.
            - @ref Request.test_type
            - @ref Request.time_to
        """

        # Create and hold the Request object for this CloudMsg
        self.req = CognitiveGetScores.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = CognitiveGetScores.Response()
        super(CognitiveGetScores, self).__init__(
            svcname='cognitive_get_scores', **kwargs)


