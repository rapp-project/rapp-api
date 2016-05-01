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


## @file RappCloud/CloudServices/EmailFetch.py
#
#  @copyright Rapp Projecty EU 2016
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


from Service import *
from RappCloud.Objects import (
    File,
    Payload
    )


class EmailFetch(Service):
  """ EmailFetch Cloud Service class. """

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

    # Cloud Service request arguments
    # -------------------------------------------------------------
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
    # -------------------------------------------------------------

    super(EmailFetch, self).__init__(
        svcname='email_fetch',
        **kwargs
        )


  def _make_payload(self):
    """ Make request payload object """
    return Payload(
        email=self.email,
        passwd=self.password,
        server=self.server,
        port=self.port,
        from_date=self.date_from,
        to_date=self.date_to,
        email_status=self.email_status,
        num_emails=self.num_emails)


  def _make_files(self):
    """ Create array of file object(s) """
    return []
