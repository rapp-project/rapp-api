from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class OntologySuperclasses(CloudMsg):
    """ Ontology Superclasses Of Cloud Message object"""

    class Request(CloudRequest):
        """ Ontology Superclasses Of Cloud Request object.

        OntologySuperclasses.Request
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
            super(OntologySuperclasses.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(
                ontology_class=self.ontology_class,
                recursive=self.recursive)


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return []


    class Response(CloudResponse):
        """ Ontology Superclasses Cloud Response object.

        OntologySuperclasses.Response
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
            super(OntologySuperclasses.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
            - @ref Request.query
        """

        # Create and hold the Request object for this CloudMsg
        self.req = OntologySuperclasses.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = OntologySuperclasses.Response()
        super(OntologySuperclasses, self).__init__(
            svcname='ontology_superclasses_of', **kwargs)


