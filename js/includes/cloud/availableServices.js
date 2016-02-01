#!/usr/bin/env node

var request = require('request');
var path = require('path');

var __cloudDir = path.join(__dirname);

var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class availableServices
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the available_services cloud service for an Input
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param callback is the function that will receive the result
 */
RAPPCloud.prototype.availableServices = function ( callback )
{
	var cloud = this;
    var _delegate = callback;
	
	request.post({
        headers: {
//			'Authorization' : 'Basic cmFwcGRldjpyYXBwZGV2',
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
    
            if(json_obj.error){  // Check for Errors returned by the api.rapp.cloud
                    console.log('availableServices JSON error: ' + json_obj.error);
            }
            if (json_obj.services){
                    _delegate(json_obj.services);
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
module.exports = RAPPCloud.availableServices;
