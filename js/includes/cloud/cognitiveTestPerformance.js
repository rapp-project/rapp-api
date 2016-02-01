#!/usr/bin/env node

var request = require('request');
var path = require('path');

var __cloudDir = path.join(__dirname);

var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class cognitiveTestPerformance
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the record_cognitive_test_performance web service for an Input
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param user is the username of client used to retrieve information from database.
 * @param test_instance is the Cognitive Exercise test instance. The full cognitive test entry name as reported by the cognitive_test_chooser()
 * @param score User's performance score on given test entry.
 * @param callback is the function that will receive the result
 */
RAPPCloud.prototype.cognitiveTestPerformance = function ( user, test_instance, score, callback )
{
    var cloud = this;
    var body_string = 'user=' + cloud.escape_string(user) + '&test_instance=' + cloud.escape_string(test_instance) + '&score=' + score;
    var _delegate = callback;
    
    request.post({
        headers: {
//			'Authorization' : 'Basic cmFwcGRldjpyYXBwZGV2',
			'Content-Type' : 'application/x-www-form-urlencoded',
			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/record_cognitive_test_performance/ ',
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
			// JSON reply is: { performance_entry: '', error: '' }
		
			if(json_obj.error){  // Check for Errors returned by the api.rapp.cloud
				console.log('cognitiveTestPerformance JSON error: ' + json_obj.error);
			}
			_delegate( json_obj.performance_entry );
		} catch (e) {
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}   
};

/// Export
module.exports = RAPPCloud.cognitiveTestPerformance;
