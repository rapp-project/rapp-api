from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class EmailFetch(CloudMsg):
    """ Email Fetch Cloud Message object """

    class Request(CloudRequest):
        """ Email Fetch Cloud Request object.

        EmailFetch.Request
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref email
                - @ref password
                - @ref server
                - @ref port
                - @ref date_from
                - @ref date_to
                - @ref email_status
                - @ref num_emails
            """

            ## User's email username
            self.email = ''
            ## User's email password
            self.password = ''
            ## The email server's imap address, i.e. 'imap.gmail.com'.
            self.server = ''
            ## The email server imap port. leave empty to use default value.
            self.port = ''
            ## Emails since date. Unix timestamp.
            self.date_from = 0
            ## Emails until date. Unix timestamp.
            self.date_to = 0
            ## Define which mails the users requests. Values: ALL, UNSEEN(DEFAULT)
            self.email_status = ''
            ## Number of requested emails.
            self.num_emails = 0

            super(EmailFetch.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(
                email=self.email,
                passwd=self.password,
                server=self.server,
                port=self.port,
                from_date=self.date_from,
                to_date=self.date_to,
                email_status=self.email_status,
                num_emails=self.num_emails)


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return []


    class Response(CloudResponse):
        """ Email Fetch Cloud Response object.

        EmailFetch.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
                - @ref emails
            """

            ## Error message
            self.error = ''
            ## An array of emailEntry objects, where emailEntry is of structure:
            # {sender: '', receivers: [], date: '', body: '', attachments: []}
            self.emails = []
            super(EmailFetch.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword argumen.ts. Apply values to the request attributes.
            - @ref Request.email
            - @ref Request.password
            - @ref Request.server
            - @ref Request.port
            - @ref Request.date_from
            - @ref Request.date_to
            - @ref Request.email_status
            - @ref Request.num_emails
        """

        # Create and hold the Request object for this CloudMsg
        self.req = EmailFetch.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = EmailFetch.Response()
        super(EmailFetch, self).__init__(
            svcname='email_fetch', **kwargs)


