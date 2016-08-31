from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class CognitiveExerciseSelect(CloudMsg):
    """ Cognitive Exercise Select Cloud Message object

    For more information on available exercises have a look at:
        https://github.com/rapp-project/rapp-platform/tree/master/rapp_cognitive_exercise
    """

    class Request(CloudRequest):
        """ Cognitive Exercise Select Cloud Request object.

        CognitiveExerciseSelect.Request
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref test_type
                - @ref test_subtype
                - @ref test_diff
                - @ref test_index
            """

            ## Cognitive Exercise test type. Can be one of:
            # - 'ArithmeticCts'
            # - 'AwarenessCts'
            # - 'ReasoningCts'
            # - ''
            #
            # If left empty, selection will be performed based on user's past
            # performance records.
            self.test_type = ''
            ## Force select from this subtype. Defaults to empty string ""
            self.test_subtype = ''
            ## Force select from this difficulty. Defaults to empty string ""
            self.test_diff = ''
            ## Force select this index. Defaults to empty string "".
            self.test_index = ''
            # { test_type: 'Arithmetic', test_subtype: 'BasicArithmetic', test_diff: '1', test_index: '1' }
            super(CognitiveExerciseSelect.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(
                test_type=self.test_type,
                test_subtype=self.test_subtype,
                test_diff=self.test_diff,
                test_index=self.test_index)


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return []


    class Response(CloudResponse):
        """ Cognitive Exercise Select Cloud Response object.

        CognitiveExerciseSelect.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref questions
                - @ref possib_ans
                - @ref correct_ans
                - @ref test_instance
                - @ref test_type
                - @ref test_subtype
                - @ref language
            """

            ## Error message
            self.error = ''
            ## The set of questions for the exercise
            self.questions = []
            ## The set of possible answers for each question.
            self.possib_ans = []
            ## The set of correct answers for each question.
            self.correct_ans = []
            ## Returned test instance name.
            # e.g. 'ArithmeticCts_askw0Snwk'
            self.test_instance = ''
            ## Cognitive exercise class/type.
            self.test_type = ''
            ## Cognitive exercise sub-type.
            self.test_subtype = ''

            ## Language
            self.lang = ''
            super(CognitiveExerciseSelect.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword argumen.ts. Apply values to the request attributes.
            - @ref Request.test_type
            - @ref Request.test_subtype
            - @ref Request.test_diff
            - @ref Request.test_index
        """

        # Create and hold the Request object for this CloudMsg
        self.req = CognitiveExerciseSelect.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = CognitiveExerciseSelect.Response()
        super(CognitiveExerciseSelect, self).__init__(
            svcname='cognitive_test_chooser', **kwargs)


