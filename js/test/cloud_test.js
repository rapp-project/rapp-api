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
RAPPCloud.qrDetector = require(path.join(__cloudDir, 'setDenoiseProfile.js'));
RAPPCloud.speech2Text = require(path.join(__cloudDir, 'speech2Text.js'));

var services = new RAPPCloud( );


describe('#faceDetector()', function(){
  it('should detect faces given an image and the image type', function(done){
    services.faceDetector( path.join(__dirname, 'two_faces.jpg'), "jpg", function(faces) {
		console.log('found ' + faces.length + ' faces');
        done();
		});
  });  
});

describe('#qrDetector()', function(){
  it('should detect qr codes given an image and the image type', function(done){
    services.qrDetector( path.join(__dirname, 'qrcode.png'), "png", function(codes) {
		console.log('found ' + codes.length + ' codes');
        done();
		});
  });  
});

describe('#ontologySubclassesOf()', function(){
  it('should discover the Subclasses of the given as argument class', function(done){
    services.ontologySubclassesOf('Oven', function(classes) {
		console.log('found ' + classes.length + ' classes');
        done();
		});
  });  
});

describe('#ontologySuperclassesOf()', function(){
  it('should discover the Superclasses of the given as argument class', function(done){
    services.ontologySuperclassesOf('Oven', function(classes) {
		console.log('found ' + classes.length + ' classes');
        done();
		});
  });  
});

describe('#ontologySubSuperclassOf()', function(){
  it('should check whether there is a parent child relationship of the given as arguments classes', function(done){
    services.ontologySubSuperClassOf( 'Box-Container', 'MicrowaveOven', true, function( Parent, Child, result ) {
		console.log ( Parent + ' is Superclass of ' + Child + ': ' + result.toString() );
        done();
		});
  });  
});

describe('#setDenoiseProfile()', function(){
  it("should set a user's denoising audio profile for speech recognition", function(done){
    services.setDenoiseProfile ( path.join(__dirname, 'denoise_source.wav'), "rapp", "nao_wav_1_ch" );
    done();
  });  
});

describe('#speech2Text()', function(){
  it('should detect the words given an audio file, the language, a user token, the audio source type, a grammar, a pool of words and a pool of sentences', function(done){
    services.speech2Text( path.join(__dirname, 'recording_sentence2.ogg'), "en", "rapp", "nao_ogg", [], ["check", "my", "emails", "robot"], ["check", "my", "emails", "robot"], function(words) {
		console.log ( 'Found ' + words.length + ' words');
        done();
		});
  });  
});
