#!/usr/bin/env node

// Import the speech_recognition_google JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('rapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.speech_recognition_google = require('rapp-platform-api/includes/cloud/speech_recognition_google');

var services = new RAPPCloud( );

var audio = //"nao_wav_d05_a1.wav_mono16k.wav";
		    //"yes-no.wav";
			//"nao_wav_d05_a1.wav";
			//"nao_ogg_d05_a1.ogg"; 
		     "../../testdata/recording_sentence2.ogg";
             //"recording_sentence2.ogg";
		     //"email-robot.wav";
		     //"recording_yes.ogg";
		     //"recording_no.ogg";
		     //"recording_tuesday.ogg";
		     //"recording_triti.ogg";
		    				   
/** 
 * This is the method that will handle the reply by the services.speech_recognition_google
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
 
function handler ( possible_vectors )
{
    if ( possible_vectors.length ) {
		console.log ( 'Found ' + possible_vectors.length + ' possible vectors of detected words:');
		for (var i=0; i < possible_vectors.length; i++) {
			console.log( 'Possible sentence ' + i + ': ');
			for (var j=0; j < possible_vectors[i].length; j++) {
				  console.log( possible_vectors[i][j] + ' ' );
			  }
		}
	}
	else
		console.log ( 'No words found');
}

services.speech_recognition_google( audio,           // audio file
								"nao_ogg",       // Audio Source Type
								"en",            // Language
								//"headset",
								//"nao_wav_1_ch",
								//"nao_wav_4_ch",
								handler );
	
