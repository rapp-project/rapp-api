#!/usr/bin/env node

var test = require('unit.js');

// Import the JS API Services & Init the RAPPCloud Object
var RAPPCloud = require('./../RAPPCloud.js');
RAPPCloud.ontologySubclassesOf = require('./../includes/cloud/ontologySubclassesOf/ontologySubclassesOf.js');
RAPPCloud.ontologySuperclassesOf = require('./../includes/cloud/ontologySuperclassesOf/ontologySuperclassesOf.js');
RAPPCloud.ontologySubSuperClassOf = require('./../includes/cloud/ontologySubSuperClassOf/ontologySubSuperClassOf.js');
RAPPCloud.qrDetector = require('./../includes/cloud/qrDetector/qrDetector.js');
RAPPCloud.faceDetector = require('./../includes/cloud/faceDetector/faceDetector.js');
RAPPCloud.speech2Text = require('./../includes/cloud/speech2Text/speech2Text.js');
RAPPCloud.setDenoiseProfile = require('./../includes/cloud/setDenoiseProfile/setDenoiseProfile.js');
var services = new RAPPCloud( );


describe('#faceDetector()', function(){
  it('should detect faces given an image and the image type', function(done){
    services.faceDetector( './two_faces.jpg', 'jpg', function(faces) {
		console.log('found ' + faces.length + ' faces');
        done();
		});
  });  
});

describe('#qrDetector()', function(){
  it('should detect qr codes given an image and the image type', function(done){
    services.faceDetector( './qrcode.png', 'png', function(codes) {
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
    services.setDenoiseProfile ( "denoise_source.wav", "rapp", "nao_wav_1_ch" );
    done();
  });  
});

describe('#speech2Text()', function(){
  it('should detect the words given an audio file, the language, a user token, the audio source type, a grammar, a pool of words and a pool of sentences', function(done){
    services.speech2Text( './recording_sentence2.ogg', "en", "rapp", "nao_ogg", [], ["check", "my", "emails", "robot"], ["check", "my", "emails", "robot"], function(words) {
		console.log ( 'Found ' + words.length + ' words');
        done();
		});
  });  
});
