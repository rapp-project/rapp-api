#!/usr/bin/env node

var test = require('unit.js');
var path = require('path');

// Import the JS API Objects & Init the RAPPObject Object
var __objectsDir = path.join(__dirname, '..', 'includes', 'objects');
var RAPPObject = require(path.join(__objectsDir, 'RAPPObject.js'));
RAPPObject.face = require(path.join(__objectsDir, 'face.js'));
RAPPObject.qrCode = require(path.join(__objectsDir, 'qrCode.js'));
RAPPObject.human = require(path.join(__objectsDir, 'human.js'));

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
	it('should construct a qrCode object when given the x and y centres and a label', function(){
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

describe('#Human()', function(){
	it('should construct a human object when given the 4 values of coordinates', function(){
		var Human = new objects.Human( 0.1, 0.1, 0.5, 0.5 );
	});
});

describe('#human.isEqual()', function(){
	it('should return true if and only if the label of the human whose isEqual is a member function is equal to the label of the human object given as an argument', function(){
		var human1 = new objects.Human( 0.5, 0.3, 0.1, 0.6 );
		var human2 = new objects.Human( 0.5, 0.3, 0.1, 0.6 );
		var human3 = new objects.Human( 1, 0.3, 0.1, 0.6 );
		test.assert.equal(human1.isEqual(human2), true);
		test.assert.equal(human1.isEqual(human3), false);
	});
});
