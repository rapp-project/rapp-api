from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class Geolocation(CloudMsg):
    """ Geolocation Cloud Message object """

    class Request(CloudRequest):
        """ Geolocation Cloud Request object.

        Geolocation.Request
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref ipaddr
                - @ref engine
            """

            ## The machine's ipv4 address.
            self.ipaddr = ''
            ## Engine to use. Defaults to 'ip-api' (Currently the only supported).
            self.engine = ''
            super(Geolocation.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(
                ipaddr=self.ipaddr,
                engine=self.engine)


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return []


    class Response(CloudResponse):
        """ Geolocation Cloud Response object.

        Geolocation.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref city
                - @ref country
                - @ref country_code
                - @ref latitude
                - @ref longtitude
                - @ref timezone
                - @ref zip
            """

            ## Error message
            self.error = ''
            ## City location
            self.city = ''
            ## Country location
            self.country = ''
            ## Location's country code
            self.country_code = ''
            ## The latitude
            self.latitude = 0.0
            ## The longtitude
            self.longtitude = 0.0
            ## Location region
            self.region = ''
            ## Location timezone
            self.timezone = ''
            ## Location zip-postal code
            self.zip = ''
            super(Geolocation.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword argumen.ts. Apply values to the request attributes.
            - @ref Request.ipaddr
            - @ref Request.engine
        """

        # Create and hold the Request object for this CloudMsg
        self.req = Geolocation.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = Geolocation.Response()
        super(Geolocation, self).__init__(svcname='geolocation', **kwargs)


