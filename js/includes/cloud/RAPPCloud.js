#!/usr/bin/env node

const platform = require("../cloud/platform");
const fs = require("fs");
const homeDir = require('home-dir');

/**
 * Define the RAPP Cloud Services object
 * @namespace RAPPCloud
 */
function RAPPCloud ()
{
//    var token_path = homeDir() + "/.platform/rapp_platform/tokens/app";
//    this.token = fs.readFileSync(token_path, 'utf8').toString().replace(/\n$/, '');
    this.token = "rapp_token";
    this.cloud_url = platform.protocol + "://" + platform.rapp_platform_ip + ":" + platform.rapp_platform_port;
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

/// Determine protocol
RAPPCloud.prototype.determine_protocol = function(
/// Export
module.exports = RAPPCloud;
