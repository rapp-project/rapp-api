#!/usr/bin/env node

// Import the qr_detection JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('../lib/cloud/RAPPCloud');
RAPPCloud.qr_detection = require('../lib/cloud/qr_detection');
var services = new RAPPCloud();

/** 
 * This is the method that will handle the reply by the services.qr_detection
 */
function handler (codes)
{
    if (codes.length) {
		console.log ('Found ' + codes.length + ' qr codes!');
		for (var i=0; i<codes.length; i++) {
            console.log('qr code ' + (i+1) + ':');
			console.log('  centre: {x: ' + codes[i].get_centre_x() + ', y: ' + codes[i].get_centre_y() + '}');
            console.log('  label: ' + codes[i].get_label() + ' ');
		}
	}
	else
		console.log ('No qr codes detected');
}

services.qr_detection('../testdata/qrcode.png', 'png', handler);
