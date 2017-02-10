#!/usr/bin/env node

var path = require('path');
var __objectsDir = path.join(__dirname);
var RAPPObject = require(path.join(__objectsDir, 'RAPPObject'));

/**
 * @fileOverview Prototype this RAPP Object Class.
 * 
 * @class Qr_code
 * @memberof RAPPObject
 * @description class which should encapsulate a QR code
 * @version 0.7.5
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 */
/***
* Define Qr_code "class" inside an immediate function.
* A bit unconventional way but it's the only way I have found to have the same 
* information flow with C++* in the way that instances of this Qr_code and only 
* those can have access to private variables of other instances of the same 
* "class" so that member functions like is_equal can work.
*/
RAPPObject.prototype.Qr_code = (function() // immediate function
{   
	var _centre_x; 
	var _centre_y;
	var _message ;
	var instance = 0; // counts the number of instances
	var qr_codes = []; // an array of private objects
	
	/**
     * @description Consruct using code coordinates (a rectangle) and a label 
     * (URL, email, string, etc)
     * @param centre_x is coordinate
     * @param centre_y is coordinate
     * @param label is message embedded in QR
     */	
	function Qr_code(centre_x, centre_y, label)
	{
		// Increment the instance count and save it to the instance. 
        // This will become the key to the private space.
		this.i = instance++;
		
		// Create a new object in the private space.
		qr_codes[this.i] = {};
		
		qr_codes[this.i]._centre_x = centre_x;
		qr_codes[this.i]._centre_y = centre_y;
		qr_codes[this.i]._message = label;
	}

    /** 
     * @function is_equal
     * @description Equality operator
     * @param qr_code2 is the Qr_code object to which this object is compared for equality
     * only the message is compared (insensitive case), not the coordinates!
     */
	Qr_code.prototype.is_equal = function(qr_code2) 
	{
		// It has access to the private space and it's children!
		return (qr_codes[this.i]._message === qr_codes[qr_code2.i]._message);
	};
	
	/**
	 * @function get_label
     * @description Return the qr message
     * @return qr_label
	 */
	Qr_code.prototype.get_label = function()
	{
		return qr_codes[this.i]._message;
	};

	/**
	 * @function get_centre_x 
     * @description Return the qr centre x coordinate
     * @return qr_centre_x 
	 */
    Qr_code.prototype.get_centre_x  = function() 
	{
		return qr_codes[this.i]._centre_x ;
	};

	/**
	 * @function get_centre_y 
     * @description Return the qr centre x coordinate
     * @return qr_centre_y
	 */
    Qr_code.prototype.get_centre_y = function() 
	{
		return qr_codes[this.i]._centre_y;
	};

	return Qr_code;	
})();

/// Export
module.exports = RAPPObject.Qr_code;
