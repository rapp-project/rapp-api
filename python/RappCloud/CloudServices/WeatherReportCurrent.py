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


## @file RappCloud/CloudServices/WeatherReportCurrent.py
#
#  @copyright Rapp Projecty EU 2016
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


from Service import *
from RappCloud.Objects import (
    File,
    Payload
    )


class WeatherReportCurrent(Service):
  """ WeatherReportCurrent Cloud Service class """

  def __init__(self, **kwargs):
    """!
    Constructor

    @param **kwargs - Keyword arguments. Apply values to the request attributes.
      - @ref city
      - @ref weather_reporter
      - @ref metric
    """

    # Cloud Service request arguments
    # -------------------------------------------------------------
    ## The desired city
    self.city = ''
    ## The weather API to use. Defaults to "yweather" .
    self.weather_reporter = ''
    ## The return value units.
    self.metric = 0
    # -------------------------------------------------------------

    super(WeatherReportCurrent, self).__init__(
        svcname='weather_report_current', **kwargs)


  def _make_payload(self):
    """! Make request payload object """
    return Payload(
        city=self.city,
        weather_reporter=self.weather_reporter,
        metric=self.metric
        )


  def _make_files(self):
    """! Create array of file object(s) """
    return []
