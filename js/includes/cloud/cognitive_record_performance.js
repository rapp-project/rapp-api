#!/usr/bin/env node

var path = require('path');
var __cloudDir = path.join(__dirname);
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));
const config = require("../../config/config");

if (config.protocol === "https")
{
    var request = require('request').defaults({
	    secureProtocol: 'TLSv1_2_method',
	    rejectUnauthorized: false
	});
}
else if (config.protocol === "http")
{
    var request = require("request");
}
else
{
    console.log("please choose one of: http or https(for TLS_1.2) as protocols");
}

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class cognitive_record_performance
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the cognitive_record_performance web service for an Input
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param test_instance (String) is the Cognitive Exercise test instance. The full cognitive test entry name as reported by the cognitive_test_chooser()
 * @param score (Integer) User's performance score on given test entry.
 * @param callback is the function that will receive the result
 */
 
RAPPCloud.prototype.cognitive_record_performance = function ( test_instance, score, callback )
{
    var cloud = this;
    var _delegate = callback;
    
    var body_obj = {};
    body_obj.test_instance = cloud.escape_string(test_instance);
    body_obj.score = score;
    var body_json = JSON.stringify(body_obj);

    request.post({
        headers: {
			'Accept-Token' : cloud.token,
			'Content-Type' : 'application/x-www-form-urlencoded',
			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/cognitive_record_performance/ ',
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
			// JSON reply is: { performance_entry: '', error: '' }
		
			if(json_obj.error){  // Check for Errors  
				console.log('cognitive_record_performance JSON error: ' + json_obj.error);
			}
			_delegate( json_obj.performance_entry );
		} catch (e) {
			console.log('cognitive_record_performance::handle_reply Error parsing: ');
            return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}   
};

/// Export
module.exports = RAPPCloud.cognitive_record_performance;
