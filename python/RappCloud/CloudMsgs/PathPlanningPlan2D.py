from RappCloud.Objects import (
    File,
    Payload)

from Cloud import (
    CloudMsg,
    CloudRequest,
    CloudResponse)


class PathPlanningPlan2D(CloudMsg):
    """ Path Planning Plan 2D Cloud Message object

    For more information read on:
        https://github.com/rapp-project/rapp-platform/tree/master/rapp_path_planning/rapp_path_planning
    """

    class Request(CloudRequest):
        """ Path Planning Plan 2D Cloud Request object.

        PathPlanningPlan2D.Request
        """
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

            ## The map name.
            self.map_name = ''
            ## The robot type. It is required to determine it's parameters
            # (footprint etc.)
            self.robot_type = ''
            ## The path planning algorithm to apply.
            self.algorithm = ''
            ## Start pose of the robot.
            # Same structure to ROS-GeometryMsgs/PoseStamped
            self.pose_start = {}
            ## Goal pose of the robot.
            # Same structure to ROS-GeometryMsgs/PoseStamped
            self.pose_goal = {}
            super(PathPlanningPlan2D.Request, self).__init__(**kwargs)


        def make_payload(self):
            """ Create and return the Payload of the Request. """
            return Payload(
                map_name=self.map_name,
                robot_type=self.robot_type,
                algorithm=self.algorithm,
                start=self.pose_start,
                goal=self.pose_goal)



        def make_files(self):
            """ Create and return Array of File objects of the Request. """
            return []


    class Response(CloudResponse):
        """ Path Planning Plan 2D Cloud Response object.

        PathPlanningPlan2D.Response
        """
        def __init__(self, **kwargs):
            """!
            Constructor

            @param **kwargs - Keyword arguments. Apply values to the request attributes.
                - @ref error
            """

            ## Error message
            self.error = ''
            ## Plan Status. Can be one of:
            # - 0 : path cannot be planned.
            # - 1 : path found.
            # - 2 : wrong map name.
            # - 3 : wrong robot type.
            # - 4 : wrong algorithm.
            self.plan_found = 0
            ## Ff plan_found is equal to 0 (path found), this is an array of
            # waypoints from start to goal.
            self.path = []
            super(PathPlanningPlan2D.Response, self).__init__(**kwargs)


    def __init__(self, **kwargs):
        """!
        Constructor

        @param **kwargs - Keyword arguments. Apply values to the request attributes.
            - @ref Request.map_name
            - @ref Request.robot_type
            - @ref Request.algorithm
            - @ref Request.pose_start
            - @ref Request.pose_goal
        """

        # Create and hold the Request object for this CloudMsg
        self.req = PathPlanningPlan2D.Request()
        # Create and hold the Response object for this CloudMsg
        self.resp = PathPlanningPlan2D.Response()
        super(PathPlanningPlan2D, self).__init__(
            svcname='path_planning_plan_path_2d', **kwargs)


