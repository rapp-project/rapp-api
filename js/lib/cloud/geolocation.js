#!/usr/bin/env node

var path = require('path');
var __cloudDir = path.join(__dirname);
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class geolocation
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the geolocation RAPP platform service
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param ipaddr: The machine's ipaddr
 * @param engine: Engine to use. Defaults to 'ip-api' (Currently the only supported).
 * @param callback is the function that will receive the result
 */
RAPPCloud.prototype.geolocation = function(
                                            ipaddr,
                                            engine,
                                            callback
                                          )
{
    var cloud = this;
    var _delegate = callback;
    var request = cloud.determine_protocol();

    var body_obj = {};
    body_obj.ipaddr = cloud.escape_string(ipaddr);
    body_obj.engine = cloud.escape_string(engine);
    var body_json = JSON.stringify(body_obj);
    
    request.post({
        headers: {
			'Accept-Token' : cloud.token,
			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/geolocation/ ',
        body: "json=" + body_json
    },
    function(error, response, json) 
    {
        if (!error && response.statusCode == 200)
            handle_reply(json);
        else if (error)
            error_handler(error);
        else if (response.statusCode != 200)
            console.log('Error: ' + response.statusCode);
    });
    
    function handle_reply(json)
    {
		var json_obj;
		try {
			json_obj = JSON.parse(json);
			// JSON reply is: { city: '', country: '', country_code: '', 
            // latitude: 0.0, longtitude: 0.0, region: '', timezone: '',
            // zip: '', error: '' }	
            //
		    // city: (String): The city.
		    // country (String): The country.
		    // country_code (String): The country code.
		    // latitude: (Float): The latitude.
		    // longtitude (Float): The longtitude.
		    // timezone (String): The timezone.
		    // zip (String): The zip postal code.
		    // error (String): Error message, if one occures.
		
			if(json_obj.error)  // Check for Errors  
				console.log('geolocation JSON error: ' + json_obj.error);
	        else 
	        	_delegate(
                            json_obj.city,
                            json_obj.country,
                            json_obj.country_code,
                            json_obj.latitude,
                            json_obj.longtitude,
                            json_obj.timezone,
                            json_obj.zip
                         );
		} catch (e) {
			console.log('geolocation::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler(error) {
		return console.error(error);
	}   
};

/// Export
module.exports = RAPPCloud.geolocation;
