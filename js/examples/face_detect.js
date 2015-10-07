#!/usr/bin/env node

// Import the faceDetector JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('./../RAPPCloud.js')
RAPPCloud.faceDetector = require('./../includes/cloud/faceDetector/faceDetector.js');
var services = new RAPPCloud( );

/** 
 * This is the method that will handle the reply by the service.faceDetector
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function handler ( faces )
{
    if (faces.length) 
		console.log ( 'Found ' + faces.length + ' faces!');
	else
		console.log ( 'No faces detected');
}

services.faceDetector('./two_faces.jpg', handler );
