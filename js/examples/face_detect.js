#!/usr/bin/env node

// Import the face_detection JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../includes/cloud/RAPPCloud.js');
RAPPCloud.face_detection = require('../includes/cloud/face_detection.js');

var services = new RAPPCloud( );


/** 
 * This is the method that will handle the reply by the service.face_detection
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function handler ( faces )
{
    if (faces.length) 
		console.log ( 'Found ' + faces.length + ' faces!');
	else
		console.log ( 'No faces detected');
}

services.face_detection('two_faces.jpg', 'jpg', handler, true );
