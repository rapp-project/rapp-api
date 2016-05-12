#!/usr/bin/env node

// Import the face_detection JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../includes/cloud/RAPPCloud.js');
RAPPCloud.set_noise_profile = require('../includes/cloud/set_noise_profile.js');
var services = new RAPPCloud( );

services.set_noise_profile ("denoise_source.wav",
                            //"silence_sample.wav",
                            // "silence_wav_d05_a1.wav",
                            //"silence_ogg_d05_a1.ogg",
							"nao_wav_1_ch"
                            //"nao_wav_4_ch" 
                            //"nao_ogg"
                            );
