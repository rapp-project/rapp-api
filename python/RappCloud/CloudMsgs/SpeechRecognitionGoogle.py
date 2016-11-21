from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class SpeechRecognitionGoogle(CloudMsg):
    """ Speech Recognition Google Cloud Message object """

    class Request(CloudRequest):
        """ Speech Recognition Google  Cloud Request object.

        SpeechRecognitionGoogle.Request
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref audio_source
                - @ref audiofile
                - @ref language
            """

            ## Language to use for recognition
            self.language = ''
            ##  Audio source data format. e.g "nao_wav_1_ch".
            self.audio_source = ''
            ## Path to the audio file.
            self.audiofile = ''

            super(SpeechRecognitionGoogle.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(
                language=self.language,
                audio_source = self.audio_source)


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return [File(self.audiofile, postfield='file')]


    class Response(CloudResponse):
        """ Speech Recognition Google Cloud Response object.

        SpeechRecognitionGoogle.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref words
                - @ref alternatives
            """

            ## An array that contains the "words-found" with highest confidence.
            self.words = []
            ## Alternative sentences.
            # e.g. [['send', 'mail'], ['send', 'email'], ['set', 'mail']...]
            self.alternatives = []
            ## Error message.
            self.error = ''
            super(SpeechRecognitionGoogle.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
            - @ref Request.audio_source
            - @ref Request.audiofile
            - @ref Request.language
        """

        # Create and hold the Request object for this CloudMsg
        self.req = SpeechRecognitionGoogle.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = SpeechRecognitionGoogle.Response()
        super(SpeechRecognitionGoogle, self).__init__(
            svcname='speech_detection_google', **kwargs)


