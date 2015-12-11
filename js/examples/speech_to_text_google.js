#!/usr/bin/env node

var path = require('path');

// Import the faceDetector JS API Service & Init the RAPPCloud Object
var __cloudDir = path.join(__dirname, '..', 'includes', 'cloud');
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));
RAPPCloud.speechDetectionGoogle = require(path.join(__cloudDir, 'speechDetectionGoogle.js'));

var services = new RAPPCloud( );

/** 
 * This is the method that will handle the reply by the services.speech2Text
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
 
 var audio = //"nao_wav_d05_a1.wav_mono16k.wav";
										 //"yes-no.wav";
										 //"nao_wav_d05_a1.wav";
										 //"nao_ogg_d05_a1.ogg"; 
		     "recording_sentence2.ogg";
		     //"email-robot.wav";
		     //"recording_yes.ogg";
		     //"recording_no.ogg";
		     //"recording_tuesday.ogg";
		     //"recording_triti.ogg";
		    				   
 
function handler ( possible_vectors )
{
    if ( possible_vectors.length ) {
		console.log ( 'Found ' + possible_vectors.length + ' possible vectors of detected words:\n');
		for (i=0; i < possible_vectors.length; i++) {
			console.log( 'Possible sentence ' + i + ': ');
			for (j=0; j < possible_vectors[i].length; j++) {
				  console.log( possible_vectors[i][j] + ' ' );
			  }
		}
	}
	else
		console.log ( 'No words found');
}

services.speechDetectionGoogle( audio,           // audio file
								"nao_ogg",       // Audio Source Type
								"rapp",          // user
								"en",            // Language
								//"headset",
								//"nao_wav_1_ch",
								//"nao_wav_4_ch",
								handler );
	
