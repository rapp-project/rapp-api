#!/usr/bin/env node

var path = require('path');
var __cloudDir = path.join(__dirname);
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));
const config = require("../../config/config");

if (config.protocol === "https")
{
    var request = require('request').defaults({
	    secureProtocol: 'TLSv1_2_method',
	    rejectUnauthorized: false
	});
}
else if (config.protocol === "http")
{
    var request = require("request");
}
else
{
    console.log("please choose one of: http or https(for TLS_1.2) as protocols");
}

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class path_planning_upload_map
 * @memberof RAPPCloud
 * @description Asynchronous Service which will try to upload a map to be used for path planning on the cloud
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param png_file: The map image png file.
 * @param yaml_file: The map description yaml file.
 * @param map_name: The map name.
 */ 

RAPPCloud.prototype.path_planning_upload_map = function ( png_file, yaml_file, map_name )
{
    var formData = require('form-data');
	var fs = require('fs');

    var cloud = this;
	var form = new formData();

	var body_obj = {};
    body_obj.map_name = map_name;
    var body_json = JSON.stringify(body_obj);
	
	if (!!png_file) {
		form.append('png_file', fs.createReadStream(png_file));
	}
	else return console.error('png file name missing');
    if (!!yaml_file) {
	    form.append('yaml_file', fs.createReadStream(yaml_file));
	}
	else return console.error('yaml file name missing');
	form.append('json', body_json);
	var r = request.post(cloud.cloud_url + '/hop/path_planning_upload_map/ ', function(error, res, json){ 
		if (res.statusCode==200 && !error) {
			handle_reply( json );
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
		try {
			json_obj = JSON.parse(json);
			if(json_obj.error){  // Check for Errors  
				console.log('path_planning_upload_map JSON error: ' + json_obj.error);
			}
		} catch (e) {
			console.log('path_planning_upload_map::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler( error ) {
		return console.error(error);
	}
};

/// Export
module.exports = RAPPCloud.path_planning_upload_map;
