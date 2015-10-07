#!/usr/bin/env node

var RAPPCloud = require('./../../../RAPPCloud.js');
var request = require('request');

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class ontologySubSuperClassOf
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the Ontology SubSuperclass of/for an Input
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param parent is the parent class in question
 * @param child is the child of the parent class in question
 * @param recursive is a boolean argument, when true the function checks for indirect parent-child relationship as well
 * @param callback is the function that will receive the result
 */
RAPPCloud.prototype.ontologySubSuperClassOf = function ( parent, child, recursive, callback )
{
    var cloud = this;
    var body_string = 'parent_class=' + parent + '&child_class=' + child + '&recursive=' + recursive.toString();
    var _delegate = callback;
    
    request.post({
        headers: {
//			'Authorization' : 'Basic cmFwcGRldjpyYXBwZGV2',
			'Content-Type' : 'application/x-www-form-urlencoded',
			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/ontology_is_subsuperclass_of/ ',
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
			// JSON reply is: { "result":true,"trace":[],"error":"" }
		
			if(json_obj.error){  // Check for Errors returned by the api.rapp.cloud
				console.log('ontologySubSuperClassOf JSON error: ' + json_obj.error);
			}
			_delegate( parent, child, json_obj.result);
		} catch (e) {
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}   
};

/// Export
module.exports = RAPPCloud.ontologySubSuperClassOf;
