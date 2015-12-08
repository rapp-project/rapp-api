#!/usr/bin/env node

var RAPPObject = require('./../../../RAPPObject.js');

/**
 * @class QrCode
 * @description class which should encapsulate a QR code
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 */

/***
* Define QrCode "class" inside an immediate function.
* A bit unconventional way but it's the only way I have found to have the same information flow with C++
* in the way that instances of this QrCode and only those can have access to private variables of 
* other instances of the same "class" so that member functions like isEqual can work.
*/

RAPPObject.prototype.QrCode = (function( centre_x, centre_y, label ){   // immediate function
	
	var _centre_x = -1; 
    var _centre_y = -1;
    var _message ;
	
	var instance = 0; // counts the number of instances
	var qrCodes = []; // an array of private objects
	
	/**
     * @description Consruct using code coordinates (a rectangle) and a label (URL, email, string, etc)
     * @param centre_x is coordinate
     * @param centre_y is coordinate
     * @param label is message embedded in QR
     */	
	function QrCode ( centre_x, centre_y, label )
	{
		// Increment the instance count and save it to the instance. 
        // This will become the key to the private space.
		this.i = instance++;
		
		// Create a new object in the private space.
		qrCodes[this.i] = {};
		
		qrCodes[this.i]._centre_x = centre_x;
		qrCodes[this.i]._centre_y = centre_y;
		qrCodes[this.i]._message = label;
	}

	//TODO: A function that can be used as a Copy Constructor
	
    /** 
     * @function isEqual
     * @description Equality operator
     * @param rhs is the QrCode object to which this object is compared for equality
     * only the message is compared (insensitive case), not the coordinates!
     */
	QrCode.prototype.isEqual = function (rhs) 
	{
		// It has access to the private space and it's children!
		return ( qrCodes[this.i]._message === qrCodes[rhs.i]._message );
	};
	
	/**
	 * @function label
     * @description Return the qr message
     * @return qr_label
	 */
	
	QrCode.prototype.label = function () 
	{
		return qrCodes[this.i]._message;
	};
	
	return QrCode;	
})();


/// Export
module.exports = RAPPObject.QrCode;
