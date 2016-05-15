#!/usr/bin/env node

// Import the qr_detection JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('rapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.qr_detection = require('rapp-platform-api/includes/cloud/qr_detection');
var services = new RAPPCloud( );

/** 
 * This is the method that will handle the reply by the services.qr_detection
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function handler ( codes )
{
    if ( codes.length ) {
		console.log ( 'Found ' + codes.length + ' codes!');
		for (var i=0; i<codes.length; i++) {
			console.log(codes[i].label() + ' ');
		}
	}
	else
		console.log ( 'No qrCodes detected');
}

services.qr_detection( 'qrcode.png', 'png', handler );
