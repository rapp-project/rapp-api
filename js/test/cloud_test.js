#!/usr/bin/env node

var test = require('unit.js');
var path = require('path');

// Import the JS API Services & Init the RAPPCloud Object
var __cloudDir = path.join(__dirname, '..', 'includes', 'cloud');
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));
RAPPCloud.ontology_subclasses_of = require(path.join(__cloudDir, 'ontology_subclasses_of.js'));
RAPPCloud.ontology_superclasses_of = require(path.join(__cloudDir, 'ontology_superclasses_of.js'));
RAPPCloud.ontology_is_subsuperclass_of = require(path.join(__cloudDir, 'ontology_is_subsuperclass_of.js'));
RAPPCloud.face_detection = require(path.join(__cloudDir, 'face_detection.js'));
RAPPCloud.qr_detection = require(path.join(__cloudDir, 'qr_detection.js'));
RAPPCloud.human_detection = require(path.join(__cloudDir, 'human_detection.js'));
RAPPCloud.hazard_detection_door = require(path.join(__cloudDir, 'hazard_detection_door.js'));
RAPPCloud.hazard_detection_light = require(path.join(__cloudDir, 'hazard_detection_light.js'));
RAPPCloud.object_recognition_caffe = require(path.join(__cloudDir, 'object_recognition_caffe.js'));
RAPPCloud.set_noise_profile = require(path.join(__cloudDir, 'set_noise_profile.js'));
RAPPCloud.speech_recognition_sphinx4 = require(path.join(__cloudDir, 'speech_recognition_sphinx4.js'));
RAPPCloud.speech_recognition_google = require(path.join(__cloudDir, 'speech_recognition_google.js'));
RAPPCloud.text_to_speech = require(path.join(__cloudDir, 'text_to_speech.js'));
RAPPCloud.available_services = require(path.join(__cloudDir, 'available_services.js'));
RAPPCloud.cognitive_test_chooser = require(path.join(__cloudDir, 'cognitive_test_chooser.js'));
RAPPCloud.cognitive_record_performance = require(path.join(__cloudDir, 'cognitive_record_performance.js'));
RAPPCloud.cognitive_get_history = require(path.join(__cloudDir, 'cognitive_get_history.js'));
RAPPCloud.cognitive_get_scores = require(path.join(__cloudDir, 'cognitive_get_scores.js'));
RAPPCloud.email_fetch = require(path.join(__cloudDir, 'email_fetch.js'));
RAPPCloud.email_send = require(path.join(__cloudDir, 'email_send.js'));
RAPPCloud.geolocation = require(path.join(__cloudDir, 'geolocation.js'));
RAPPCloud.news_explore = require(path.join(__cloudDir, 'news_explore.js'));
RAPPCloud.path_planning_plan_path_2d = require(path.join(__cloudDir, 'path_planning_plan_path_2d.js'));
RAPPCloud.path_planning_upload_map = require(path.join(__cloudDir, 'path_planning_upload_map.js'));
RAPPCloud.weather_report_current = require(path.join(__cloudDir, 'weather_report_current.js'));
RAPPCloud.weather_report_forecast = require(path.join(__cloudDir, 'weather_report_forecast.js'));

var services = new RAPPCloud( );


describe('#ontology_subclasses_of()', function(){
  it('should in all cases create an ontology_subclasses_of object given an argument class and a callback function', function(done){
    services.ontology_subclasses_of('Oven', done());
  });
});

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

describe('#face_detection()', function(){
  it('should in all cases create a face_detection object given an image, the image type and a callback function', function(done){
    services.face_detection( path.join(__dirname, '../../testdata/two_faces.jpg'), "jpg", done());
  });
});

describe('#qr_detection()', function(){
  it('should in all cases create a qr_detection object given an image, the image type and a callback function', function(done){
    services.qr_detection( path.join(__dirname, '../../testdata/qrcode.png'), "png", done());
  });
});

describe('#human_detection()', function(){
  it('should in all cases create a human_detection object given an image, the image type and a callback function', function(done){
    services.human_detection( path.join(__dirname, '../../testdata/face_samples/fatsaSou_near.jpg'), "jpg", done());
  });
});

describe('#hazard_detection_door()', function(){
  it('should in all cases create a hazard_detection_door object given an image, the image type and a callback function', function(done){
    services.face_detection( path.join(__dirname, '../../testdata/door_1.png'), "jpg", done());
  });
});

describe('#hazard_detection_light()', function(){
  it('should in all cases create a hazard_detection_light object given an image, the image type and a callback function', function(done){
    services.hazard_detection_light( path.join(__dirname, '../../testdata/lamp_on.jpg'), "jpg", done());
  });
});

