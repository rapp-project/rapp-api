#!/usr/bin/env node

var RAPPCloud = require('./../../RAPP.js');

/**
 * Prototype the RAPPCloud Service Method.
 * 
 * @method ontologySubclassOf
 * @brief Asynchronous Service which will request the Ontology Subclass of/for an Input
 * @version 1
 * @date 28-August-2015
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 */ 

RAPPCloud.prototype.ontologySubclassOf = function ( query, callback )

{
    var rapp = this;
    var body_string = 'query=' + query ;
    var request = require('request');
    request.post({
        headers: {
			'Content-Type' : 'application/x-www-form-urlencoded',
			'Content-Length' : body_string.length.toString(),
			'Connection' : 'close'
			},
        url: rapp.cloud_url + '/hop/ontology_subclasses_of/ ',
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
