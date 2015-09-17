#!/usr/bin/env node


// Import the ontologySubclassOf JS API & Init the RAPPCloud Object
var RAPPObject = require('./face.js');
var objects = new RAPPObject( );

var face1 = new objects.Face( 3, 5, 6, 8 );
var face2 = new objects.Face( 3, 4, 6, 8 );

console.log(face1.isEqual(face2));

