#!/usr/bin/env node

var path = require('path');
var __objectsDir = path.join(__dirname);
var RAPPObject = require(path.join(__objectsDir, 'RAPPObject'));

/**
 * @fileOverview Prototype this RAPP Object Class.
 * 
 * @class Human
 * @memberof RAPPObject
 * @description class which should somehow encapsulate a human
 * @version 1
 * @author Lazaros Penteridis <lp@ortelio.co.uk>
 */ 

/*** 
* Define Human "class" inside an immediate function.
* A bit unconventional way but it's the only way I have found to have the same information flow with C++
* in the way that instances of this Human and only those can have access to private variables of 
* other instances of the same "class" so that member functions like is_equal can work.
*/

RAPPObject.prototype.Human = (function(){   // immediate function
	
	var _top_left_x;
	var _top_left_y;
	var _bottom_right_x;
	var _bottom_right_y;
	
	var instance = 0; // counts the number of instances
	var humans = []; // an array of private objects
	
	/**
	 * @constructor Human
     	* @description Consruct using human coordinates (a rectangle)
     	* @param top_left_x is the top left x coordinate
     	* @param top_left_y is the top left y coordinate
     	* @param bottom_right_x is the bottom right x coordinate
     	* @param bottom_right_y is the bottom right y coordinate
     	*/
	
	function Human( top_left_x, top_left_y, bottom_right_x, bottom_right_y )
	{
		// Increment the instance count and save it to the instance. 
        // This will become the key to the private space.
		this.i = instance++;
		
		// Create a new object in the private space.
		humans[this.i] = {};
		
		humans[this.i]._top_left_x = top_left_x;
		humans[this.i]._top_left_y = top_left_y;
		humans[this.i]._bottom_right_x = bottom_right_x;
		humans[this.i]._bottom_right_y = bottom_right_y;
	}

	//TODO: A function that can be used as a Copy Constructor
	
	/**
	 * @function is_equal
     * @description Check Equality
     * @param human2 is the Human object to which this object is compared for equality
     */	
	Human.prototype.is_equal = function (human2) 
	{
		// It has access to the private space and it's children!
		return ( humans[this.i]._top_left_x === humans[human2.i]._top_left_x &&
                 humans[this.i]._top_left_y === humans[human2.i]._top_left_y &&
                 humans[this.i]._bottom_right_x === humans[human2.i]._bottom_right_x &&
                 humans[this.i]._bottom_right_y === humans[human2.i]._bottom_right_y );
	};

    /**
     * @function get_up_left_x
     * @description up_left_x getter
     */
    Human.prototype.get_up_left_x = function()
    {
        return humans[this.i]._top_left_x;
    } 

    /**
     * @function get_up_left_y
     * @description up_left_y getter
     */
    Human.prototype.get_up_left_y = function()
    {
        return humans[this.i]._top_left_y;
    }

    /**
     * @function get_down_right_x
     * @description down_right_x getter
     */
    Human.prototype.get_down_right_x = function()
    {
        return humans[this.i]._bottom_right_x;
    } 

    /**
     * @function get_down_right_y
     * @description down_right_y getter
     */
    Human.prototype.get_down_right_y = function()
    {
        return humans[this.i]._bottom_right_y;
    }


	
	return Human;	
})();


/// Export
module.exports = RAPPObject.Human;
