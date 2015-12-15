#!/usr/bin/env node

var path = require('path');

// Import the ontologySubclassOf JS API Service & Init the RAPPCloud Object
var __cloudDir = path.join(__dirname, '..', 'includes', 'cloud');
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));
RAPPCloud.qrDetector = require(path.join(__cloudDir, 'ontologySubclassesOf.js'));
RAPPCloud.qrDetector = require(path.join(__cloudDir, 'ontologySuperclassesOf.js'));
RAPPCloud.qrDetector = require(path.join(__cloudDir, 'ontologySubSuperClassOf.js'));

var services = new RAPPCloud( );
var query='Oven';

/** 
 * This is the method that will handle the reply by the service.ontologySubclassesOf
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function cb1 ( classes )
{
    console.log ( 'Subclasses of ' + query + ':');
    for (var i = 0; i < classes.length; i++) {
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
    for (var i = 0; i < classes.length; i++) {
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
