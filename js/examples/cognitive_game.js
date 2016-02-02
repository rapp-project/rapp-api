#!/usr/bin/env node

// Import the record_cognitive_test_performance JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('RAPPCloud');
RAPPCloud.cognitive_test_chooser = require('cognitive_test_chooser');
RAPPCloud.cognitive_test_chooser = require('record_cognitive_test_performance');

var services = new RAPPCloud( );

/** 
 * This is the method that will handle the reply by the service.cognitive_test_chooser
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function cb1 ( questions, possib_ans, correct_ans, test_instance, test_type, test_subtype )
{
	console.log( "-------------test: " + test_instance + ", type: " + test_type + ", subtype: " + test_subtype + "-------------\n");
	for (var i=0; i<questions.length; i++) {
		console.log( "question " + (i+1) + ":" +questions[i]);
		console.log( "possible answers: " + possib_ans[i] );
		console.log ( "correct answer: " + correct_ans[i] + "\n" );
	}
}

/** 
 * This is the method that will handle the reply by the service.record_cognitive_test_performance
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function cb2 ( performance_entry )
{
	console.log( performance_entry );
}

services.cognitive_test_chooser('rapp', // 'ArithmeticCts',
								    // 'AwarenessCts',
									 'ReasoningCts', 
									cb1 );
						
services.record_cognitive_test_performance('rapp', "ReasoningCts_pQmhNKHv", 1, cb2 );


