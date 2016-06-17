from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)

import base64
from os import path


class TextToSpeech(CloudMsg):
    """ Text-To-Speech (TTS) Cloud Message object"""

    class Request(CloudRequest):
        """ Text-To-Speech (TTS) Cloud Request object.

        TextToSpeech.Request
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref text
                - @ref language
            """

            ## Input text to translate to audio data
            self.text = ''
            ## Language to use for translation.
            # Valid values are currently:
            # - 'el'
            # - 'en'
            self.language = ''
            super(TextToSpeech.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(
                text=self.text,
                language=self.language
                )



        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return []


    class Response(CloudResponse):
        """ Text-To-Speech (TTS) Cloud Response object.

        TextToSpeech.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref payload
                - @ref encoding
                - @ref basename
            """

            ## Error message
            self.error = ''
            ## The audio data payload. Payload encoding is defined by the
            # 'encoding' json field.
            self.payload = ''
            ## Codec used to encode the audio data payload.
            self.encoding = ''
            ## A static basename for the audio data file, returned from the
            # platform service. Ignore this field.
            # May be usefull in future implementations.
            self.basename = ''
            super(TextToSpeech.Response, self).__init__(**kwargs)


        def get_audio_raw(self):
            """! Get audio raw data from response """
            b64Data = self.payload
            rawData = base64.b64decode(b64Data)
            return rawData


        def store_audio(self, destfile):
            """! Store returned audio data to an audio file given by path

            @param destfile - Destination file path.
            """

            if destfile == '' or destfile == u'':
                raise ValueError('Empty destination file path {destfile} given')

            destAbs = path.expanduser(path.realpath(destfile))
            rawData = self.get_audio_raw()
            with open(destAbs, 'wb') as f:
                f.write(rawData)



    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
            - @ref Request.text
            - @ref Request.language
        """

        # Create and hold the Request object for this CloudMsg
        self.req = TextToSpeech.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = TextToSpeech.Response()
        super(TextToSpeech, self).__init__(
            svcname='text_to_speech', **kwargs)

