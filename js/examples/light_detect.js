#!/usr/bin/env node

// Import the hazard_detection_light_check JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('rapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.hazard_detection_light_check = require('rapp-platform-api/includes/cloud/hazard_detection_light_check');

var services = new RAPPCloud( );


/** 
 * This is the method that will handle the reply by the service.hazard_detection_light_check
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
services.hazard_detection_light_check('../../testdata/lamp_on.jpg', 'jpg', handler );
console.log('lamp_off.jpg: ');
services.hazard_detection_light_check('../../testdata/lamp_off.jpg', 'jpg', handler );
