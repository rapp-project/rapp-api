#!/usr/bin/env node

var path = require('path');

// Import the faceDetector JS API Service & Init the RAPPCloud Object
var __cloudDir = path.join(__dirname, '..', 'includes', 'cloud');
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));
RAPPCloud.qrDetector = require(path.join(__cloudDir, 'faceDetector.js'));
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

services.faceDetector('two_faces.jpg', 'jpg', handler );
