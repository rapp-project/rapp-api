#!/usr/bin/env node

var path = require('path');
var formData = require('form-data');
var randomstring = require('randomstring');
var fs = require('fs');
var __cloudDir = path.join(__dirname);
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class set_noise_profile
 * @memberof RAPPCloud
 * @description Setting the denoising audio profile for speech recognition
 * @version 0.7.5
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param file is the input audio file
 * @param audio_source is a string with the audio source type
 */
RAPPCloud.prototype.set_noise_profile = function(
                                                  file, 
                                                  audio_source
                                                )
{
    var cloud = this;
    var request = cloud.determine_protocol();
	var form = new formData();
	var ext = file.substr(file.lastIndexOf('.') + 1);
	//Generate a random file name under which the audio file will be saved on the Server 
	var filename = randomstring.generate() + '.' + ext;
	var body_obj = {};
    body_obj.audio_source = audio_source;
    var body_json = JSON.stringify(body_obj);

	form.append('file', fs.createReadStream(file), { 
		filename: filename
	});
	form.append('json', body_json);
	
	var r = request.post(cloud.cloud_url + '/hop/set_noise_profile/ ',
    function(error, res, json)
    { 
		if (res.statusCode==200 && !error){
			handle_reply(json);
			}
		else if (error) {
			error_handler(error);
		}
		else if (res.statusCode != 200) {
			console.log(res.statusCode);
		}
	});
	r._form = form;
	r.setHeader('Connection', 'close');
	r.setHeader('Accept-Token', cloud.token);

	function handle_reply(json)
    {
		var json_obj;
		try {
			json_obj = JSON.parse(json);
			if(json_obj.error){  // Check for Errors  
				console.log('set_noise_profile JSON error: ' + json_obj.error);
			}	
		} catch (e) {
			console.log('set_noise_profile::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler(error) {
		return console.error(error);
	}
};



/// Export
module.exports = RAPPCloud.set_noise_profile;
