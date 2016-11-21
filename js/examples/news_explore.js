#!/usr/bin/env node

// Import the news_explore JS API Services & Init the RAPPCloud Object
var RAPPCloud = require('rapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.news_explore = require('rapp-platform-api/includes/cloud/news_explore');

var services = new RAPPCloud( );

/** 
 * This is the method that will handle the reply by the service.news_explore
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function callback ( news_stories )
{
    for (var i=0; i<news_stories.length; i++)
    	console.log ( news_stories[i] );
}

services.news_explore( 'msn', ['Athens'], [], 'Greece', 'politics', 2, callback );
