#!/usr/bin/env node

// Import the hazard_detection_door JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../lib/cloud/RAPPCloud');
RAPPCloud.hazard_detection_door = require('../lib/cloud/hazard_detection_door');

var services = new RAPPCloud();

/** 
 * This is the method that will handle the reply by the service.hazard_detection_door
 */
function handler(door_angle)
{
    if (door_angle >= 0) 
		console.log('Estimated door angle: ' + door_angle);
	else
		console.log('Error processing image');
}

services.hazard_detection_door('../testdata/door_1.png', 'png', handler);
