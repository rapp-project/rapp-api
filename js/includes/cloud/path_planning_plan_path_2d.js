#!/usr/bin/env node

var path = require('path');
var __cloudDir = path.join(__dirname);
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class path_planning_plan_path_2d
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the path_planning_plan_path_2d RAPP platform service
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param map_name (String): The map name to use.
 * @param robot_type (String): The robot type. It is required to determine it's parameters (footprint etc.)
 * @param algorithm (String): The path planning algorithm to apply.
 * @param start (Object): Start pose of the robot. (ROS-GeometryMsgs/PoseStamped)
 * @param goal (Object): Goal pose of the robot. (ROS-GeometryMsgs/PoseStamped)
 * @param callback is the function that will receive the result
 */

RAPPCloud.prototype.path_planning_plan_path_2d = function ( map_name, robot_type, algorithm, start, goal, callback )
{
    var request = require('request').defaults({
	  secureProtocol: 'TLSv1_2_method',
	  rejectUnauthorized: false
	});

    var cloud = this;
    var _delegate = callback;
    
    var body_obj = {};
    body_obj.map_name = cloud.escape_string(map_name);
    body_obj.robot_type = cloud.escape_string(robot_type);
    body_obj.algorithm = cloud.escape_string(algorithm);
    body_obj.start = start;
    body_obj.goal = goal;
    var body_json = JSON.stringify(body_obj);
    
    request.post({
        headers: {
			'Accept-Token' : cloud.token,
			'Content-Type' : 'application/x-www-form-urlencoded',
			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/path_planning_plan_path_2d/ ',
        body: "json=" + body_json
    },
    function ( error, response, json ) 
    {
        if ( !error && response.statusCode == 200)
            handle_reply( json );
        else if ( error )
            error_handler ( error );
        else if ( response.statusCode != 200 )
            console.log ( 'Error: ' + response.statusCode );
    });
    
    function handle_reply( json )
    {
		var json_obj;
		try {
			json_obj = JSON.parse(json);
			// JSON reply is: { plan_found: 0, path: [], error: '' }
			// plan_found (String): Plan Status. Can be one of
        	// 		0 : path cannot be planned.
        	// 		1 : path found.
        	// 		2 : wrong map name.
        	// 		3 : wrong robot type.
        	// 		4 : wrong algorithm.
    		// path: if plan_found is true, this is an array of waypoints from start to goal, where the first one equals start and the last one equals goal.
    		// error (String): Error message, if one occures.

		
			if(json_obj.error){  // Check for Errors  
				console.log('path_planning_plan_path_2d JSON error: ' + json_obj.error);
			}
			switch (json_obj.plan_found)
			{
				case 0:
	        		console.log("Path Cannot be planned.");
	        		break;
	        	case 1:
	        		_delegate(json_obj.path);
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
		} catch (e) {
			console.log('path_planning_plan_path_2d::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}   
};

/// Export
module.exports = RAPPCloud.path_planning_plan_path_2d;
