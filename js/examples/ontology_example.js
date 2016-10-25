#!/usr/bin/env node

// Import the ontology related JS API Services & Init the RAPPCloud Object
var RAPPCloud = require('rapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.ontology_subclasses_of = require('rapp-platform-api/includes/cloud/ontology_subclasses_of');
RAPPCloud.ontology_superclasses_of = require('rapp-platform-api/includes/cloud/ontology_superclasses_of');
RAPPCloud.ontology_is_subsuperclass_of = require('rapp-platform-api/includes/cloud/ontology_is_subsuperclass_of');

var services = new RAPPCloud( );
var query = 'Oven';
var superclass =  'Box-Container';
var subclass = 'MicrowaveOven';

/** 
 * This is the method that will handle the reply by the service.ontology_subclasses_of
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
 * This is the method that will handle the reply by the service.ontology_superclasses_of
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
 * This is the method that will handle the reply by the service.ontology_is_subsuperclass_of
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function cb3 ( result )
{
    console.log ( superclass + ' is Superclass of ' + subclass + ': ' + result.toString() );
}

services.ontology_subclasses_of(query, cb1 );
services.ontology_superclasses_of(query, cb2 );
services.ontology_is_subsuperclass_of( superclass, subclass, true, cb3 );
