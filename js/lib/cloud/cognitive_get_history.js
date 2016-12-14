#!/usr/bin/env node

var path = require('path');
var __cloudDir = path.join(__dirname);
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class cognitive_get_history
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the cognitive_get_history web service for an Input
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param callback is the function that will receive the result
 * @param test_type (String): Cognitive Exercise test type. Can be one of 
 * ['ArithmeticCts', 'AwarenessCts', 'ReasoningCts'] or leave empty ("") for all. Default: "".
 * @param from_time (Integer): Unix timestamp. Default: 0.
 * @param to_time (Integer): Unix timestamp. Default: 0.
 */
RAPPCloud.prototype.cognitive_get_history = function(
                                                        callback,
                                                        test_type,
                                                        from_time,
                                                        to_time 
                                                    )
{
    test_type = typeof test_type !== 'undefined' ? test_type : '';
    from_time = typeof from_time !== 'undefined' ? from_time : 0;
    to_time = typeof to_time !== 'undefined' ? to_time : 0;

    var cloud = this;
    var _delegate = callback;
    var request = cloud.determine_protocol();

    var body_obj = {};
    body_obj.test_type = cloud.escape_string(test_type);
    body_obj.from_time = from_time;
    body_obj.to_time = to_time;
    var body_json = JSON.stringify(body_obj);
    
    request.post({
        headers: {
			'Accept-Token' : cloud.token,
			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/cognitive_get_history/ ',
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
			// JSON reply is: { records: {}, error: '' }
            // records (Object): Users history records on Cognitive Exerises
            // error (String): Error message, if one occures.
		
			if(json_obj.error){  // Check for Errors  
				console.log('cognitive_get_history JSON error: ' + json_obj.error);
			}
			_delegate(json_obj.records);
		} catch (e) {
			console.log('ognitive_get_history::handle_reply Error parsing: ');
            return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}   
};

/// Export
module.exports = RAPPCloud.cognitive_get_history;
