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
 * @class ontology_is_subsuperclass_of
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the Ontology SubSuperclass of/for an Input
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param parent is the parent class in question
 * @param child is the child of the parent class in question
 * @param recursive is a boolean argument, when true the function checks for indirect parent-child relationship as well
 * @param callback is the function that will receive the result
 */
RAPPCloud.prototype.ontology_is_subsuperclass_of = function ( parent, child, recursive, callback )
{
    var cloud = this;
    var _delegate = callback;
    
    var body_obj = {};
    body_obj.parent_class = cloud.escape_string(parent);
    body_obj.child_class = cloud.escape_string(child);
    body_obj.recursive = recursive;
    var body_json = JSON.stringify(body_obj);
    
    request.post({
        headers: {
			'Accept-Token' : cloud.token,
			'Content-Type' : 'application/x-www-form-urlencoded',
			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/ontology_is_subsuperclass_of/ ',
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
			// JSON reply is: { "result":true,"trace":[],"error":"" }
		
			if(json_obj.error){  // Check for Errors  
				console.log('ontology_is_subsuperclass_of JSON error: ' + json_obj.error);
			}
			_delegate( json_obj.result);
		} catch (e) {
			console.log('ontology_is_subsuperclass_of::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}   
};

/// Export
module.exports = RAPPCloud.ontology_is_subsuperclass_of;
