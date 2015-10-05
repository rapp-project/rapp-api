#!/usr/bin/env node

var RAPPCloud = require('./../../../RAPPCloud.js');
var RAPPObject = require('./../../../RAPPObject.js');
RAPPObject.qrCode = require('./../../objects/qrCode/qrCode.js');

/**
 * Prototype the RAPPCloud Service Method.
 * 
 * @method qrDetector
 * @brief Asynchronous Service which will request the cloud to detect QR Codes
 * @version 1
 * @date 25-September-2015
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 */ 

/**
 * @brief Constructor
 * @param image is the input image @see rapp::object::picture
 * @param callback is the function that will receive a vector of detected qr(s)
 */
RAPPCloud.prototype.qrDetector = function ( image, callback )
{
    var cloud = this;
    var object = new RAPPObject( );
    var _delegate=callback;
    var FormData = require('form-data');
	var fs = require('fs');
	var form = new FormData();
	var request = require('request');
	
	form.append('file_uri', fs.createReadStream(image));
	
	var r = request.post(cloud.cloud_url + '/hop/qr_detection/ ', function(error, res, json){ 
		if (res.statusCode==200 && !error){
//			console.log(json);
			handle_reply(json);
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
		var codes = [];
		try {
			json_obj = JSON.parse(json);
			if(json_obj.error){  // Check for Errors returned by the api.rapp.cloud
				console.log('qrDetection JSON error: ' + json_obj.error);
			}
			// JSON reply is eg.: {"qr_centers":[{"x":86.0,"y":86.0}],"qr_messages":["http://www.qrstuff.com"],"error":""}
			if (json_obj.qr_centers.length){
				for (i=0; i<json_obj.qr_centers.length; i++){
					var x = json_obj.qr_centers[i].x;
					var y = json_obj.qr_centers[i].y;
					var label = json_obj.qr_messages[i];
					codes.push(new object.QrCode( x, y, label ));
				}
				_delegate(codes);
			}
		} catch (e) {
			console.log("qrDetector::handle_reply Error parsing: ");
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}
}



/// Export
module.exports = RAPPCloud.qrDetector;
