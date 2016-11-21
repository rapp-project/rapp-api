from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class SpeechRecognitionSphinx(CloudMsg):
    """ Speech Recognition Sphinx4 Cloud Message object """

    class Request(CloudRequest):
        """ Speech Recognition Sphinx4 Cloud Request object.
        SpeechRecognitionSphinx.Request
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref audio_source
                - @ref audiofile
                - @ref language
                - @ref words
                - @ref sentences
                - @ref grammar
            """

            ## Language to use for recognition
            self.language = ''
            ##  Audio source data format. e.g "nao_wav_1_ch".
            self.audio_source = ''
            ## A vector that carries the words to recognize.
            self.words = []
            ## The under consideration sentences.
            self.sentences = []
            ## Grammar to use
            self.grammar = []
            ## Path to the audio file.
            self.audiofile = ''

            super(SpeechRecognitionSphinx.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(
                language=self.language,
                audio_source = self.audio_source,
                words=self.words,
                sentences=self.sentences,
                grammar=self.grammar)


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return [File(self.audiofile, postfield='file')]


    class Response(CloudResponse):
        """ Speech Recognition Sphinx4 Cloud Response object.
        SpeechRecognitionSphinx.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref words
            """

            ## Recognized words.
            self.words = []
            ## Error message.
            self.error = ''
            super(SpeechRecognitionSphinx.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
            - @ref Request.audio_source
            - @ref Request.audiofile
            - @ref Request.language
            - @ref Request.words
            - @ref Request.sentences
            - @ref Request.grammar
        """

        # Create and hold the Request object for this CloudMsg
        self.req = SpeechRecognitionSphinx.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = SpeechRecognitionSphinx.Response()
        super(SpeechRecognitionSphinx, self).__init__(
            svcname='speech_detection_sphinx4', **kwargs)


