#!/usr/bin/env node

// Import the weather_report_current JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../lib/cloud/RAPPCloud');
RAPPCloud.weather_report_current = require('../lib/cloud/weather_report_current');

var services = new RAPPCloud();

/** 
 * This is the method that will handle the reply by the service.weather_report_current
 */
function callback(weather)
{
    //    date: '', temperature: '', weather_description: '', humidity: '',
    //    visibility: '', pressure: '', wind_speed: '', wind_temperature: '',
    //    wind_direction: ''
    console.log(weather);    
}

services.weather_report_current('Thessaloniki', '', 0, callback);
