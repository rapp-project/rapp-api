#!/usr/bin/env node

// Import the face_detection JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('rapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.face_detection = require('rapp-platform-api/includes/cloud/face_detection');
var services = new RAPPCloud();

/** 
 * This is the method that will handle the reply by the service.face_detection
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function handler(faces)
{
    if (faces.length)
    {
        for (var i=0;i<faces.length;i++)
        {
            console.log("face " + (i+1) + ":");
            console.log("up_left_point: {x: " + faces[i].get_up_left_x() + ", y: " + faces[i].get_up_left_y() + "}"); 
            console.log("down_right_point: {x: " + faces[i].get_down_right_x() + ", y: " + faces[i].get_down_right_y() + "}");
        }
    }
	else
		console.log('No faces detected');
}

services.face_detection('../../testdata/two_faces.jpg', 'jpg', handler );
