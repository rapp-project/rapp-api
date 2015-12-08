#!/usr/bin/env node

var RAPPCloud = require('../../../RAPPCloud.js');
var request = require('request');

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class ontologySubClassesOf
 * @description Asynchronous Service which will request the Ontology Subclasses of/for an Input - Constructor for this handler
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @see HTTP POST RFC: http://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html
 * @see HTTP Transfer requirements: http://www.w3.org/Protocols/rfc2616/rfc2616-sec8.html
 * @param query is the entity for which we will try to acquire its Sub-Ordinates
 * @param callback is the function that will receive the classes discovered
 */
RAPPCloud.prototype.ontologySubclassesOf = function ( query, callback )
{
    var cloud = this;
    var body_string = 'query=' + query;
    var _delegate = callback;
    
    request.post({
        headers: {
//			'Authorization' : 'Basic cmFwcGRldjpyYXBwZGV2',
			'Content-Type' : 'application/x-www-form-urlencoded',
			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/ontology_subclasses_of/ ',
        body: body_string
    },
    function ( error, response, json ) 
    {
        if ( !error && response.statusCode == 200)
            handle_reply( json );
        else if ( error )
            error_handler ( error );
        else if ( response.statusCode != 200 )
            console.log ( "Error: " + response.statusCode );
    });
    
    function handle_reply( json )
    {
		var json_obj;
		try {
			json_obj = JSON.parse(json);
			// JSON reply is: { results: [], trace: [], error: '' }
		
			if(json_obj.error){  // Check for Errors returned by the api.rapp.cloud
				console.log('ontologySubClassesOf JSON error: ' + json_obj.error);
			}
			if (json_obj.results){
				_delegate(json_obj.results);
			}
		} catch (e) {
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}   
};

/// Export
module.exports = RAPPCloud.ontologySubclassesOf;
