#!/usr/bin/env node

// Import the object_recognition JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../includes/cloud/RAPPCloud.js');
RAPPCloud.object_recognition = require('../includes/cloud/object_recognition.js');
var services = new RAPPCloud( );


/** 
 * This is the method that will handle the reply by the service.object_recognition
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function handler ( object_class )
{
    if (object_class) 
		console.log ( 'A(n) ' + object_class + ' object was recognized!');
	else
		console.log ( 'No objects recognized');
}

services.object_recognition('../../testdata/cat.jpg', 'jpg', handler, true );
