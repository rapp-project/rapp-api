#!/usr/bin/env node

// Import the weather_report_current JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('rapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.weather_report_current = require('rapp-platform-api/includes/cloud/weather_report_current');

var services = new RAPPCloud( );

/** 
 * This is the method that will handle the reply by the service.weather_report_current
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function callback ( weather )
{
//    date: '', temperature: '', weather_description: '', humidity: '', visibility: '', pressure: '', wind_speed: '', wind_temperature: '', wind_direction: ''
//    var str = JSON.stringify(weather, null, 2);
//    console.log(str);
console.log(weather);
}

services.weather_report_current( 'Athens', '', 0, callback );
