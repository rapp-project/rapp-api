#!/usr/bin/env python


# Copyright 2016 RAPP

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

    #http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Authors: Konstantinos Panayiotou
# contact: klpanagi@gmail.com


## @file RappCloud/CloudServices/EmailSend.py
#
#  @copyright Rapp Projecty EU 2016
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


from Service import *
from RappCloud.Objects import (
    File,
    Payload
    )


class EmailSend(Service):
  """ EmailSend Cloud Service class """

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

    # Cloud Service request arguments
    # -------------------------------------------------------------
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
    ## The email body string
    self.body = ''
    ## The email subject string
    self.subject = ''
    ## Attachment file path. Can be a .zip file that will be decompressed on the server.
    self.attach_file = ''
    # -------------------------------------------------------------

    super(EmailSend, self).__init__(
        svcname='email_send',
        **kwargs
        )


  def _make_payload(self):
    """ Make request payload object """
    return Payload(
        email=self.email,
        passwd=self.password,
        server=self.server,
        port=self.port,
        recipients=self.recipients,
        body=self.body,
        subject=self.subject
        )


  def _make_files(self):
    """ Create array of file object(s) """
    return [File(self.attach_file, 'file')]
