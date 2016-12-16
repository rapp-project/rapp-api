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
 * @class object_detection_learn_object
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the cloud to learn an
 * object given by the user
 * @version 0.7.5
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param image is the input image
 * @param name is the name of the object
 * @param callback is the function that will receive an int with the result
 */
RAPPCloud.prototype.object_detection_learn_object = function(
                                                              image,
                                                              name,
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
    var body_obj = {};
    body_obj.name = name;
    var body_json = JSON.stringify(body_obj);

	form.append('file', pic.image, { 
		filename: filename,
		contentType: 'image/' + pic.img_type
	});
	form.append('json', body_json);

	var r = request.post(
                          cloud.cloud_url + '/hop/object_detection_learn_object/ ', 
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
			if(json_obj.error)  // Check for Errors  
				console.log('object_detection_learn_object JSON error: ' + json_obj.error);
			// JSON reply is eg.: {result:0, error":""}
            else {
                
			    _delegate(json_obj.result);
            }
		} catch (e) {
			console.log('object_detection_learn_object::handle_reply Error parsing: ');
			return console.error(e);
	    }
	}
	
	function error_handler(error) {
		return console.error(error);
	}
};

/// Export
module.exports = RAPPCloud.object_detection_learn_object;
