from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class WeatherReportCurrent(CloudMsg):
    """ Weather Report Current Cloud Message object """

    class Request(CloudRequest):
        """ Weather Report Current Cloud Request object.

        WeatherReportCurrent.Request
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref city
                - @ref weather_reporter
                - @ref metric
            """

            ## The desired city
            self.city = ''
            ## The weather API to use. Defaults to "yweather" .
            self.weather_reporter = ''
            ## The return value units.
            self.metric = 0
            super(WeatherReportCurrent.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(
                city=self.city,
                weather_reporter=self.weather_reporter,
                metric=self.metric
                )


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return []


    class Response(CloudResponse):
        """ Weather Report Current Cloud Response object.

        WeatherReportCurrent.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref date
                - @ref temperature
                - @ref weather_description
                - @ref humidity
                - @ref visibility
                - @ref pressure
                - @ref wind_speed
                - @ref wind_temperature
                - @ref wind_direction
            """

            ## Error message
            self.error = ''
            ## Current date
            self.date = ''
            ## Current temperature
            self.temperature = ''
            ## A brief description of the current weather
            self.weather_description = ''
            ## Current humidity
            self.humidity = ''
            ## Current vilibility
            self.visibility = ''
            ## Current pressure
            self.pressure = ''
            ## Current speed of the wind
            self.wind_speed = ''
            ## Current temperature of the wind
            self.wind_temperature = ''
            ## Current wind direction
            self.wind_direction = ''
            super(WeatherReportCurrent.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword argumen.ts. Apply values to the request attributes.
            - @ref Request.city
            - @ref Request.weather_reporter
            - @ref Request.metric
        """

        # Create and hold the Request object for this CloudMsg
        self.req = WeatherReportCurrent.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = WeatherReportCurrent.Response()
        super(WeatherReportCurrent, self).__init__(
            svcname='weather_report_current', **kwargs)


