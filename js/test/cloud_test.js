#!/usr/bin/env node

var test = require('unit.js');
var path = require('path');

// Import the faceDetector JS API Service & Init the RAPPCloud Object
var __cloudDir = path.join(__dirname, '..', 'includes', 'cloud');
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));
RAPPCloud.ontologySubclassesOf = require(path.join(__cloudDir, 'ontologySubclassesOf.js'));
RAPPCloud.ontologySuperclassesOf = require(path.join(__cloudDir, 'ontologySuperclassesOf.js'));
RAPPCloud.ontologySubSuperClassOf = require(path.join(__cloudDir, 'ontologySubSuperClassOf.js'));
RAPPCloud.qrDetector = require(path.join(__cloudDir, 'qrDetector.js'));
RAPPCloud.faceDetector = require(path.join(__cloudDir, 'faceDetector.js'));
RAPPCloud.setNoiseProfile = require(path.join(__cloudDir, 'setNoiseProfile.js'));
RAPPCloud.speechDetectionSphinx4 = require(path.join(__cloudDir, 'speechDetectionSphinx4.js'));
RAPPCloud.speechDetectionGoogle = require(path.join(__cloudDir, 'speechDetectionGoogle.js'));

var services = new RAPPCloud( );


describe('#faceDetector()', function(){
  it('should in all cases create a faceDetector object given an image, the image type and a callback function', function(done){
    services.faceDetector( path.join(__dirname, 'two_faces.jpg'), "jpg", done());
  });
});

describe('#qrDetector()', function(){
  it('should in all cases create a qrDetector object given an image, the image type and a callback function', function(done){
    services.qrDetector( path.join(__dirname, 'qrcode.png'), "png", done());
  });
});

describe('#ontologySubclassesOf()', function(){
  it('should in all cases create an ontologySubclassesOf object given an argument class and a callback function', function(done){
    services.ontologySubclassesOf('Oven', done());
  });
});+

describe('#ontologySuperclassesOf()', function(){
  it('should in all cases create an ontologySuperclassesOf object given an argument class and a callback function', function(done){
    services.ontologySuperclassesOf('Oven', done());
  });
});

describe('#ontologySubSuperclassOf()', function(){
  it('should in all cases create an ontologySubSuperclassOf object given a parent, a child, a boolean and a callback function as arguments', function(done){
    services.ontologySubSuperClassOf( 'Box-Container', 'MicrowaveOven', true, done());
  });  
});

describe('#setNoiseProfile()', function(){
  it("should in all cases create a setNoiseProfile object given an audio file, username and audio type as arguments", function(){
	services.setNoiseProfile ( path.join(__dirname, 'denoise_source.wav'), "rapp", "nao_wav_1_ch" );
  });
});

describe('#speechDetectionSphinx4()', function(){
  it('should in all cases create a speechDetectionSphinx4 object given an audio file, the language, a user token, the audio source type, a grammar, a pool of words, a pool of sentences and a callback function as arguments', function(done){
    services.speechDetectionSphinx4( path.join(__dirname, 'recording_sentence2.ogg'), "en", "rapp", "nao_ogg", [], ["check", "my", "emails", "robot"], ["check", "my", "emails", "robot"], done());
  });  
});

describe('#speechDetectionGoogle()', function(){
  it('should in all cases create a speechDetectionGoogle object given an audio file, the audio source type, a user token, a language and a callback function as arguments', function(done){
    services.speechDetectionGoogle( path.join(__dirname, 'recording_sentence2.ogg'), "nao_ogg", "rapp", "en", done());
  });  
});
