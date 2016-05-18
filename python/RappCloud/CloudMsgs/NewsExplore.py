from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class NewsExplore(CloudMsg):
    """ NewsExplore Cloud Message object """

    class Request(CloudRequest):
        """ News Explore Cloud Request object.

        NewsExplore.Request
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref news_engine
                - @ref keywords
                - @ref exclude_titles
                - @ref region
                - @ref topic
                - @ref num_news
            """

            ## The news search engine to use.
            self.news_engine = ''
            ## Desired keywords.
            self.keywords = []
            ## Reject list of previously read articles, in order to avoid duplicates.
            self.exclude_titles = []
            ## Language/Region.
            self.region = ''
            ## Main topics, i.e. sports, politics, etc.
            self.topic = ''
            ## Number of news stories.
            self.num_news = 0

            super(NewsExplore.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(
                news_engine=self.news_engine,
                keywords=self.keywords,
                exclude_titles=self.exclude_titles,
                region=self.region,
                topic=self.topic,
                num_news=self.num_news)


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return []


    class Response(CloudResponse):
        """ News Explore Cloud Response object.

        NewsExplore.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
            """

            ## Error message
            self.error = ''
            ## Array of story objects, where story is of structure:
            # { title: '', content: '', puplisher: '', publishedDate: '', url: '' }
            self.news_stories = []
            super(NewsExplore.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword argumen.ts. Apply values to the request attributes.
            - @ref Request.news_engine
            - @ref Request.keywords
            - @ref Request.exclude_titles
            - @ref Request.region
            - @ref Request.topic
            - @ref Request.num_news
        """

        # Create and hold the Request object for this CloudMsg
        self.req = NewsExplore.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = NewsExplore.Response()
        super(NewsExplore, self).__init__(svcname='news_explore', **kwargs)


