#!/usr/bin/env node

var path = require('path');
var formData = require('form-data');
var randomstring = require('randomstring');
var fs = require('fs');
var __cloudDir = path.join(__dirname);
var __objectsDir = path.join(__dirname, '..', 'objects');
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class object_detection_learn_object
 * @memberof RAPPCloud
 * @description Asynchronous Service which will request the cloud to learn an
 * object given by the user
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param image is the input image path
 * @param image_format is the image format
 * @param name is the name of the object
 * @param callback is the function that will receive an int with the result
 */
RAPPCloud.prototype.object_detection_learn_object = function(
                                                              image,
                                                              image_format,
                                                              name,
                                                              callback
                                                            )
{
    var cloud = this;
    var _delegate = callback;
    var request = cloud.determine_protocol();
	var form = new formData();
	//Generate a random file name under which the image will be saved on the Server 
	var filename = randomstring.generate() + '.' + image_format;

    var body_obj = {};
    body_obj.name = name;
    var body_json = JSON.stringify(body_obj);

	form.append('file', fs.createReadStream(image), { 
		filename: filename,
		contentType: 'image/' + image_format 
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
