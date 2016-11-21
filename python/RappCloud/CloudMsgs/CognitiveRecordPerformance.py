from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class CognitiveRecordPerformance(CloudMsg):
    """ Cognitive Record Performance Cloud Message object """

    class Request(CloudRequest):
        """ Cognitive Record Performance Cloud Request object.

        CognitiveRecordPerformance.Request
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref test_instance
                - @ref score
            """

            ## Cognitive Exercise test instance. The full cognitive test entry
            # name as obtained from CognitiveExerciseSelect
            self.test_instance = ''
            ## Performance score to record.
            self.score = 0
            super(CognitiveRecordPerformance.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(
                test_instance=self.test_instance,
                score=self.score)


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return []


    class Response(CloudResponse):
        """ Cognitive Record Performance Cloud Response object.

        CognitiveRecordPerformance.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref performance_entry
            """

            ## Error message
            self.error = ''
            ## Cognitive exercise ontology performance entry.
            self.performance_entry = ''
            super(CognitiveRecordPerformance.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword argumen.ts. Apply values to the request attributes.
            - @ref Request.test_instance
            - @ref Request.score
        """

        # Create and hold the Request object for this CloudMsg
        self.req = CognitiveRecordPerformance.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = CognitiveRecordPerformance.Response()
        super(CognitiveRecordPerformance, self).__init__(
            svcname='cognitive_record_performance', **kwargs)


