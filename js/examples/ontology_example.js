#!/usr/bin/env node


// Import the ontologySubclassOf JS API & Init the RAPPCloud Object
var RAPPCloud = require('./../includes/cloud/ontologySubclassOf/ontologySubclassOf.js');
var services = new RAPPCloud( );
var query='Oven';

/** 
 * This is the method that will handle the reply by the service.ontologySubclassOf
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function cb1 ( classes )
{
    console.log ( 'Subclasses of ' + query + ':');
    for (i = 0; i < classes.length; i++) {
		console.log ( classes[i] );
	}
}

services.ontologySubclassOf(query, cb1 );
