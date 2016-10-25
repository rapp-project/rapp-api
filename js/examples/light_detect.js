#!/usr/bin/env node

// Import the hazard_detection_light JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('rapp-platform-arapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.hazard_detection_light = require('rapp-platform-arapp-platform-api/includes/cloud/hazard_detection_light');

var services = new RAPPCloud( );


/** 
 * This is the method that will handle the reply by the service.hazard_detection_light
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function handler ( light_level )
{
    if (light_level >= 0) 
		console.log ( 'Estimated light level: ' + light_level );
	else
		console.log ( 'Error processing image' );
}

console.log('lamp_on.jpg: ');
services.hazard_detection_light('../../testdata/lamp_on.jpg', 'jpg', handler );
console.log('lamp_off.jpg: ');
services.hazard_detection_light('../../testdata/lamp_off.jpg', 'jpg', handler );
