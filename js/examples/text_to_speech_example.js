#!/usr/bin/env node

// Import the text_to_speech JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../includes/cloud/RAPPCloud.js');
RAPPCloud.text_to_speech = require('../includes/cloud/text_to_speech.js');

var services = new RAPPCloud( );

var text = "Hello human";

/** 
 * This is the method that will handle the reply by the services.text_to_speech
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
 
function handler ( audio_data, encoding, basename )
{
	var fs = require('fs');
	var path = "audio/" + basename;
	fs.writeFile(path, audio_data, encoding, function(err) {
	    if(err) {
	        return console.log(err);
	    }
	    console.log("The file was saved under audio/" + basename );
	}); 
}

services.text_to_speech( text, "en", handler );
