from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class SetNoiseProfile(CloudMsg):
    """ Set Noise Profile Cloud Message object """

    class Request(CloudRequest):
        """ Set Noise Profile Cloud Request object.

        SetNoiseProfile.Request
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref audio_source
                - @ref audiofile
            """

            ##  Audio source data format. e.g "nao_wav_1_ch".
            self.audio_source = ''
            ## Path to the audio file.
            self.audiofile = ''

            super(SetNoiseProfile.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(audio_source = self.audio_source)


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return [File(self.audiofile, postfield='file')]


    class Response(CloudResponse):
        """ Set Noise Profile Cloud Response object.

        SetNoiseProfile.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
            """

            ## Error message.
            self.error = ''
            super(SetNoiseProfile.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
            - @ref Request.audio_source
            - @ref Request.audiofile
        """

        # Create and hold the Request object for this CloudMsg
        self.req = SetNoiseProfile.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = SetNoiseProfile.Response()
        super(SetNoiseProfile, self).__init__(
            svcname='set_noise_profile', **kwargs)


