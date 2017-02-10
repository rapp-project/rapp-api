#!/usr/bin/env node

var path = require('path');
var formData = require('form-data');
var randomstring = require('randomstring');
var __cloudDir = path.join(__dirname);
var __objectsDir = path.join(__dirname, '..', 'objects');
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));
var RAPPObject = require(path.join(__objectsDir, 'RAPPObject.js'));
RAPPObject.picture = require(path.join(__objectsDir, 'picture.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class object_recognition_caffe
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the cloud to recognize an object
 * @version 0.7.5
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param image is the input image
 * @param callback is the function that will receive the detected object class
 */
RAPPCloud.prototype.object_recognition_caffe = function(
                                                         image,
                                                         callback
                                                       )
{
    var cloud = this;
    var object = new RAPPObject();
    var _delegate = callback;
    var request = cloud.determine_protocol();
	var form = new formData();
    var pic = new object.picture(image);
	//Generate a random file name under which the image will be saved on the Server 
	var filename = randomstring.generate() + '.' + pic.img_type;

	form.append('file', pic.image, { 
		filename: filename,
		contentType: 'image/' + pic.img_type
	});

	var r = request.post(
                          cloud.cloud_url + '/hop/object_recognition_caffe/ ',
                          function(error, res, json){ 
                              if (res.statusCode==200 && !error){
                                  handle_reply(json);
                                  }
                              else if (error) {
                                  error_handler(error);
                              }
                              else if (res.statusCode != 200) {
                                  console.log(res.statusCode);
                              }
                          }
                        );
	r._form = form;
	r.setHeader('Connection', 'close');
	r.setHeader('Accept-Token', cloud.token);

	function handle_reply(json)
    {
		var json_obj;
		try {
			json_obj = JSON.parse(json);
			if(json_obj.error) {  // Check for Errors  
				console.log('object_recognition_caffe JSON error: ' + json_obj.error);
			}
			// JSON reply is: {object_class: '', error: ''}
			_delegate(json_obj.object_class);
		} catch (e) {
			console.log('object_recognition_caffe::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler(error) {
		return console.error(error);
	}
};

/// Export
module.exports = RAPPCloud.object_recognition_caffe;
