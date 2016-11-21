from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class OntologyIsSubsuperclass(CloudMsg):
    """ Ontology Is Sub-Superclass Of Cloud Message object"""

    class Request(CloudRequest):
        """ Ontology Is Sub-Superclass Of Cloud Request object.

        OntologyIsSubsuperclass.Request
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref parent_class
                - @ref child_class
                - @ref recursive
            """

            ## The ontology parent class name.
            # e.g. 'Oven'
            self.parent_class = ''
            ## The ontology child class name.
            # e.g. 'Microwave'
            self.child_class = ''
            ## Recursive ontology database search.
            self.recursive = False
            super(OntologyIsSubsuperclass.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(
                parent_class=self.parent_class,
                child_class=self.child_class,
                recursive=self.recursive)


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return []


    class Response(CloudResponse):
        """ Ontology Is Sub-Superclass Cloud Response object.

        OntologyIsSubsuperclass.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref result
            """

            ## Error message
            self.error = ''
            ## Success index on ontology-is-subsuperclass-of query.
            self.result = False
            super(OntologyIsSubsuperclass.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
            - @ref Request.parent_class
            - @ref Request.child_class
            - @ref Request.recursive
        """

        # Create and hold the Request object for this CloudMsg
        self.req = OntologyIsSubsuperclass.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = OntologyIsSubsuperclass.Response()
        super(OntologyIsSubsuperclass, self).__init__(
            svcname='ontology_is_subsuperclass_of', **kwargs)


