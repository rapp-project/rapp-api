#!/usr/bin/env node

// Import the weather_report_current JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../includes/cloud/RAPPCloud.js');
RAPPCloud.weather_report_current = require('../includes/cloud/weather_report_current.js');

var services = new RAPPCloud( );

/** 
 * This is the method that will handle the reply by the service.weather_report_current
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function callback ( weather )
{
//    date: '', temperature: '', weather_description: '', humidity: '', visibility: '', pressure: '', wind_speed: '', wind_temperature: '', wind_direction: ''
//    var weather_json = JSON.parse(weather);
    var str = JSON.stringify(weather, null, 2);
    console.log(str);
}

services.weather_report_current( 'Athens', '', 0, callback );