describe('#object_recognition_caffe()', function(){
  it('should in all cases create an object_recognition_caffe object given an image, the image type and a callback function', function(done){
    services.object_recognition_caffe( path.join(__dirname, '../../testdata/cat.jpg'), "jpg", done());
  });
});

describe('#set_noise_profile()', function(){
  it("should in all cases create a set_noise_profile object given an audio file, username and audio type as arguments", function(){
	services.set_noise_profile ( path.join(__dirname, '../../testdata/denoise_source.wav'), "rapp", "nao_wav_1_ch" );
  });
});

describe('#speech_recognition_sphinx4()', function(){
  it('should in all cases create a speech_recognition_sphinx4 object given an audio file, the language, a user token, the audio source type, a grammar, a pool of words, a pool of sentences and a callback function as arguments', function(done){
    services.speech_recognition_sphinx4( path.join(__dirname, '../../testdata/recording_sentence2.ogg'), "en", "rapp", "nao_ogg", [], ["check", "my", "emails", "robot"], ["check", "my", "emails", "robot"], done());
  });  
});

describe('#speech_recognition_google()', function(){
  it('should in all cases create a speech_recognition_google object given an audio file, the audio source type, a user token, a language and a callback function as arguments', function(done){
    services.speech_recognition_google( path.join(__dirname, '../../testdata/recording_sentence2.ogg'), "nao_ogg", "rapp", "en", done());
  });  
});

describe('#text_to_speech()', function(){
  it('should in all cases create a text_to_speech object given the text to become speech, the language and a callback function', function(done){
    services.text_to_speech('Hello human', "en", done());
  });
});

describe('#available_services()', function(){
  it('should in all cases create available_services object given a callback function', function(done){
    services.available_services(done());
  });
});

describe('#cognitive_test_chooser()', function(){
  it('should in all cases create a cognitive_test_chooser object given a username, a test type and a callback function', function(done){
    services.cognitive_test_chooser( 'ReasoningCts', done());
  });
});

describe('#cognitive_record_performance()', function(){
  it('should in all cases create a cognitive_record_performance object given a username, a test instance, a score and a callback function', function(done){
    services.cognitive_record_performance( 'ReasoningCts_pQmhNKHv', 1, done());
  });
});

describe('#cognitive_get_history()', function(){
  it('should in all cases create a cognitive_get_history object given a callback function and optionally a string describing the test type and two timestamps', function(done){
    services.cognitive_get_history( done() );
  });
});

describe('#cognitive_get_scores()', function(){
  it('should in all cases create a cognitive_get_scores object given a callback function and optionally a timestamp and a string describing the test type', function(done){
    services.cognitive_get_scores( done() );
  });
});

describe('#email_fetch()', function(){
  it('should in all cases create a email_fetch object given 5 strings as arguments, 3 integers and a callback function', function(done){
    services.email_fetch( '', '', '', '', '', 0, 0, 1, done() );
  });
});

describe('#email_send()', function(){
  it('should in all cases create a email_fetch object given 4 strings as arguments, an array and 3 more strings', function(){
    services.email_send( '', '', '', '', [], '', '', '' );
  });
});

describe('#geolocation()', function(){
  it('should in all cases create a geolocation object given an IP address, an engine(string) and a callback function', function(done){
    services.geolocation( '', '', done() );
  });
});

describe('#news_explore()', function(){
  it('should in all cases create a news_explore object given a news_engine (String), an array of keywords, an array of titles to be excluded, a region (string), a topic (string) and a callback function', function(done){
    services.news_explore( '', [], [], '', '', 1, done() );
  });
});

describe('#path_planning_plan_path_2d()', function(){
  it('should in all cases create a path_planning_plan_path_2d object given 3 strings, 2 robot pose objects and a callback function', function(done){
    services.geolocation( '', '', '', {}, {}, done() );
  });
});

describe('#path_planning_upload_map()', function(){
  it('should in all cases create a path_planning_upload_map object given a png file, a yaml file and a map name (string) and a callback function', function(){
    services.path_planning_upload_map( '', '', '' );
  });
});

describe('#weather_report_current()', function(){
  it('should in all cases create a weather_report_current object given the city and the weather reporter strings, a metric (integer) and a callback function', function(done){
    services.weather_report_current( '', '', 0, done() );
  });
});

describe('#weather_report_forecast()', function(){
  it('should in all cases create a weather_report_forecast object given the city and the weather reporter strings, a metric (integer) and a callback function', function(done){
    services.weather_report_forecast( '', '', 0, done() );
  });
});