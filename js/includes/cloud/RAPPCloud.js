#!/usr/bin/env node

const config = require("../../config/config");
const fs = require("fs");
const homeDir = require('home-dir');

/**
 * Define the RAPP Cloud Services object
 * @namespace RAPPCloud
 */
function RAPPCloud ()
{
    var token_path = homeDir() + "/.config/rapp_platform/tokens/app";
    this.token = fs.readFileSync(token_path, 'utf8').toString().replace(/\n$/, '');
//    this.token = "rapp_token";
    this.cloud_url = config.protocol + "://" + config.rapp_platform_ip + ":" + config.rapp_platform_port;
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
