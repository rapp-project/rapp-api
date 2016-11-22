#!/usr/bin/env node

// Import the ontology related JS API Services & Init the RAPPCloud Object
var RAPPCloud = require('rapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.object_detection_learn_object = require('rapp-platform-api/includes/cloud/object_detection_learn_object');
RAPPCloud.object_detection_clear_models = require('rapp-platform-api/includes/cloud/object_detection_clear_models');
RAPPCloud.object_detection_load_models = require('rapp-platform-api/includes/cloud/object_detection_load_models');
RAPPCloud.object_detection_find_objects = require('rapp-platform-api/includes/cloud/object_detection_find_objects');

var services = new RAPPCloud();
var pic = "../../testdata/cat.jpg";

/** 
 * This is the method that will handle the reply by the following services:
 * object_detection_learn_object, object_detection_load_models, object_detection_clear_models
 * All it does is receive an int to indicate the state.
 */
function callback (result)
{
    switch(result){
        case 0:
            console.log("Correct");
            break;
        case -1:
            console.log("No models loaded");
            break;
        case -2:
            console.log("No image to analyze");
            break;
        default:
            console.log("Error");
            break;
    }
}

/** 
 * This is the method that will handle the reply by the object_detection_find_objects service
 * All it does is receive and print the data of the objects found
 */
function find_cb (names, centers, scores, result)
{
    console.log("Found the following objects: ");
    for (var i=0;i<names.length;i++)
        console.log(names[i]);
    console.log("In the following centers:");
    for (var i=0;i<centers.length;i++)
        console.log(centers[i]);
    console.log("With the following scores:");
    for (var i=0;i<scores.length;i++)
        console.log(scores[i]);
    console.log("Result: " + result);
}

services.object_detection_learn_object(pic, "cat", callback);
services.object_detection_load_models(names, callback);
services.object_detection_find_objects(pic, 1, find_cb);
services.object_detection_clear_models(callback);
