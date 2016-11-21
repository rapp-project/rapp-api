#!/usr/bin/env node

// Import the face_detection JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('rapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.set_noise_profile = require('rapp-platform-api/includes/cloud/set_noise_profile');
var services = new RAPPCloud( );

services.set_noise_profile ("../../testdata/denoise_source.wav",
                            //"../../testdata/../../testdata/silence_sample.wav",
                            // "../../testdata/silence_wav_d05_a1.wav",
                            //"../../testdata/silence_ogg_d05_a1.ogg",
							"nao_wav_1_ch"
                            //"nao_wav_4_ch" 
                            //"nao_ogg"
                            );
