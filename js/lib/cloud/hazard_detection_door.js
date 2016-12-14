#!/usr/bin/env node

var path = require('path');
var formData = require('form-data');
var randomstring = require('randomstring');
var fs = require('fs');
var __cloudDir = path.join(__dirname);
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class hazard_detection_door
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the cloud to estimate door angle
 * @version 1
 * @author Maciej Stefańczyk <M.Stefanczyk@elka.pw.edu.pl>
 * @param image is the input image 
 * @param image_format is the image format
 * @param callback is the function that will receive an estimated door level [0..100]
 */
RAPPCloud.prototype.hazard_detection_door = function(
                                                        image,
                                                        image_format,
                                                        callback
                                                    )
{
	var cloud = this;
	var _delegate=callback;
    var request = cloud.determine_protocol();
	var form = new formData();
	//Generate a random file name under which the image will be saved on the Server 
	var filename = randomstring.generate() + '.' + image_format;
	
	form.append('file', fs.createReadStream(image), { 
		filename: filename,
		contentType: 'image/' + image_format 
	});

	var r = request.post(
                          cloud.cloud_url + '/hop/hazard_detection_door_check/ ', 
                          function(error, res, json) { 
                              if (res.statusCode==200 && !error) {
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
			if(json_obj.error){  // Check for Errors  
				console.log('hazard_detection_door JSON error: ' + json_obj.error);
			}
			// JSON reply is eg.: { "faces":[{"up_left_point":{"x":212.0,"y":200.0},
            // "down_right_point":{"x":391.0,"y":379.0}}],"error":""}
			var door_angle = json_obj.door_angle;
			_delegate(door_angle);
		} catch (e) {
			console.log('hazard_detection_door::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler(error) {
		return console.error(error);
	}
};

/// Export
module.exports = RAPPCloud.hazard_detection_door;
