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


## @file RappCloud/CloudServices/Service.py
#
#  @copyright Rapp Projecty EU 2015
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


from Service import *
from RappCloud.Objects import (
    File,
    Payload
    )


##
#  @brief Face-Detection Cloud Service Class.
#  @param fast
#  @param image
#
class EmailFetch(Service):
    def __init__(self, *args, **kwargs):
        # Cloud Service request arguments
        self.email = ''
        self.password = ''
        self.server = ''
        self.port = ''
        self.date_from = 0
        self.date_to = 0
        self.email_status = ''
        self.num_emails = 0
        ###############################

        super(EmailFetch, self).__init__(
            svcname='email_fetch',
            **kwargs
            )


    ##
    #  @brief Create payload object of the cloud service
    #
    def _make_payload(self):
        # Create and return payload object
        return Payload(
            email=self.email,
            passwd=self.password,
            server=self.server,
            port=self.port,
            from_date=self.date_from,
            to_date=self.date_to,
            email_status=self.email_status,
            num_emails=self.num_emails)


    ##
    #  @brief Create array of file object(s) of the cloud service.
    #
    def _make_files(self):
        # Create and return array of file objects
        return []
