#!/usr/bin/env node

// Import the email_fetch JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../lib/cloud/RAPPCloud');
RAPPCloud.email_fetch = require('../lib/cloud/email_fetch');

var services = new RAPPCloud();
/** 
 * This is the method that will handle the reply by the service.email_fetch
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function callback(emails)
{
    console.log(emails);
}

//var now = new Date();
//var startOfDay = new Date(now.getFullYear(), now.getMonth(), now.getDate());
//var today_start = startOfDay / 1000;

services.email_fetch('', '', '', '993', "ALL", 0, 0, 1, callback);
