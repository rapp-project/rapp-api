#!/usr/bin/env node

// Import the path_planning_plan_path_2d JS API Services & Init the RAPPCloud Object
var RAPPCloud = require('../lib/cloud/RAPPCloud');
RAPPCloud.path_planning_plan_path_2d = require('../lib/cloud/path_planning_plan_path_2d');

var services = new RAPPCloud();

/** 
 * This is the method that will handle the reply by the service.path_planning_plan_path_2d
 */
function callback(path)
{
    // check if path is an array meaning that a path was found
    if (path.constructor === Array){
        console.log ('The waypoints need be followed are the following:');
        for (var i = 0; i < path.length; i++) {
		    console.log(path[i]);
	    }
    }
    else {
        switch(path) {
            case 0:
                console.log("No plan found");
                break;
            case 2:
                console.log("Wrong map name.");
                break;
            case 3:
                console.log("Wrong robot type.");
                break;
            case 4:
                console.log("Wrong algorithm.");
                break;
        }
    }
}

var start = {};
start.header = {};
start.header.seq = 1;
start.header.stamp = 0;
start.header.frame_id = '1';
start.pose = {};
start.pose.position = {x:3, y:4, z:0};
start.pose.orientation = {x:0, y:0, z:0, w:0};

var goal = {};
goal.header = {};
goal.header.seq = 2;
goal.header.stamp = 0;
goal.header.frame_id = '2';
goal.pose = {};
goal.pose.position = {x:5, y:10, z:0};
goal.pose.orientation = {x:0, y:1, z:0, w:0};

services.path_planning_plan_path_2d('the_map', 'Nao', 'dijkstra', start, goal, callback);
