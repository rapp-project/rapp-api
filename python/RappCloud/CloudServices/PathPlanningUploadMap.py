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


## @file RappCloud/CloudServices/PathPlanningUploadMap.py
#
#  @copyright Rapp Projecty EU 2016
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


from Service import *
from RappCloud.Objects import (
    File,
    Payload
    )


class PathPlanningUploadMap(Service):
  """ PathPlanningUploadMap Cloud Service class """

  def __init__(self, **kwargs):
    """!
    Constructor

    @param **kwargs - Keyword arguments. Apply values to the request attributes.
      - @ref map_name
      - @ref png_file
      - @ref yaml_file
    """

    # Cloud Service request arguments
    # -------------------------------------------------------------
    ## The map name.
    self.map_name = ''
    ## Path to the map image png file.
    self.png_file = ''
    ## Path to the map description yaml file.
    self.yaml_file = ''
    # -------------------------------------------------------------

    super(PathPlanningUploadMap, self).__init__(
        svcname='path_planning_upload_map', **kwargs)


  def _make_payload(self):
    """ Make request payload object """
    return Payload(map_name=self.map_name)


  def _make_files(self):
    """ Create array of file object(s) """
    return [
        File(self.png_file, 'png_file'),
        File(self.yaml_file, 'yaml_file')
        ]
