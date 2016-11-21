#!/usr/bin/env node

var path = require('path');
var __cloudDir = path.join(__dirname);
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class cognitive_get_scores
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the cognitive_get_scores web service for an Input
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param callback is the function that will receive the result
 * @param up_to_time (Integer): Unix timestamp. Return scores that have been recorder up to this time value. Default: 0.
 * @param test_type (String): Cognitive Exercise test type. Can be one of ['ArithmeticCts', 'AwarenessCts', 'ReasoningCts'] or leave empty ("") for all. Default: "".
 */

RAPPCloud.prototype.cognitive_get_scores = function ( callback, up_to_time, test_type )
{
    up_to_time = typeof up_to_time !== 'undefined' ? up_to_time : 0;
    test_type = typeof test_type !== 'undefined' ? test_type : '';
    
    var request = require('request').defaults({
	  secureProtocol: 'TLSv1_2_method',
	  rejectUnauthorized: false
	});

    var cloud = this;
    var _delegate = callback;

    var body_obj = {};
    body_obj.up_to_time = up_to_time;
    body_obj.test_type = cloud.escape_string(test_type);
    var body_json = JSON.stringify(body_obj);
    
    request.post({
        headers: {
			'Accept-Token' : cloud.token,
			'Content-Type' : 'application/x-www-form-urlencoded',
			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/cognitive_get_scores/ ',
        body: "json=" + body_json
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
			// JSON reply is: { test_classes: [], scores: [], error: '' }
            // test_classes (Array): An array of the test classes indexes.
            // scores (Array): Array of scores. Each array index corresponds to the test class of the test_classes property.
            // error (String): Error message, if one occures.
		
			if(json_obj.error){  // Check for Errors
				console.log('cognitive_get_scores JSON error: ' + json_obj.error);
			}
			_delegate(json_obj.test_classes, json_obj.scores);
		} catch (e) {
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}   
};

/// Export
module.exports = RAPPCloud.cognitive_get_scores;
