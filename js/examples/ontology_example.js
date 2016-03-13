#!/usr/bin/env node

// Import the ontologySubclassOf JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('RAPPCloud');
RAPPCloud.ontology_subclasses_of = require('ontology_subclasses_of');
RAPPCloud.ontology_superclasses_of = require('ontology_superclasses_of');
RAPPCloud.ontology_is_subsuperclass_of = require('ontology_is_subsuperclass_of');

var services = new RAPPCloud( );
var query='Oven';

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
function cb3 ( Parent, Child, result )
{
    console.log ( Parent + ' is Superclass of ' + Child + ': ' + result.toString() );
}

services.ontology_subclasses_of(query, cb1 );
services.ontology_superclasses_of(query, cb2 );
services.ontology_is_subsuperclass_of( 'Box-Container', 'MicrowaveOven', true, cb3 );
