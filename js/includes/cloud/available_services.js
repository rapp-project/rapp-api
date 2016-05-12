#!/usr/bin/env node

var path = require('path');
var __cloudDir = path.join(__dirname);
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class available_services
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the available_services cloud service for an Input
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param callback is the function that will receive the result
 */
RAPPCloud.prototype.available_services = function ( callback )
{
	var request = require('request').defaults({
      secureProtocol: 'TLSv1_2_method',
      rejectUnauthorized: false
    });

    var cloud = this;
    var _delegate = callback;
	
	request.post({
        headers: {
            'Accept-Token' : cloud.token,
			'Content-Type' : 'application/x-www-form-urlencoded',
			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/available_services/ ',
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
            // JSON reply is: { services: [], error: '' }
    
            if(json_obj.error){  // Check for Errors  
                    console.log('available_services JSON error: ' + json_obj.error);
            }
            if (json_obj.services){
                    _delegate(json_obj.services);
            }
        } catch (e) {
            console.log('available_services::handle_reply Error parsing: ');
            return console.error(e);
        }
    }
    
    function error_handler( error ) {
        return console.error(error);
    }  
};

/// Export
module.exports = RAPPCloud.available_services;
