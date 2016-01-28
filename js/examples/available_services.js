#!/usr/bin/env node

// Import the availableServices JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('RAPPCloud');
RAPPCloud.availableServices = require('availableServices');

var services = new RAPPCloud( );

/** 
 * This is the method that will handle the reply by the services.speechDetectionSphinx4
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
 
function handler ( services )
{
	console.log( "The following services are available:\n" + services );
}

services.availableServices( handler );
