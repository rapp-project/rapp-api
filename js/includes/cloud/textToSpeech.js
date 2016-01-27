#!/usr/bin/env node

var request = require('request');
var path = require('path');

var __cloudDir = path.join(__dirname);

var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 *
 * @class textToSpeech
 * @description Asynchronous Service which will request the cloud to process TTS
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param text is the text to become speech
 * @param language is the language of the text
 * @param callback will be executed once the rapp cloud has responded
 */
 
RAPPCloud.prototype.textToSpeech = function ( text, language, callback )
{
	var cloud = this;
    var body_string = 'text=' + text + '&language=' + language;
    var _delegate = callback;
    
    request.post({
        headers: {
//			'Authorization' : 'Basic cmFwcGRldjpyYXBwZGV2',
			'Content-Type' : 'application/x-www-form-urlencoded',
			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/text_to_speech/ ',
        body: body_string
    },
    function ( error, response, json ) 
    {
        if ( !error && response.statusCode == 200)
            handle_reply( json );
        else if ( error )
            error_handler ( error );
        else if ( response.statusCode != 200 )
            console.log ( "Error: " + response.statusCode );
    });
    
    function handle_reply( json )
    {
		var json_obj;
		try {
			json_obj = JSON.parse(json);
			// JSON reply is: { payload: <audio_data>, basename: <audio_file_basename>, encoding: <payload_encoding>, error: <error_message> }
		
			if(json_obj.error){  // Check for Errors returned by the api.rapp.cloud
				console.log('textToSpeech JSON error: ' + json_obj.error);
			}
			_delegate( json_obj.payload, json_obj.encoding, json_obj.basename);
		} catch (e) {
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}	
};


/// Export
module.exports = RAPPCloud.textToSpeech;
