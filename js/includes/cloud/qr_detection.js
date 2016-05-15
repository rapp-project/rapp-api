#!/usr/bin/env node

var path = require('path');
var __cloudDir = path.join(__dirname);
var __objectsDir = path.join(__dirname, '..', 'objects');
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));
var RAPPObject = require(path.join(__objectsDir, 'RAPPObject.js'));
RAPPObject.qrCode = require(path.join(__objectsDir, 'qrCode.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class qr_detection
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the cloud to detect QR Codes
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param image is the input image
 * @param image_format is the image format
 * @param callback is the function that will receive a vector of detected qr(s)
 */
RAPPCloud.prototype.qr_detection = function ( image, image_format, callback )
{
    var formData = require('form-data');
	var randomstring = require('randomstring');
	var fs = require('fs');
	var request = require('request').defaults({
	  secureProtocol: 'TLSv1_2_method',
	  rejectUnauthorized: false
	});

    var cloud = this;
    var object = new RAPPObject();
    var _delegate = callback;
	var form = new formData();
	//Generate a random file name under which the image will be saved on the Server 
	var filename = randomstring.generate() + '.' + image_format;

	form.append('file', fs.createReadStream(image), { 
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
	r.setHeader('Accept-Token', cloud.token);

	function handle_reply( json )
    {
		var json_obj;
		var codes = [];
		try {
			json_obj = JSON.parse(json);
			if(json_obj.error){  // Check for Errors  
				console.log('qr_detection JSON error: ' + json_obj.error);
			}
			// JSON reply is eg.: {"qr_centers":[{"x":86.0,"y":86.0}],"qr_messages":["http://www.qrstuff.com"],"error":""}
			for (var i=0; i<json_obj.qr_centers.length; i++){
				var x = json_obj.qr_centers[i].x;
				var y = json_obj.qr_centers[i].y;
				var label = json_obj.qr_messages[i];
				codes.push(new object.QrCode( x, y, label ));
			}
			_delegate(codes);
		} catch (e) {
			console.log('qr_detection::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}
};



/// Export
//module.exports = RAPPCloud.qr_detection;
module.exports = RAPPCloud.qr_detection;