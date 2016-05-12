#!/usr/bin/env node

// Import the weather_report_forecast JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../includes/cloud/RAPPCloud.js');
RAPPCloud.weather_report_forecast = require('../includes/cloud/weather_report_forecast.js');

var services = new RAPPCloud( );

/** 
 * This is the method that will handle the reply by the service.weather_report_forecast
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function callback ( forecast )
{
//    date: '', temperature: '', weather_description: '', humidity: '', visibility: '', pressure: '', wind_speed: '', wind_temperature: '', wind_direction: ''
//    var weather_json = JSON.parse(weather);
    for (var i=0; i<forecast.length; i++) {
    	var str = JSON.stringify(forecast[i], null, 2);
    	console.log(str);
    }
}

services.weather_report_forecast( 'Athens', '', 0, callback );
