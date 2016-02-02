#!/usr/bin/env node

var test = require('unit.js');
var path = require('path');

// Import the JS API Services & Init the RAPPCloud Object
var __cloudDir = path.join(__dirname, '..', 'includes', 'cloud');
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));
RAPPCloud.ontology_subclasses_of = require(path.join(__cloudDir, 'ontology_subclasses_of.js'));
RAPPCloud.ontology_superclasses_of = require(path.join(__cloudDir, 'ontology_superclasses_of.js'));
RAPPCloud.ontology_is_subsuperclass_of = require(path.join(__cloudDir, 'ontology_is_subsuperclass_of.js'));
RAPPCloud.qr_detection = require(path.join(__cloudDir, 'qr_detection.js'));
RAPPCloud.face_detection = require(path.join(__cloudDir, 'face_detection.js'));
RAPPCloud.set_noise_profile = require(path.join(__cloudDir, 'set_noise_profile.js'));
RAPPCloud.speech_detection_sphinx4 = require(path.join(__cloudDir, 'speech_detection_sphinx4.js'));
RAPPCloud.speech_detection_google = require(path.join(__cloudDir, 'speech_detection_google.js'));
RAPPCloud.available_services = require(path.join(__cloudDir, 'available_services.js'));
RAPPCloud.cognitive_test_chooser = require(path.join(__cloudDir, 'cognitive_test_chooser.js'));
RAPPCloud.record_cognitive_test_performance = require(path.join(__cloudDir, 'record_cognitive_test_performance.js'));
RAPPCloud.text_to_speech = require(path.join(__cloudDir, 'text_to_speech.js'));

var services = new RAPPCloud( );


describe('#face_detection()', function(){
  it('should in all cases create a face_detection object given an image, the image type and a callback function', function(done){
    services.face_detection( path.join(__dirname, 'two_faces.jpg'), "jpg", done());
  });
});

describe('#qr_detection()', function(){
  it('should in all cases create a qr_detection object given an image, the image type and a callback function', function(done){
    services.qr_detection( path.join(__dirname, 'qrcode.png'), "png", done());
  });
});

describe('#ontology_subclasses_of()', function(){
  it('should in all cases create an ontology_subclasses_of object given an argument class and a callback function', function(done){
    services.ontology_subclasses_of('Oven', done());
  });
});+

describe('#ontology_superclasses_of()', function(){
  it('should in all cases create an ontology_superclasses_of object given an argument class and a callback function', function(done){
    services.ontology_superclasses_of('Oven', done());
  });
});

describe('#ontology_is_subsuperclass_of()', function(){
  it('should in all cases create an ontology_is_subsuperclass_of object given a parent, a child, a boolean and a callback function as arguments', function(done){
    services.ontology_is_subsuperclass_of( 'Box-Container', 'MicrowaveOven', true, done());
  });  
});

describe('#set_noise_profile()', function(){
  it("should in all cases create a set_noise_profile object given an audio file, username and audio type as arguments", function(){
	services.set_noise_profile ( path.join(__dirname, 'denoise_source.wav'), "rapp", "nao_wav_1_ch" );
  });
});

describe('#speech_detection_sphinx4()', function(){
  it('should in all cases create a speech_detection_sphinx4 object given an audio file, the language, a user token, the audio source type, a grammar, a pool of words, a pool of sentences and a callback function as arguments', function(done){
    services.speech_detection_sphinx4( path.join(__dirname, 'recording_sentence2.ogg'), "en", "rapp", "nao_ogg", [], ["check", "my", "emails", "robot"], ["check", "my", "emails", "robot"], done());
  });  
});

describe('#speech_detection_google()', function(){
  it('should in all cases create a speech_detection_google object given an audio file, the audio source type, a user token, a language and a callback function as arguments', function(done){
    services.speech_detection_google( path.join(__dirname, 'recording_sentence2.ogg'), "nao_ogg", "rapp", "en", done());
  });  
});

describe('#available_services()', function(){
  it('should in all cases create available_services object given a callback function', function(done){
    services.available_services(done());
  });
});

describe('#cognitive_test_chooser()', function(){
  it('should in all cases create a cognitive_test_chooser object given a username, a test type and a callback function', function(done){
    services.cognitive_test_chooser( 'rapp', 'ReasoningCts', done());
  });
});

describe('#record_cognitive_test_performance()', function(){
  it('should in all cases create a record_cognitive_test_performance object given a username, a test instance, a score and a callback function', function(done){
    services.record_cognitive_test_performance('rapp', "ReasoningCts_pQmhNKHv", 1, done());
  });
});

describe('#text_to_speech()', function(){
  it('should in all cases create a text_to_speech object given the text to become speech, the language and a callback function', function(done){
    services.text_to_speech('Hello human', "en", done());
  });
});
