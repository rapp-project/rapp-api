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
 * @class hazard_detection_light
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the cloud to check light
 * @version 0.7.5
 * @author Maciej Stefańczyk <M.Stefanczyk@elka.pw.edu.p
 * Lazaros Penteridis <lp@ortelio.co.uk>
 * @param image is the input image
 * @param callback is the function that will receive an estimated light level [0..100]
 */
RAPPCloud.prototype.hazard_detection_light = function(
                                                        image,
                                                        callback
                                                     )
{
	var cloud = this;
    var object = new RAPPObject();
	var _delegate=callback;
	var form = new formData();
    var pic = new object.picture(image);
    var request = cloud.determine_protocol();
	//Generate a random file name under which the image will be saved on the Server 
	var filename = randomstring.generate() + '.' + pic.img_type;
	
	form.append('file', pic.image, { 
		filename: filename,
		contentType: 'image/' + pic.img_type
	});

	var r = request.post(
                            cloud.cloud_url + '/hop/hazard_detection_light_check/ ',
                            function(error, res, json) { 
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
			if(json_obj.error){  // Check for Errors  
				console.log('hazard_detection_light JSON error: ' + json_obj.error);
			}
			var light_level = json_obj.light_level;
			_delegate(light_level);
		} catch (e) {
			console.log('hazard_detection_light::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler(error) {
		return console.error(error);
	}
};

/// Export
module.exports = RAPPCloud.hazard_detection_light;
