#!/usr/bin/env node

// Import the email_send JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../lib/cloud/RAPPCloud');
RAPPCloud.email_send = require('../lib/cloud/email_send');

var services = new RAPPCloud();

services.email_send('', '', '', '465', ['lp@ortelio.co.uk'], 'blah', 'test', '');
