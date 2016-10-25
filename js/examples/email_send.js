#!/usr/bin/env node

// Import the email_send JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('rapp-platform-arapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.email_send = require('rapp-platform-arapp-platform-api/includes/cloud/email_send');

var services = new RAPPCloud( );

services.email_send( '', '', '', '465', ['lp@ortelio.co.uk'], 'blah', 'test', '' );
