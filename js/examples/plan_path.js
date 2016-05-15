#!/usr/bin/env node

// Import the path_planning_plan_path_2d JS API Services & Init the RAPPCloud Object
var RAPPCloud = require('rapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.path_planning_plan_path_2d = require('rapp-platform-api/includes/cloud/path_planning_plan_path_2d');

var services = new RAPPCloud( );

/** 
 * This is the method that will handle the reply by the service.path_planning_plan_path_2d
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function callback ( path )
{
    console.log ( 'The waypoints need be followed are the following:');
    for (var i = 0; i < path.length; i++) {
		console.log ( path[i] );
	}
}

services.path_planning_plan_path_2d( 'empty', 'Nao', 'dijkstra', {}, {}, callback );
