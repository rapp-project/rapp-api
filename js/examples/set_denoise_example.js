#!/usr/bin/env node

var path = require('path');

// Import the faceDetector JS API Service & Init the RAPPCloud Object
var __cloudDir = path.join(__dirname, '..', 'includes', 'cloud');
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));
RAPPCloud.setDenoiseProfile = require(path.join(__cloudDir, 'setDenoiseProfile.js'));

var services = new RAPPCloud( );

services.setDenoiseProfile ("denoise_source.wav",
                            //"silence_sample.wav",
                            // "silence_wav_d05_a1.wav",
                            //"silence_ogg_d05_a1.ogg",
                             
							"rapp",
							"nao_wav_1_ch"
                            //"nao_wav_4_ch" 
                            //"nao_ogg"
                            );
