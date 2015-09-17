#!/usr/bin/env node


// Import the ontologySubclassOf JS API & Init the RAPPCloud Object
var RAPPCloud = require('./../includes/cloud/faceDetector/faceDetector.js');
var services = new RAPPCloud( );

/** 
 * This is the method that will handle the reply by the service.ontologySubclassOf
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function handler ( data )
{
    console.log ( "Reply: " + data );
}

services.faceDetector('./Lenna.png', handler );
