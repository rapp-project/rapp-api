#!/usr/bin/env node

// Import the geolocation JS API Services & Init the RAPPCloud Object
var RAPPCloud = require('../includes/cloud/RAPPCloud');
RAPPCloud.geolocation = require('../includes/cloud/geolocation');

var services = new RAPPCloud( );

/** 
 * This is the method that will handle the reply by the service.geolocation
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function callback ( city, country, country_code, latitude, longtitude, timezone, zip )
{
    console.log ( 'city: ' + city + "\ncountry: " + country + "\ncountry_code: " + country_code + "\nlatitude: " + latitude + "\nlongtitude: " + longtitude + "\ntimezone: " + timezone + "\nzip: " + zip );
}

services.geolocation( '155.207.33.185', '', callback );
