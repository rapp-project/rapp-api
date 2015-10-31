#!/usr/bin/env node

// Import the faceDetector JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('./../RAPPCloud.js')
RAPPCloud.setDenoiseProfile = require('./../includes/cloud/setDenoiseProfile/setDenoiseProfile.js');
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
