#!/usr/bin/env node

var path = require('path');
var __cloudDir = path.join(__dirname);
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 *
 * @class speech_detection_sphinx4
 * @description Asynchronous Service which will request the cloud to process speech-to-text
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param audio is the actual binary sound file
 * @param language is the language used for speech to text
 * @param audio_source is a string with the audio source type
 * @param grammar is the Grammars used in Spc2Txt
 * @param words will be searched for in the audio
 * @param sentences will be under consideration
 * @param callback will be executed once the rapp cloud has responded
 */
 
RAPPCloud.prototype.speech_detection_sphinx4 = function ( audio, language, audio_source, grammar, words, sentences, callback )
{
    var formData = require('form-data');
	var randomstring = require('randomstring');
	var fs = require('fs');
	var request = require('request').defaults({
	  secureProtocol: 'TLSv1_2_method',
	  rejectUnauthorized: false
	});

    var cloud = this;
    var _delegate=callback;

	var form = new formData();
	var ext = audio.substr(audio.lastIndexOf('.') + 1);
	//Generate a random file name under which the audio file will be saved on the Server 
	var filename = randomstring.generate() + '.' + ext;
	
	var i;
	var grammar_str = '[';
	for (i=0; i<grammar.length; i++) {
		grammar_str += '"' + grammar[i] + '"';
		if ( i != grammar.length-1 ) grammar_str += ',';
	}
	grammar_str += ']';
	
	var sentences_str = '[';
	for (i=0; i<sentences.length; i++) {
		sentences_str += '"' + cloud.escape_string(sentences[i]) + '"';
		if ( i != sentences.length-1 ) sentences_str += ',';
	}
	sentences_str += ']';
	
	var words_str = '[';
	for (i=0; i<words.length; i++) {
		words_str += '"' + cloud.escape_string(words[i]) + '"';
		if ( i != words.length-1 ) words_str += ',';
	}
	words_str += ']';
	

	var body_obj = new Object();
    body_obj.language = language;
    body_obj.audio_source = audio_source;
    body_obj.grammar = grammar;
    body_obj.words = words;
    body_obj.sentences = sentences;
    var body_json = JSON.stringify(body_obj);

	form.append('file', fs.createReadStream(audio), { filename: filename });
	form.append('json', body_json);
	
	var r = request.post(cloud.cloud_url + '/hop/speech_detection_sphinx4/ ', function(error, res, json){ 
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
		var words_vector = [];
		try {
			json_obj = JSON.parse(json);
			if(json_obj.error){  // Check for Errors  
				console.log('speech_detection_sphinx4 JSON error: ' + json_obj.error);
			}
			// JSON reply is eg.: {"words":["check","my","emails"],"error":""}
			for (i=0; i<json_obj.words.length; i++){
				words_vector.push(json_obj.words[i]);
			}
			_delegate(words_vector);
		} catch (e) {
			console.log('speech_detection_sphinx4::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}
};



/// Export
module.exports = RAPPCloud.speech_detection_sphinx4;
