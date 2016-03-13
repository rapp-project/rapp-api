#!/usr/bin/env node

/**
 * Define the RAPP Cloud Services object, which needs a username and password
 * @namespace RAPPCloud
 */
function RAPPCloud ( )
{
    //this.cloud_url = 'http://155.207.19.13:9001';
    this.cloud_url = 'http://localhost:9001'; 
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
