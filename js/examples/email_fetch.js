#!/usr/bin/env node

// Import the email_fetch JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../includes/cloud/RAPPCloud.js');
RAPPCloud.email_fetch = require('../includes/cloud/email_fetch.js');

var services = new RAPPCloud( );
/** 
 * This is the method that will handle the reply by the service.email_fetch
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function callback ( emails )
{
    console.log ( emails );
}

var now = new Date();
var startOfDay = new Date(now.getFullYear(), now.getMonth(), now.getDate());
var today_start = startOfDay / 1000;

services.email_fetch( '', '', 'imap.mail.yahoo.com', '993', "ALL", 1462496400, 1462535475, 1, callback );
