#!/usr/bin/env node

var path = require('path');
var __cloudDir = path.join(__dirname);
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class email_send
 * @memberof RAPPCloud
 * @description Asynchronous Service which will send an email to a list of recipients
 * @version 0.7.5
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param email (String): The user's email username
 * @param passwd (String): The user's email password
 * @param server (String): The email server's smtp address, i.e. 'smtp.gmail.com'
 * @param port (String): The email server smtp port
 * @param recipients (Array): Email addresses of the recipients.
 * @param body (String): The email body
 * @param subject (String): The email subject
 * @param file(String): Path to a file attachment. Single file. In case of 
 * multiple attachments a zip file must be send to this field name.
 */
RAPPCloud.prototype.email_send = function(
                                            email,
                                            passwd,
                                            server,
                                            port,
                                            recipients,
                                            body,
                                            subject,
                                            file
                                         )
{
    var formData = require('form-data');
    var fs = require('fs');
    var cloud = this;
    var form = new formData();
    var request = cloud.determine_protocol();
    var body_obj = {};
    body_obj.email = cloud.escape_string(email);
    body_obj.passwd = cloud.escape_string(passwd);
    body_obj.server = cloud.escape_string(server);
    body_obj.port = cloud.escape_string(port);
    body_obj.recipients = [];
    for (var i=0; i<recipients.length; i++)
        body_obj.recipients[i] = cloud.escape_string(recipients[i]);
    body_obj.body = body;
    body_obj.subject = subject;
    var body_json = JSON.stringify(body_obj);
    
    if (!!file) {
       form.append('file', fs.createReadStream(file), { 
        filename: file
        }); 
    }
    
    form.append('json', body_json);
    var r = request.post(cloud.cloud_url + '/hop/email_send/ ', function(error, res, json){ 
        if (res.statusCode==200 && !error) {
            handle_reply(json);
        }
        else if (error) {
            error_handler(error);   
        }
        else if (res.statusCode != 200) {
            console.log(res.statusCode);
        }
    });
    r._form = form;
    r.setHeader('Connection', 'close');
    r.setHeader('Accept-Token', cloud.token);
    
    function handle_reply(json)
    {
		var json_obj;
		try {
			json_obj = JSON.parse(json);
			// JSON reply is: { error: '' }
		
			if(json_obj.error){  // Check for Errors  
				console.log('email_send JSON error: ' + json_obj.error);
			}
		} catch (e) {
			console.log('email_send::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler(error) {
		return console.error(error);
	}   
};

/// Export
module.exports = RAPPCloud.email_send;
