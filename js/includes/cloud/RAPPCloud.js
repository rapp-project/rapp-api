#!/usr/bin/env node

/**
 * Define the RAPP Cloud Services object
 * @namespace RAPPCloud
 */
function RAPPCloud ( )
{
    var fs = require('fs');
	this.token = fs.readFileSync('/home/leizer/.config/rapp_platform/application_token', 'utf8').toString().replace(/\n$/, '');
    this.cloud_url = 'https://localhost:9001';
}

/// escape JSON strings when sending them over the socket
RAPPCloud.prototype.escape_string = function(string)
{
	return string.replace(/\\/g, '\\\\').
	replace(/\u0008/g, '\\b').
	replace(/\t/g, '\\t').
	replace(/\n/g, '\\n').
	replace(/\f/g, '\\f').
	replace(/\r/g, '\\r').
	replace(/'/g, '\\\'').
    replace(/"/g, '\\"');
};

/// Export
module.exports = RAPPCloud;
