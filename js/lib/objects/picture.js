#!/usr/bin/env node

var path = require('path');
var fs = require('fs');
var __objectsDir = path.join(__dirname);
var RAPPObject = require(path.join(__objectsDir, 'RAPPObject'));

/**
 * @fileOverview Prototype this RAPP Object Class.
 * 
 * @class Picture
 * @memberof RAPPObject
 * @description overloaded class which wraps around raw bytes of a picture
 * given either as such or as a file path
 * @version 0.7.5
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 */ 
RAPPObject.prototype.picture = function(image)
{
    /// Consruct using a file path
    if (typeof image === 'string') {
        var img_type = image.substr((~-image.lastIndexOf(".") >>> 0) + 2);
        if (img_type === 'jpg' || img_type === 'png') {
            this.img_type = img_type; 
            this.image = fs.createReadStream(image);
        }
        else
            throw 'unsupported file type for picture object construction';
    /// Construct using a raw data buffer
    } 
    else if (image instanceof Buffer) {
        /// currently only png and jpg image buffers supported
        if (image[0] === 137 && image[1] === 80)
            this.img_type = 'png';
        else if (image[0] === 255 && image[1] === 216)
            this.img_type = 'jpg'; 
        else 
            throw 'unsupported file type for picture object construction';
        this.image = image;
    } 
    else {
        throw 'unsupported data type for picture object construction';
    }
};

/// Export
module.exports = RAPPObject.picture;
