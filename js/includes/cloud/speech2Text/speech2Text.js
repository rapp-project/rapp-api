#!/usr/bin/env node

var RAPPCloud = require('./../../../RAPPCloud.js');
var FormData = require('form-data');
var fs = require('fs');
var request = require('request');
var randomstring = require('randomstring');

/**
 * Prototype the RAPPCloud Service Method.
 *
 * @method speech2Text
 * @brief Asynchronous Service which will request the cloud to process speech-to-text
 * @version 1
 * @date 06-October-2015
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 */ 

/**
 * @brief Contrusct a speechToText handler
 * @param audio is the actual binary sound file
 * @param language is the language used for speech to text
 * @param user is the user token
 * @param audio_source is a string with the audio source type
 * @param grammar is the Grammars used in Spc2Txt
 * @param words will be searched for in the audio
 * @param sentences will be under consideration
 * @param callback will be executed once the rapp cloud has responded
 */
 
RAPPCloud.prototype.speech2Text = function ( audio, language, user, audio_source, grammar, words, sentences, callback )
{
    var cloud = this;
    var _delegate=callback;
	var form = new FormData();
	var ext = audio.substr(audio.lastIndexOf('.') + 1);
	var filename = randomstring.generate() + '.' + ext;
	
	var grammar_str = '[';
	for (i=0; i<grammar.length; i++) {
		grammar_str += '"' + grammar[i] + '"';
		if ( i != grammar.length-1 ) grammar_str += ',';
	}
	grammar_str += ']';
	
	var sentences_str = '[';
	for (i=0; i<sentences.length; i++) {
		sentences_str += '"' + sentences[i] + '"';
		if ( i != sentences.length-1 ) sentences_str += ',';
	}
	sentences_str += ']';
	
	var words_str = '[';
	for (i=0; i<words.length; i++) {
		words_str += '"' + words[i] + '"';
		if ( i != words.length-1 ) words_str += ',';
	}
	words_str += ']';
	
	form.append('file_uri', fs.createReadStream(audio), { filename: filename });
	form.append('language', language);
	form.append('user', user);
	form.append('audio_source', audio_source);
	form.append('grammar', grammar_str);
	form.append('words', words_str);
	form.append('sentences', sentences_str);
	
	var r = request.post(cloud.cloud_url + '/hop/speech_detection_sphinx4/ ', function(error, res, json){ 
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
		var words_vector = [];
		try {
			json_obj = JSON.parse(json);
			if(json_obj.error){  // Check for Errors returned by the api.rapp.cloud
				console.log('speech2Text JSON error: ' + json_obj.error);
			}
			// JSON reply is eg.: {"words":["check","my","emails"],"error":""}
			for (i=0; i<json_obj.words.length; i++){
				words_vector.push(json_obj.words[i]);
			}
			_delegate(words_vector);
		} catch (e) {
			console.log("speech2Text::handle_reply Error parsing: ");
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}
}



/// Export
module.exports = RAPPCloud.speech2Text;
