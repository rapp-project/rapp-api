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
 * @class object_detection_clear_models
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the
 * Cloud to delete the operational memory 
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param callback is the function that will receive the result
 */
RAPPCloud.prototype.object_detection_clear_models = function ( callback )
{
    var cloud = this;
    var _delegate = callback;
	
	request.post({
        headers: {
            'Accept-Token' : cloud.token,
			'Content-Type' : 'application/x-www-form-urlencoded',
			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/object_detection_clear_models/ ',
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
            // JSON reply is: { result: 0, error: '' }
    
            if(json_obj.error)  // Check for Errors  
                console.log('object_detection_clear_models JSON error: ' + json_obj.error);
            else 
                _delegate(json_obj.result);
        } catch (e) {
            console.log('object_detection_clear_models::handle_reply Error parsing: ');
            return console.error(e);
        }
    }
    
    function error_handler( error ) {
        return console.error(error);
    }  
};

/// Export
module.exports = RAPPCloud.object_detection_clear_models;
