#!/usr/bin/env node

const path = require('path');
//const fs = require('fs');
const cloud_dir = path.join(__dirname);
//const home_dir = require('home-dir');

/**
 * Define the RAPP Cloud Services object
 * @namespace RAPPCloud
 */
function RAPPCloud()
{
    this.platform = require(path.join(cloud_dir, '..', 'config', 'platform'));
//    var token_path = home_dir() + "/.this.platform/rapp_this.platform/tokens/app";
//    this.token = fs.readFileSync(token_path, 'utf8').toString().replace(/\n$/, '');
    this.token = "rapp_token";
    this.cloud_url = this.platform.protocol + "://" + this.platform.ip + 
        ":" + this.platform.port;
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
RAPPCloud.prototype.determine_protocol = function()
{
    if (this.platform.protocol === "https") {
        var request = require('request').defaults({
            secureProtocol: 'TLSv1_2_method',
            rejectUnauthorized: false
        });
        return request;
    }
    else if (this.platform.protocol === "http") {
        var request = require("request");
        return request;
    }
    else {
        throw "please choose one of: http or https(for TLS_1.2) as protocols";
    }
};

/// Export
module.exports = RAPPCloud;
