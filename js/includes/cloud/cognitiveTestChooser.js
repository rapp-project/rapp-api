#!/usr/bin/env node

var request = require('request');
var path = require('path');

var __cloudDir = path.join(__dirname);

var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class cognitiveTestChooser
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the record_cognitive_test_chooser web service for an Input
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param user is the username of client used to retrieve information from database.
 * @param test_type is the Cognitive Exercise test type. Can be one of ['ArithmeticCts', 'AwarenessCts', 'ReasoningCts']
 * @param callback is the function that will receive the result
 */
RAPPCloud.prototype.cognitiveTestChooser = function ( user, test_type, callback )
{
    var cloud = this;
    var body_string = 'user=' + cloud.escape_string(user) + '&test_type=' + cloud.escape_string(test_type);
    var _delegate = callback;
    
    request.post({
        headers: {
//			'Authorization' : 'Basic cmFwcGRldjpyYXBwZGV2',
			'Content-Type' : 'application/x-www-form-urlencoded',
			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/cognitive_test_chooser/ ',
        body: body_string
    },
    function ( error, response, json ) 
    {
        if ( !error && response.statusCode == 200)
            handle_reply( json );
        else if ( error )
            error_handler ( error );
        else if ( response.statusCode != 200 )
            console.log ( 'Error: ' + response.statusCode );
    });
    
    function handle_reply( json )
    {
		var json_obj;
		try {
			json_obj = JSON.parse(json);
			// JSON reply is: { questions: [], possib_ans: [], correct_ans: [], test_instance: '', test_type: '', test_subtype: '', error: '' }
		
			if(json_obj.error){  // Check for Errors returned by the api.rapp.cloud
				console.log('cognitiveTestChooser JSON error: ' + json_obj.error);
			}
			_delegate( json_obj.questions, json_obj.possib_ans, json_obj.correct_ans, json_obj.test_instance, json_obj.test_type, json_obj.test_subtype );
		} catch (e) {
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}   
};

/// Export
module.exports = RAPPCloud.cognitiveTestChooser;
