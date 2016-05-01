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


## @file RappCloud/CloudServices/PathPlanningPlan2D.py
#
#  @copyright Rapp Projecty EU 2016
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


from Service import *
from RappCloud.Objects import (
    File,
    Payload
    )


class PathPlanningPlan2D(Service):
  """ PathPlanningPlan2D Cloud Service class """

  def __init__(self, **kwargs):
    """!
    Constructor

    @param **kwargs - Keyword arguments. Apply values to the request attributes.
      - @ref map_name
      - @ref robot_type
      - @ref algorithm
      - @ref pose_start
      - @ref pose_goal
    """

    # Cloud Service request arguments
    # -------------------------------------------------------------
    ## The map name to use.
    self.map_name = ''
    ## The robot type. It is required to determine it's parameters (footprint etc.)
    self.robot_type = ''
    ## The path planning algorithm to apply.
    self.algorithm = ''
    ## Start pose of the robot. (Same structure to ROS-GeometryMsgs/PoseStamped)
    self.pose_start = {}
    ## Goal pose of the robot. (Same structure to ROS-GeometryMsgs/PoseStamped)
    self.pose_goal = {}
    # -------------------------------------------------------------

    super(PathPlanningPlan2D, self).__init__(
        svcname='path_planning_plan_path_2d', **kwargs)


  def _make_payload(self):
    # Create and return payload object
    return Payload(
        map_name=self.map_name,
        robot_type=self.robot_type,
        algorithm=self.algorithm,
        start=self.pose_start,
        goal=self.pose_goal
        )


  def _make_files(self):
    """ Create array of file object(s) """
    return [ ]
