#!/usr/bin/env node

var path = require('path');
var formData = require('form-data');
var __cloudDir = path.join(__dirname);
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 *
 * @class object_detection_load_models
 * @description Asynchronous Service which will request the cloud to 
 * load one or more models to operational memory
 * @version 0.7.5
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param names a vector with the object names to load 
 * @param callback will be executed once the rapp cloud has responded
 */
RAPPCloud.prototype.object_detection_load_models = function(
                                                             names,
                                                             callback
                                                           )
{
    var cloud = this;
    var _delegate = callback;
	var form = new formData();
    var request = cloud.determine_protocol();
	//Escaping all the names of the vector
    var escaped_names = [];
	for (var i=0; i<names.length; i++){
        escaped_names.push(cloud.escape_string(names[i]));
	}
	
	var body_obj = {};
    body_obj.names = escaped_names;
    var body_json = JSON.stringify(body_obj);

	form.append('json', body_json);
	
	var r = request.post(
                          cloud.cloud_url + '/hop/object_detection_load_models/ ',
                          function(error, res, json){ 
                              if (res.statusCode==200 && !error){
                                  handle_reply(json);
                                  }
                              else if (error) {
                                  error_handler(error);
                              }
                              else if ( res.statusCode != 200 ) {
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
				console.log('object_detection_load_models JSON error: ' + json_obj.error);
			// JSON reply is eg.: {"result":0,"error":""}
            else
			    _delegate(json_obj.result);
		} catch (e) {
			console.log('object_detection_load_models::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}
};

/// Export
module.exports = RAPPCloud.object_detection_load_models;
