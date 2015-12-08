#!/usr/bin/env node

var path = require('path');
var __objectsDir = path.join(__dirname);

var RAPPObject = require(path.join(__objectsDir, 'RAPPObject'));

/**
 * @fileOverview Prototype the RAPP Object Class.
 * 
 * @class Face
 * @description class which should somehow encapsulate a face
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 */ 

/*** 
* Define Face "class" inside an immediate function.
* A bit unconventional way but it's the only way I have found to have the same information flow with C++
* in the way that instances of this Face and only those can have access to private variables of 
* other instances of the same "class" so that member functions like isEqual can work.
*/

RAPPObject.prototype.Face = (function( top_left_x, top_left_y, bottom_right_x, bottom_right_y ){   // immediate function
	
	var _top_left_x = -1;
	var _top_left_y = -1;
	var _bottom_right_x = -1;
	var _bottom_right_y = -1;
	
	var instance = 0; // counts the number of instances
	var faces = []; // an array of private objects
	
	/**
	 * @constructor Face
     	* @description Consruct using face coordinates (a rectangle)
     	* @param top_left_x is the top left x coordinate
     	* @param top_left_y is the top left y coordinate
     	* @param bottom_right_x is the bottom right x coordinate
     	* @param bottom_right_y is the bottom right y coordinate
     	*/
	
	function Face( top_left_x, top_left_y, bottom_right_x, bottom_right_y )
	{
		// Increment the instance count and save it to the instance. 
        // This will become the key to the private space.
		this.i = instance++;
		
		// Create a new object in the private space.
		faces[this.i] = {};
		
		faces[this.i]._top_left_x = top_left_x;
		faces[this.i]._top_left_y = top_left_y;
		faces[this.i]._bottom_right_x = bottom_right_x;
		faces[this.i]._bottom_right_y = bottom_right_y;
	}

	//TODO: A function that can be used as a Copy Constructor
	
	/**
	 * @function isEqual
     * @description Check Equality
     * @param rhs is the Face object to which this object is compared for equality
     */	
	Face.prototype.isEqual = function (rhs) 
	{
		// It has access to the private space and it's children!
		return ( faces[this.i]._top_left_x === faces[rhs.i]._top_left_x &&
                 faces[this.i]._top_left_y === faces[rhs.i]._top_left_y &&
                 faces[this.i]._bottom_right_x === faces[rhs.i]._bottom_right_x &&
                 faces[this.i]._bottom_right_y === faces[rhs.i]._bottom_right_y );
	};
	
	return Face;	
})();


/// Export
module.exports = RAPPObject.Face;
