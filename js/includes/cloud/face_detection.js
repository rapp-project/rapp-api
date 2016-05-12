#!/usr/bin/env node

var path = require('path');
var __cloudDir = path.join(__dirname);
var __objectsDir = path.join(__dirname, '..', 'objects');
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));
var RAPPObject = require(path.join(__objectsDir, 'RAPPObject.js'));
RAPPObject.face = require(path.join(__objectsDir, 'face.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class face_detection
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the cloud to detect faces
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param image is the input image 
 * @param image_format is the image format
 * @param callback is the function that will receive a vector of the detected face(s) coordinates
 * @param fast is a string. Only valid values 'true' and 'false'. When 'true' the fast face detection service is called, which should be used for tracking applications
 */
RAPPCloud.prototype.face_detection = function ( image, image_format, callback, fast )
{
    fast = typeof fast !== 'undefined' ? fast : false;

    var formData = require('form-data');
	var randomstring = require('randomstring');
	var fs = require('fs');
	var request = require('request').defaults({
	  secureProtocol: 'TLSv1_2_method',
	  rejectUnauthorized: false
	});

    var cloud = this;
    var object = new RAPPObject( );
    var _delegate = callback;
	var form = new formData();
	//Generate a random file name under which the image will be saved on the Server 
	var filename = randomstring.generate() + '.' + image_format;

	var body_obj = new Object();
    body_obj.fast = fast;
    var body_json = JSON.stringify(body_obj);
	
	form.append('file', fs.createReadStream(image), { 
		filename: filename,
		contentType: 'image/' + image_format 
	});
	form.append('json', body_json);
	var r = request.post(cloud.cloud_url + '/hop/face_detection/ ', function(error, res, json){ 
		if (res.statusCode==200 && !error){
			handle_reply( json );
		}
		else if (error) {
			error_handler(error);	
		}
		else if ( res.statusCode != 200 ) {
			console.log(res.statusCode);
		}
	});
	r._form = form;
	r.setHeader('Connection', 'close');
	r.setHeader('Accept-Token', cloud.token);

	function handle_reply( json )
    {
		var json_obj;
		var faces = [];
		try {
			json_obj = JSON.parse(json);
			if(json_obj.error){  // Check for Errors  
				console.log('face_detection JSON error: ' + json_obj.error);
			}
			// JSON reply is eg.: { "faces":[{"up_left_point":{"x":212.0,"y":200.0},"down_right_point":{"x":391.0,"y":379.0}}],"error":""}
			for (var i=0; i<json_obj.faces.length; i++){
				var up_left = json_obj.faces[i].up_left_point;
				var down_right = json_obj.faces[i].down_right_point;
				faces.push(new object.Face( up_left.x, up_left.y, down_right.x, down_right.y ));
			}
			_delegate(faces);
		} catch (e) {
			console.log('face_detection::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}
};



/// Export
module.exports = RAPPCloud.face_detection;
