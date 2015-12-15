#!/usr/bin/env node

var fs = require('fs');
var request = require('request');
var path = require('path');
var formData = require('form-data');
var randomstring = require('randomstring');

var __cloudDir = path.join(__dirname);
var __objectsDir = path.join(__dirname, '..', 'objects');

var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));
var RAPPObject = require(path.join(__objectsDir, 'RAPPObject.js'));
RAPPObject.qrCode = require(path.join(__objectsDir, 'qrCode.js'));


/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class qrDetector
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the cloud to detect QR Codes
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param image is the input image
 * @param image_format is the image format
 * @param callback is the function that will receive a vector of detected qr(s)
 */
RAPPCloud.prototype.qrDetector = function ( image, image_format, callback )
{
    var cloud = this;
    var object = new RAPPObject( );
    var _delegate=callback;
	var form = new formData();

	var filename = randomstring.generate() + '.' + image_format;

	form.append('file_uri', fs.createReadStream(image), { 
		filename: filename,
		contentType: 'image/' + image_format
	});
	
	var r = request.post(cloud.cloud_url + '/hop/qr_detection/ ', function(error, res, json){ 
		if (res.statusCode==200 && !error){
			handle_reply(json);
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

	function handle_reply( json )
    {
		var json_obj;
		var codes = [];
		try {
			var i;
			json_obj = JSON.parse(json);
			if(json_obj.error){  // Check for Errors returned by the api.rapp.cloud
				console.log('qrDetection JSON error: ' + json_obj.error);
			}
			// JSON reply is eg.: {"qr_centers":[{"x":86.0,"y":86.0}],"qr_messages":["http://www.qrstuff.com"],"error":""}
			for (i=0; i<json_obj.qr_centers.length; i++){
				var x = json_obj.qr_centers[i].x;
				var y = json_obj.qr_centers[i].y;
				var label = json_obj.qr_messages[i];
				codes.push(new object.QrCode( x, y, label ));
			}
			_delegate(codes);
		} catch (e) {
			console.log("qrDetector::handle_reply Error parsing: ");
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}
};



/// Export
module.exports = RAPPCloud.qrDetector;
