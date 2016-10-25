#!/usr/bin/env node

// Import the human_detection JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('rapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.human_detection = require('rapp-platform-api/includes/cloud/human_detection');
var services = new RAPPCloud( );

/** 
 * This is the method that will handle the reply by the services.human_detection
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function handler ( humans )
{
    if (humans.length)
    {
        for (var i=0;i<humans.length;i++)
        {
            console.log("human " + (i+1) + ":");
            console.log("up_left_point: {x: " + humans[i].get_up_left_x() + ", y: " + humans[i].get_up_left_y() + "}"); 
            console.log("down_right_point: {x: " + humans[i].get_down_right_x() + ", y: " + humans[i].get_down_right_y() + "}");
        }
    }
	else
		console.log('No humans detected');
}

services.human_detection( '../../testdata/face_samples/fatsaSou_near.jpg', 'jpg', handler );
