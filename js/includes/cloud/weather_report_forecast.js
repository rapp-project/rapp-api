#!/usr/bin/env node

var path = require('path');
var __cloudDir = path.join(__dirname);
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class weather_report_forecast
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the weather_report_forecast RAPP platform service
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param city (String): The desired city
 * @param weather_reporter (String): The weather API to use. Defaults to "yweather" .
 * @param metric (Integer): The return value units.
 * @param callback is the function that will receive the result
 */

RAPPCloud.prototype.weather_report_forecast = function ( city, weather_reporter, metric, callback )
{
    var request = require('request').defaults({
	  secureProtocol: 'TLSv1_2_method',
	  rejectUnauthorized: false
	});

    var cloud = this;
    var _delegate = callback;
    
    var body_obj = {};
    body_obj.city = cloud.escape_string(city);
    body_obj.weather_reporter = cloud.escape_string(weather_reporter);
    body_obj.metric = metric;
    var body_json = JSON.stringify(body_obj);
    
    request.post({
        headers: {
			'Accept-Token' : cloud.token,
			'Content-Type' : 'application/x-www-form-urlencoded',
			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/weather_report_forecast/ ',
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
			// JSON reply is: { forecast: [{<forecastEntry_1>}, ...,  {<forecastEntry_n>}], error: '' }
		
			if(json_obj.error){  // Check for Errors  
				console.log('weather_report_forecast JSON error: ' + json_obj.error);
			}
			_delegate( json_obj.forecast );
		} catch (e) {
			console.log('weather_report_forecast::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}   
};

/// Export
module.exports = RAPPCloud.weather_report_forecast;
