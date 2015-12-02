#!/usr/bin/env node


// Import the ontologySubclassOf JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../RAPPCloud.js');
RAPPCloud.ontologySubclassesOf = require('../includes/cloud/ontologySubclassesOf/ontologySubclassesOf.js');
RAPPCloud.ontologySuperclassesOf = require('../includes/cloud/ontologySuperclassesOf/ontologySuperclassesOf.js');
RAPPCloud.ontologySubSuperClassOf = require('../includes/cloud/ontologySubSuperClassOf/ontologySubSuperClassOf.js');

var services = new RAPPCloud( );
var query='Oven';

/** 
 * This is the method that will handle the reply by the service.ontologySubclassesOf
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function cb1 ( classes )
{
    console.log ( 'Subclasses of ' + query + ':');
    for (i = 0; i < classes.length; i++) {
		console.log ( classes[i] );
	}
}

/** 
 * This is the method that will handle the reply by the service.ontologySuperclassesOf
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function cb2 ( classes )
{
    console.log ( 'Superclasses of ' + query + ':');
    for (i = 0; i < classes.length; i++) {
		console.log ( classes[i] );
	}
}

/** 
 * This is the method that will handle the reply by the service.ontologySubSuperclassOf
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function cb3 ( Parent, Child, result )
{
    console.log ( Parent + ' is Superclass of ' + Child + ': ' + result.toString() );
}

services.ontologySubclassesOf(query, cb1 );
services.ontologySuperclassesOf(query, cb2 );
services.ontologySubSuperClassOf( 'Box-Container', 'MicrowaveOven', true, cb3 );
