#!/usr/bin/env node

// Import the hazard_detection_light JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../lib/cloud/RAPPCloud');
RAPPCloud.hazard_detection_light = require('../lib/cloud/hazard_detection_light');

var services = new RAPPCloud();

/** 
 * This is the method that will handle the reply by the service.hazard_detection_light
 */
function handler(light_level)
{
    if (light_level >= 0) 
		console.log ('Estimated light level: ' + light_level);
	else
		console.log ('Error processing image');
}

services.hazard_detection_light('../testdata/lamp_on.jpg', handler);
