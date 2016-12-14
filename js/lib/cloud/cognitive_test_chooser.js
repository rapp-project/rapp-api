#!/usr/bin/env node

var path = require('path');
var __cloudDir = path.join(__dirname);
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class cognitive_test_chooser
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the cognitive_test_chooser web service for an Input
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param test_type (String) is the Cognitive Exercise test type. Can be one of ['ArithmeticCts', 'AwarenessCts', 'ReasoningCts', '']
 * @param test_subtype (String): Use this to force select from this subtype. Defaults to empty string "".
 * @param test_diff (String): Use this to force select from this difficulty. Defaults to empty string "".
 * @param test_index (String): Use this to force select from this id. Defaults to empty string "".
 * @param callback is the function that will receive the result
 */
RAPPCloud.prototype.cognitive_test_chooser = function(
                                                        test_type,
                                                        callback,
                                                        test_subtype,
                                                        test_diff,
                                                        test_index
                                                     )
{
    test_subtype = typeof test_subtype !== 'undefined' ? test_subtype : '';
    test_diff = typeof test_diff !== 'undefined' ? test_diff : '';
    test_index = typeof test_index !== 'undefined' ? test_index : '';

    var cloud = this;
    var _delegate = callback;
    var request = cloud.determine_protocol();

    var body_obj = {};
    body_obj.test_type = cloud.escape_string(test_type);
    body_obj.test_subtype = cloud.escape_string(test_subtype);
    body_obj.test_diff = cloud.escape_string(test_diff);
    body_obj.test_index = cloud.escape_string(test_index);
    var body_json = JSON.stringify(body_obj);
    
    request.post({
        headers: {
			'Accept-Token' : cloud.token,
			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/cognitive_test_chooser/ ',
        body: "json=" + body_json
    },
    function (error, response, json) 
    {
        if (!error && response.statusCode == 200)
            handle_reply(json);
        else if (error)
            error_handler (error);
        else if (response.statusCode != 200)
            console.log ('Error: ' + response.statusCode);
    });
    
    function handle_reply(json)
    {
		var json_obj;
		try {
			json_obj = JSON.parse(json);
			// JSON reply is: { questions: [], possib_ans: [], correct_ans: [], test_instance: '', test_type: '', test_subtype: '', error: '' }
		
			if(json_obj.error){  // Check for Errors  
				console.log('cognitive_test_chooser JSON error: ' + json_obj.error);
			}
			_delegate(json_obj.questions, json_obj.possib_ans, json_obj.correct_ans, json_obj.test_instance, json_obj.test_type, json_obj.test_subtype);
		} catch (e) {
			console.log('cognitive_test_chooser::handle_reply Error parsing: ');
            return console.error(e);
		}
	}
	
	function error_handler(error) {
		return console.error(error);
	}   
};

/// Export
module.exports = RAPPCloud.cognitive_test_chooser;
