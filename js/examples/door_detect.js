#!/usr/bin/env node

// Import the hazard_detection_door_check JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('rapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.hazard_detection_door_check = require('rapp-platform-api/includes/cloud/hazard_detection_door_check');

var services = new RAPPCloud( );


/** 
 * This is the method that will handle the reply by the service.hazard_detection_door_check
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function handler ( door_angle )
{
    if (door_angle >= 0) 
		console.log ( 'Estimated door angle: ' + door_angle );
	else
		console.log ( 'Error processing image' );
}

services.hazard_detection_door_check('door_1.png', 'png', handler );
