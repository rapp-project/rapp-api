#!/usr/bin/env node

var RAPPCloud = require('./../../../RAPPCloud.js');
var RAPPObject = require('./../../../RAPPObject.js');
RAPPObject.face = require('./../../objects/face/face.js');
var FormData = require('form-data');
var fs = require('fs');
var request = require('request');
var randomstring = require('randomstring');

/**
 * Prototype the RAPPCloud Service Method.
 * 
 * @method faceDetector
 * @brief Asynchronous Service which will request the cloud to detect faces
 * @version 1
 * @date 20-September-2015
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 */ 

/**
 * @brief Constructor
 * @param image is the input image 
 * @param image_format is the image format
 * @param callback is the function that will receive a vector of the detected face(s) coordinates
 */
RAPPCloud.prototype.faceDetector = function ( image, image_format, callback )
{
    var cloud = this;
    var object = new RAPPObject( );
    var _delegate=callback;
	var form = new FormData();
	var filename = randomstring.generate() + '.' + image_format;
	
	form.append('file_uri', fs.createReadStream(image), { 
		filename: filename,
		contentType: 'image/' + image_format 
	});

	var r = request.post(cloud.cloud_url + '/hop/face_detection/ ', function(error, res, json){ 
		if (res.statusCode==200 && !error){
			handle_reply( json );
			}
		else if (error) {
			error_handler(error);
		}
		else if ( response.statusCode != 200 ) {
			console.log(res.statusCode);
		}
	});
	r._form = form;
	r.setHeader('Connection', 'close');

	function handle_reply( json )
    {
		var json_obj;
		var faces = [];
		try {
			json_obj = JSON.parse(json);
			if(json_obj.error){  // Check for Errors returned by the api.rapp.cloud
				console.log('faceDetection JSON error: ' + json_obj.error);
			}
			// JSON reply is eg.: { "faces":[{"up_left_point":{"x":212.0,"y":200.0},"down_right_point":{"x":391.0,"y":379.0}}],"error":""}
			for (i=0; i<json_obj.faces.length; i++){
				var up_left = json_obj.faces[i].up_left_point;
				var down_right = json_obj.faces[i].down_right_point;
				faces.push(new object.Face( up_left.x, up_left.y, down_right.x, down_right.y ));
			}
			_delegate(faces);
		} catch (e) {
			console.log("faceDetector::handle_reply Error parsing: ");
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}
}



/// Export
module.exports = RAPPCloud.faceDetector;
