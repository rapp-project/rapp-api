#!/usr/bin/env node

var path = require('path');
var __cloudDir = path.join(__dirname);
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));
const config = require("../../config/config");

if (config.protocol === "https")
{
    var request = require('request').defaults({
	    secureProtocol: 'TLSv1_2_method',
	    rejectUnauthorized: false
	});
}
else if (config.protocol === "http")
{
    var request = require("request");
}
else
{
    console.log("please choose one of: http or https(for TLS_1.2) as protocols");
}

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 *
 * @class speech_recognition_google
 * @description Asynchronous Service which will request the cloud to process speech-to-text
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param audio is the actual binary sound file
 * @param audio_source is a string with the audio source type
 * @param language is the language used for speech to text
 * @param callback will be executed once the rapp cloud has responded
 */
 
RAPPCloud.prototype.speech_recognition_google = function ( audio, audio_source, language, callback )
{
    var formData = require('form-data');
	var randomstring = require('randomstring');
	var fs = require('fs');

    var cloud = this;
    var _delegate=callback;

	var form = new formData();
	var ext = audio.substr(audio.lastIndexOf('.') + 1);
	//Generate a random file name under which the audio file will be saved on the Server 
	var filename = randomstring.generate() + '.' + ext;
	
	var body_obj = {};
    body_obj.audio_source = audio_source;
    body_obj.language = language;
    var body_json = JSON.stringify(body_obj);

	form.append('file', fs.createReadStream(audio), { filename: filename });
	form.append('json', body_json);
	
	var r = request.post(cloud.cloud_url + '/hop/speech_detection_google/ ', function(error, res, json){ 
		if (res.statusCode==200 && !error){
			handle_reply(json);
			}
		else if (error) {
			error_handler(error);
		}
		else if ( res.statusCode != 200 ) {
			console.log(res.statusCode);
		}
	});
	r._form = form;
	r.setHeader('Connection', 'close');
	r.setHeader('Accept-Token', cloud.token);

	function handle_reply( json )
    {
		var json_obj;
		try {
			var i;
			json_obj = JSON.parse(json);
			if(json_obj.error){  // Check for Errors  
				console.log('speech_recognition_google JSON error: ' + json_obj.error);
			}
			// JSON reply is eg.: {"words":["check","minus"],"alternatives":[["check","-"],["check","my","mail"],["Tech","-"],["take","-"],["10","-"],["check","cashing"],["check","in"],["check","cash"]],"error":""}
			var possible_vectors = new Array(json_obj.alternatives.length + 1);
			
			possible_vectors[0] = new Array(json_obj.words.length);
			for (i = 0; i < json_obj.alternatives.length; i++) {
				possible_vectors[i+1] = new Array(json_obj.alternatives[i].length);
			}
			
			for (i=0; i<json_obj.words.length; i++){
				possible_vectors[0][i] = json_obj.words[i]; //add the primary detected word vector
			}
			for (i=0; i<json_obj.alternatives.length; i++){
				for (var j=0; j<json_obj.alternatives[i].length; j++) {
					possible_vectors[i+1][j] = json_obj.alternatives[i][j];
				}
			}
			_delegate(possible_vectors);
		} catch (e) {
			console.log('speech_recognition_google::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}
};



/// Export
module.exports = RAPPCloud.speech_recognition_google;
