#!/usr/bin/env node

var RAPPCloud = require('./../../../RAPPCloud.js');

/**
 * Prototype the RAPPCloud Service Method.
 * 
 * @method ontologySubclassOf
 * @brief Asynchronous Service which will request the Ontology Subclass of/for an Input
 * @version 1
 * @date 28-August-2015
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 */ 

/**
 * @brief Constructor for this handler
 * @param query is the entity for which we will try to acquire its Super-Ordinates
 * @param callback is the function that will receive the classes discovered
 */
RAPPCloud.prototype.ontologySubclassOf = function ( query, callback )
{
    var cloud = this;
    var body_string = 'query=' + query ;
    var request = require('request');
    request.post({
        headers: {
//			'Authorization' : 'Basic cmFwcGRldjpyYXBwZGV2',
			'Content-Type' : 'application/x-www-form-urlencoded'
//			'Content-Length' : body_string.length.toString(),
//			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/ontology_subclasses_of/ ',
        body: body_string
    },
    function ( error, response, body ) 
    {
        if ( !error && response.statusCode == 200)
            callback( body );
        else if ( error )
            console.log ( error );
        else if ( response.statusCode != 200 )
            console.log ( "Error: " + response.statusCode );
    })
}

/// Export
module.exports = RAPPCloud;
