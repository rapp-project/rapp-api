from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class UserPersonalInfo(CloudMsg):
    """ Ontology Is Sub-Superclass Of Cloud Message object"""

    class Request(CloudRequest):
        """ User Personal Info Cloud Request object.

        UserPersonalInfo.Request
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
            """

            super(UserPersonalInfo.Request, self).__init__(**kwargs)

        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload()

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
                - @ref name
                - @ref surname
                - @ref language
                - @ref emails
            """

            ## Error message
            self.error = ''
            ## User's name
            self.name = ''
            ## User's surname
            self.surname = ''
            ## User's language
            self.language = ''
            ## User's registered destination email addresses
            self.emails = []
            super(UserPersonalInfo.Response, self).__init__(**kwargs)

    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
        """

        # Create and hold the Request object for this CloudMsg
        self.req = UserPersonalInfo.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = UserPersonalInfo.Response()
        super(UserPersonalInfo, self).__init__(
            svcname='user_personal_info', **kwargs)
