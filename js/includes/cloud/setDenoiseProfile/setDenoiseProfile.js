#!/usr/bin/env node

var RAPPCloud = require('./../../../RAPPCloud.js');
var FormData = require('form-data');
var fs = require('fs');
var request = require('request');

/**
 * Prototype the RAPPCloud Service Method.
 * 
 * @method setDenoiseProfile
 * @brief Setting the denoising audio profile for speech recognition
 * @version 1
 * @date 29-September-2015
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 */ 

/**
 * @brief Constructor
 * @param file is the input audio file
 * @param user is a string with the username
 * @param audio_source is a string with the audio source type
 */

RAPPCloud.prototype.setDenoiseProfile = function ( file, user, audio_source )
{
    var cloud = this;    
	var form = new FormData();
	
	form.append('user', user);
	form.append('audio_source', audio_source);
	form.append('file_uri', fs.createReadStream(file));
	
	var r = request.post(cloud.cloud_url + '/hop/set_denoise_profile/ ', function(error, res, json){ 
		if (res.statusCode==200 && !error){
			handle_reply(json);
			}
		else if (error) {
			error_handler(error);
		}
		else if ( response.statusCode != 200 ) {
			console.log(res.statusCode);
		}
	});
	r._form = form;
	r.setHeader('Connection', 'close');

	function handle_reply( json )
    {
		var json_obj;
		try {
			json_obj = JSON.parse(json);
			if(json_obj.error){  // Check for Errors returned by the api.rapp.cloud
				console.log('setDenoiseProfile JSON error: ' + json_obj.error);
			}
			
		} catch (e) {
			console.log("qrDetector::handle_reply Error parsing: ");
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}
}



/// Export
module.exports = RAPPCloud.setDenoiseProfile;
