#!/usr/bin/env node

var test = require('unit.js');
var path = require('path');

// Import the faceDetector JS API Service & Init the RAPPCloud Object
var __objectsDir = path.join(__dirname, '..', 'includes', 'objects');
var RAPPObject = require(path.join(__objectsDir, 'RAPPObject.js'));
RAPPObject.face = require(path.join(__objectsDir, 'face.js'));
RAPPObject.qrCode = require(path.join(__objectsDir, 'qrCode.js'));

var objects = new RAPPObject( );

describe('#Face()', function(){
	it('should construct a face when given the 4 values of coordinates', function(){
		var face = new objects.Face( 0.5, 0.3, 0.1, 0.6 );
	});
});

describe('#face.isEqual()', function(){
	it('should return true if and only if the face whose isEqual is a member function is equal to the face given as an argument', function(){
		var face1 = new objects.Face( 0.5, 0.3, 0.1, 0.6 );
		var face2 = new objects.Face( 0.5, 0.3, 0.1, 0.6 );
		var face3 = new objects.Face( 1, 0.3, 0.1, 0.6 );
		test.assert.equal(face1.isEqual(face2), true);
		test.assert.equal(face1.isEqual(face3), false);
	});

});

describe('#QrCode()', function(){
	it('should construct a qrCode when given the x and y centres and a label', function(){
		var qrCode = new objects.QrCode( 0.1, 0.1, "lazaros" );
	});
});

describe('#qrCode.isEqual()', function(){
	it('should return true if and only if the label of the qrCode whose isEqual is a member function is equal to the label of the qrCode object given as an argument', function(){
		var qrCode1 = new objects.QrCode( 0.1, 0.1, "lazaros" );
		var qrCode2 = new objects.QrCode( 0.1, 0.2, "lazaros" );
		var qrCode3 = new objects.QrCode( 0.1, 0.1, "nao" );
		test.assert.equal(qrCode1.isEqual(qrCode2), true);
		test.assert.equal(qrCode1.isEqual(qrCode3), false);
	});

});

describe('#qrCode.label()', function(){
	it('should return the label of the qrCode Object', function(){
		var qrCode = new objects.QrCode( 0.1, 0.1, "lazaros" );
		test.assert.equal(qrCode.label(), "lazaros");
	});

});
