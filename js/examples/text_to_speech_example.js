#!/usr/bin/env node

var fs = require('fs');
// Import the text_to_speech JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../lib/cloud/RAPPCloud');
RAPPCloud.text_to_speech = require('../lib/cloud/text_to_speech');
var services = new RAPPCloud();

var text = 'Hello human';

/** 
 * This is the method that will handle the reply by the services.text_to_speech
 */
function handler(audio_data, encoding, basename)
{
	var path = '../testdata/audio_tts/' + basename;
	fs.writeFile(path, audio_data, encoding, function(err) {
	    if(err) {
	        return console.log(err);
	    }
	    console.log('The file was saved under ../testdata/audio_tts/' + basename);
	}); 
}

services.text_to_speech(text, 'en', handler);
