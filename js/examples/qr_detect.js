#!/usr/bin/env node

// Import the faceDetector JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../RAPPCloud.js');
RAPPCloud.qrDetector = require('../includes/cloud/qrDetector/qrDetector.js');
var services = new RAPPCloud( );

/** 
 * This is the method that will handle the reply by the services.qrDetector
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function handler ( codes )
{
    if ( codes.length ) {
		console.log ( 'Found ' + codes.length + ' codes!');
		for (i=0; i<codes.length; i++) {
			console.log(codes[i].label() + ' ');
		}
	}
	else
		console.log ( 'No qrCodes detected');
}

services.qrDetector( 'qrcode.png', 'png', handler );
