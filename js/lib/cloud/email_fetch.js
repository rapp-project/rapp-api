#!/usr/bin/env node

var path = require('path');
var __cloudDir = path.join(__dirname);
var RAPPCloud = require(path.join(__cloudDir, 'RAPPCloud.js'));

/**
 * @fileOverview Prototype the RAPPCloud Service Method.
 * 
 * @class email_fetch
 * @memberof RAPPCloud
 * @description Asynchronous Service which will fetch the user's emails
 * @version 0.7.5
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 * @param email (String): The user's email username
 * @param passwd (String): The user's email password
 * @param server (String): The email server's imap address, i.e. 'imap.gmail.com'
 * @param port (String): The email server imap port
 * @param email_status (String): Define which mails the users requests. 
 * Values: ALL, UNSEEN(DEFAULT)
 * @param from_date (Integer): Emails since date. Unix timestamp.
 * @param to_date (Integer): Emails until date. Unix timestamp.
 * @param num_emails (Integer): Number of requested emails
 * @param callback is the function that will receive the result
 */
RAPPCloud.prototype.email_fetch = function(
                                            email,
                                            passwd,
                                            server,
                                            port,
                                            email_status,
                                            from_date,
                                            to_date,
                                            num_emails,
                                            callback
                                          )
{
    var cloud = this;
    var _delegate = callback;
    var request = cloud.determine_protocol();   
    var body_obj = {};
    body_obj.email = cloud.escape_string(email);
    body_obj.passwd = cloud.escape_string(passwd);
    body_obj.server = cloud.escape_string(server);
    body_obj.port = cloud.escape_string(port);
    body_obj.email_status = cloud.escape_string(email_status);
    body_obj.from_date = from_date;
    body_obj.to_date = to_date;
    body_obj.num_emails = num_emails;
    var body_json = JSON.stringify(body_obj);

    request.post({
        headers: {
			'Accept-Token' : cloud.token,
			'Connection' : 'close'
			},
        url: cloud.cloud_url + '/hop/email_fetch/ ',
        body: "json=" + body_json
    },
    function(error, response, json) 
    {
        if (!error && response.statusCode == 200)
            handle_reply(json);
        else if (error)
            error_handler(error);
        else if (response.statusCode != 200)
            console.log('Error: ' + response.statusCode);
    });
    
    function handle_reply(json)
    {
		var json_obj;
		try {
			json_obj = JSON.parse(json);
			// JSON reply is: { emails: [{<emailEntry_1>}, ..., {<emailEntry_n>}], error: '' }
			// where emailEntry is an object of structure: {sender: '', receivers: [], body: '', date: '', body: '', attachments: []}
			if(json_obj.error){  // Check for Errors  
				console.log('email_fetch JSON error: ' + json_obj.error);
			}
			_delegate( json_obj.emails);
		} catch (e) {
			console.log('email_fetch::handle_reply Error parsing: ');
			return console.error(e);
		}
	}
	
	function error_handler(error) {
		return console.error(error);
	}   
};

/// Export
module.exports = RAPPCloud.email_fetch;
