#!/usr/bin/env node

// Import the human_detection JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../includes/cloud/RAPPCloud.js');
RAPPCloud.human_detection = require('../includes/cloud/human_detection.js');
var services = new RAPPCloud( );

/** 
 * This is the method that will handle the reply by the services.human_detection
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function handler ( humans )
{
    if (humans.length) 
		console.log ( 'Found ' + humans.length + ' humans!');
	else
		console.log ( 'No humans detected');
}

services.human_detection( '../../testdata/face_samples/fatsaSou_near.jpg', 'jpg', handler );
