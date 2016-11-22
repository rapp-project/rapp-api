//#!/usr/bin/env node

var test = require('unit.js');
var path = require('path');

// Import the JS API Objects & Init the RAPPObject Object
var __objectsDir = path.join(__dirname, '..', 'includes', 'objects');
var RAPPObject = require(path.join(__objectsDir, 'RAPPObject.js'));
RAPPObject.face = require(path.join(__objectsDir, 'face.js'));
RAPPObject.qr_code = require(path.join(__objectsDir, 'qr_code.js'));
RAPPObject.human = require(path.join(__objectsDir, 'human.js'));

var objects = new RAPPObject( );

describe('#Face()', function(){
	it('should construct a face when given the 4 values of coordinates', function(){
		var face = new objects.Face( 0.5, 0.3, 0.1, 0.6 );
	});
});

describe('#face.is_equal()', function(){
	it('should return true if and only if the face whose is_equal is a member function is equal to the face given as an argument', function(){
		var face1 = new objects.Face( 0.5, 0.3, 0.1, 0.6 );
		var face2 = new objects.Face( 0.5, 0.3, 0.1, 0.6 );
		var face3 = new objects.Face( 1, 0.3, 0.1, 0.6 );
		test.assert.equal(face1.is_equal(face2), true);
		test.assert.equal(face1.is_equal(face3), false);
	});

});

describe('#QrCode()', function(){
	it('should construct a qr_code object when given the x and y centres and a label', function(){
		var qr_code = new objects.QrCode( 0.1, 0.1, "lazaros" );
	});
});

describe('#qr_code.is_equal()', function(){
	it('should return true if and only if the label of the qr_code whose is_equal is a member function is equal to the label of the qr_code object given as an argument', function(){
		var qr_code1 = new objects.QrCode( 0.1, 0.1, "lazaros" );
		var qr_code2 = new objects.QrCode( 0.1, 0.2, "lazaros" );
		var qr_code3 = new objects.QrCode( 0.1, 0.1, "nao" );
		test.assert.equal(qr_code1.is_equal(qr_code2), true);
		test.assert.equal(qr_code1.is_equal(qr_code3), false);
	});

});

describe('#qr_code.get_label()', function(){
	it('should return the label of the qr_code Object', function(){
		var qr_code = new objects.QrCode( 0.1, 0.1, "lazaros" );
		test.assert.equal(qr_code.get_label(), "lazaros");
	});

});

describe('#Human()', function(){
	it('should construct a human object when given the 4 values of coordinates', function(){
		var Human = new objects.Human( 0.1, 0.1, 0.5, 0.5 );
	});
});

describe('#human.is_equal()', function(){
	it('should return true if and only if the label of the human whose is_equal is a member function is equal to the label of the human object given as an argument', function(){
		var human1 = new objects.Human( 0.5, 0.3, 0.1, 0.6 );
		var human2 = new objects.Human( 0.5, 0.3, 0.1, 0.6 );
		var human3 = new objects.Human( 1, 0.3, 0.1, 0.6 );
		test.assert.equal(human1.is_equal(human2), true);
		test.assert.equal(human1.is_equal(human3), false);
	});
});
