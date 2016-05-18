from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class WeatherReportForecast(CloudMsg):
    """ Weather Report Forecast Cloud Message object """

    class Request(CloudRequest):
        """ Weather Report Forecast Cloud Request object.

        WeatherReportForecast.Request
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
            super(WeatherReportForecast.Request, self).__init__(**kwargs)


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
        """ Weather Report Forecast Cloud Response object.

        WeatherReportForecast.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref forecast
            """

            ## Error message
            self.error = ''
            ## Array of forecastEntry objects, where forecastEntry is of structure:
            # {high_temp: '', low_temp: '', description: '', date: ''}
            self.forecast = []
            super(WeatherReportForecast.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword argumen.ts. Apply values to the request attributes.
            - @ref Request.city
            - @ref Request.weather_reporter
            - @ref Request.metric
        """

        # Create and hold the Request object for this CloudMsg
        self.req = WeatherReportForecast.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = WeatherReportForecast.Response()
        super(WeatherReportForecast, self).__init__(
            svcname='weather_report_forecast', **kwargs)


