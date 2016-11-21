from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class EmailSend(CloudMsg):
    """ Email Send Cloud Message object """

    class Request(CloudRequest):
        """ Email Send Cloud Request object.

        EmailSend.Request
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref email
                - @ref password
                - @ref server
                - @ref port
                - @ref recipients
                - @ref body
                - @ref subject
                - @ref attach_file
            """

            ## The user's email username
            self.email = ''
            ## The user's email password
            self.password = ''
            ## The email server's smtp address, i.e. 'smtp.gmail.com'
            self.server = ''
            ## The email server imap port. Leave empty to use default value.
            self.port = ''
            ## Email addresses of the recipients
            self.recipients = []
            ## The email body
            self.body = ''
            ## The email subject
            self.subject = ''
            ## Attachment file path. Can be a .zip file that will be decompressed on the server.
            self.attach_file = ''

            super(EmailSend.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(
                email=self.email,
                passwd=self.password,
                server=self.server,
                port=self.port,
                recipients=self.recipients,
                body=self.body,
                subject=self.subject
                )


        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            # Check if attachment file has been defined as it is optional
            if self.attach_file != '':
                return [File(self.attach_file, 'file')]
            return []


    class Response(CloudResponse):
        """ Email Send Cloud Response object.

        EmailSend.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
            """

            ## Error message
            self.error = ''
            super(EmailSend.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword argumen.ts. Apply values to the request attributes.
            - @ref Request.email
            - @ref Request.password
            - @ref Request.server
            - @ref Request.port
            - @ref Request.recipients
            - @ref Request.body
            - @ref Request.subject
            - @ref Request.attach_file
        """

        # Create and hold the Request object for this CloudMsg
        self.req = EmailSend.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = EmailSend.Response()
        super(EmailSend, self).__init__(
            svcname='email_send', **kwargs)


