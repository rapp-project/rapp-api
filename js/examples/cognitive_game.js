#!/usr/bin/env node

// Import the cognitive_record_performance JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('rapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.cognitive_test_chooser = require('rapp-platform-api/includes/cloud/cognitive_test_chooser');
RAPPCloud.cognitive_record_performance = require('rapp-platform-api/includes/cloud/cognitive_record_performance');
RAPPCloud.cognitive_get_history = require('rapp-platform-api/includes/cloud/cognitive_get_history');
RAPPCloud.cognitive_get_scores = require('rapp-platform-api/includes/cloud/cognitive_get_scores');
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

function cb3 ( records )
{
	console.log( records );
}

function cb4 ( test_classes, scores )
{
	for (var i=0; i<test_classes.length; i++) {
		console.log ("Your score in " + test_classes[i] + " category is: " + scores[i] );
	}
}

services.cognitive_test_chooser(	// 'ArithmeticCts',
								    // 'AwarenessCts',
									'ReasoningCts', 
									cb1 );
						
services.cognitive_record_performance("ReasoningCts_pQmhNKHv", 1, cb2 );

services.cognitive_get_history( cb3, '', 1450348786, 1450348787 );

services.cognitive_get_scores( cb4, 1450348787, '' );
