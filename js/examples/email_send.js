#!/usr/bin/env node

// Import the email_send JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../includes/cloud/RAPPCloud.js');
RAPPCloud.email_send = require('../includes/cloud/email_send.js');

var services = new RAPPCloud( );

services.email_send( '', '', 'smtp.gmail.com', '465', ['lp@ortelio.co.uk'], 'trela', 'test', '' );
