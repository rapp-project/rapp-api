#!/usr/bin/env node

var RAPPCloud = require('./../../../RAPPCloud.js');
var RAPPObject = require('./../../objects/face/face.js')

/**
 * Prototype the RAPPCloud Service Method.
 * 
 * @method faceDetector
 * @brief Asynchronous Service which will request the cloud to detect faces
 * @version 1
 * @date 14-September-2015
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 */ 

/**
 * @brief Constructor
 * @param image is the input image @see rapp::object::picture
 * @param image_format is the image format
 * @param callback is the function that will receive a vector of the detected face(s) coordinates
 */
RAPPCloud.prototype.faceDetector = function ( image, callback )
{
    var cloud = this;
    var FormData = require('form-data');
	var fs = require('fs');
	var http = require('http');
	
	var form = new FormData();
	var img_stream = fs.createReadStream(image);
	
	form.append('file_uri', img_stream);
	
	var form_headers = form.getHeaders();
	
	//Object.size = function(obj) {
	    //var size = 0, key;
	    //for (key in obj) {
	        //if (obj.hasOwnProperty(key)) size++;
	    //}
	    //return size;
	//};
	// Get the size of an object
	//var size = Object.size(form);
	
	var request = http.request({
		method: 'post',
		host: 'localhost',
		port: '9001',
		path: '/hop/face_detection/ ',
		headers: form_headers
		//knownLength: size
	});

	form.pipe(request);
	
	request.on('response', function(response) {
		if ( response.statusCode == 200) {
		    response.setEncoding('utf8');
		    response.on('data', function (body) {
		    console.log('body: ' + body);
			});
		}
		else {
			console.log(response.statusCode);
		}
	});
		
	request.on('error', function(error) {
		console.log('problem with request: ' + error.message);
	});
}



/// Export
module.exports = RAPPCloud;
