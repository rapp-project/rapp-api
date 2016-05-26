#!/usr/bin/env node

// Import the speech_detection_sphinx4 JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('rapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.speech_detection_sphinx4 = require('rapp-platform-api/includes/cloud/speech_detection_sphinx4');

var services = new RAPPCloud( );

var audio = //"../../testdata/nao_wav_d05_a1.wav_mono16k.wav";
			//"../../testdata/yes-no.wav";
			//"../../testdata/nao_wav_d05_a1.wav";
			//"../../testdata/nao_ogg_d05_a1.ogg"; 
		     "../../testdata/recording_sentence2.ogg";
		     //"../../testdata/email-robot.wav";
		     //"../../testdata/recording_yes.ogg";
		     //"../../testdata/recording_no.ogg";
		     //"../../testdata/recording_tuesday.ogg";
		     //"../../testdata/recording_triti.ogg";    
var grammar = [];
var words = //["tuesday", "monday"];
					   //["yes", "no"];
					   //["i", "want", "to", "go", "out"];
					   //["email", "robot"];
					   ["check", "my", "emails", "robot"];
					   //["Τρίτη", "Δευτέρα"];
					   
var sentences = //["tuesday", "monday"];
					   //["yes", "no"];
					   //["i", "want", "to", "go", "out"];
					   //["email", "robot"];
					   ["check", "my", "emails", "robot"];
					   //["Τρίτη", "Δευτέρα"];					   

/** 
 * This is the method that will handle the reply by the services.speech_detection_sphinx4
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
 
function handler ( words_detected )
{
    if ( words_detected.length ) {
		console.log ( 'Found ' + words_detected.length + ' words:');
		for (var i=0; i < words_detected.length; i++) {
			console.log( words_detected[i] );
		}
	}
	else
		console.log ( 'No words found');
}

services.speech_detection_sphinx4( audio,           // audio file
								"en",            // Language
								//"headset",
								//"nao_wav_1_ch",
								//"nao_wav_4_ch",
								"nao_ogg",       // Audio Source Type
								grammar,         // grammar ? (empty)
								words,           // words to be considered
								sentences,       // sentences to be considered
								handler );
