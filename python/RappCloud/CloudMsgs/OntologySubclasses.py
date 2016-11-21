from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class OntologySubclasses(CloudMsg):
    """ Ontology Subclasses Of Cloud Message object"""

    class Request(CloudRequest):
        """ Ontology Subclasses Of Cloud Request object.

        OntologySubclasses.Request
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref query
            """
            ## The Ontology class.
            # e.g. 'Oven'
            self.ontology_class = ''
            ## Recursive search.
            self.recursive = False
            super(OntologySubclasses.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(
                ontology_class=self.ontology_class,
                recursive=self.recursive)


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return []


    class Response(CloudResponse):
        """ Ontology Subclasses Cloud Response object.

        OntologySubclasses.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref results
            """

            ## Error message
            self.error = ''
            ## Ontology query results
            self.results = []
            super(OntologySubclasses.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
            - @ref Request.query
        """

        # Create and hold the Request object for this CloudMsg
        self.req = OntologySubclasses.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = OntologySubclasses.Response()
        super(OntologySubclasses, self).__init__(
            svcname='ontology_subclasses_of', **kwargs)


