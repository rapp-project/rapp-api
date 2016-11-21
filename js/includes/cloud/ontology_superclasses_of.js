#!/usr/bin/env node

var path = require('path');
var __cloudDir = path.join(__dirname);
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class ontology_superclasses_of
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the Ontology Superclasses of/for an Input - Constructor for this handler
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @see HTTP POST RFC: http://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html
 * @see HTTP Transfer requirements: http://www.w3.org/Protocols/rfc2616/rfc2616-sec8.html
 * @param ontology_class(String): the entity for which we will try to acquire its Super-Ordinates
 * @param callback is the function that will receive the classes discovered
 * @param recursive (Boolean): Recursive search
 */
RAPPCloud.prototype.ontology_superclasses_of = function ( ontology_class, callback, recursive )
{
    var request = require('request').defaults({
	  secureProtocol: 'TLSv1_2_method',
	  rejectUnauthorized: false
	});

    var cloud = this;
    var _delegate = callback;
    
    var body_obj = {};
    body_obj.ontology_class = cloud.escape_string(ontology_class);
    if (typeof recursive != 'undefined')
        body_obj.recursive = recursive;
    var body_json = JSON.stringify(body_obj);
    
    request.post({
        headers: {
			'Accept-Token' : cloud.token,
			'Content-Type' : 'application/x-www-form-urlencoded',
			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/ontology_superclasses_of/ ',
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
			// JSON reply is: { results: [], trace: [], error: '' }
		
			if(json_obj.error){  // Check for Errors  
				console.log('ontology_superclasses_of JSON error: ' + json_obj.error);
			}
			if (json_obj.results){
				_delegate(json_obj.results);
			}
		} catch (e) {
			console.log('ontology_superclasses_of::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}   
};

/// Export
module.exports = RAPPCloud.ontology_superclasses_of;
