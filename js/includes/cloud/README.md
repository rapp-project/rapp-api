- RAPP Platform JS API calls
  - [Cognitive Exercises - Test Selector](#cognitive-exercises---test-selector)
  - [Cognitive Exercises - Get History Records](#cognitive-exercises---get-history-records)
  - [Cognitive Exercises - Get Scores](#cognitive-exercises---get-scores)
  - [Cognitive Exercises - Record Performance](#cognitive-exercises---record-performance)
  - [Email - Fetch Received Emails](#email---fetch-received-emails)
  - [Email - Send](#email---send)
  - [Face detection](#face-detection)
  - [Geolocation](#geolocation)
  - [Human detection](#human-detection)
  - [Hazard detection - Door](#hazard-detection---door)
  - [Hazard detection - Lights](#hazard-detection---lights)
  - [News Explorer](#news-explorer)
  - [Object recognition Caffe](#object-recognition-caffe)
  - [Ontology Query - Subclasses of](#ontology-query---subclasses-of)
  - [Ontology Query - Superclasses of](#ontology-query---superclasses-of)
  - [Ontology Query - Is Subsuperclass of](#ontology-query---is-subsuperclass-of)
  - [Path Planning - Plan Path 2D](#path-planning---plan-path-2d)
  - [Path Planning - Upload Map](#path-planning---upload-map)
  - [Qr detection](#qr-detection)
  - [Set Noise Profile](#set-noise-profile)
  - [Speech Recognition Sphinx](#speech-recognition-sphinx)
  - [Speech Recognition Google](#speech-recognition-google)
  - [Text To Speech](#text-to-speech)
  - [Weather Reporter - Current Weather](#weather-reporter---current-weather)
  - [Weather Reporter - Forecast](#weather-reporter---forecast)


***

## Face detection

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Face-Detection)

**Sample call** ```face_detection(image, image_format, callback, fast)```

**Input arguments**
- ```image```: string with the path of the input image
- ```image_format```: string, the format of the input image
- ```callback```: the function that will receive a vector of the detected face(s) coordinates
- ```fast```: string. Only valid values are 'true' and 'false'. When 'true' the fast face detection service is called, which should be used for tracking applications. 

**Data returned to callback**
```js
function handler(faces){...} // faces: An array of found face Objects (see includes/objects/face.js). A face is described by an up_left_point and a down_right_point in cartesian coordinates:
// face: { up_left_point: {<point2D>}, down_right_point: {<point2D>} } where point2D is an object of structure:
// point2D: { x: <value_int>, y: <value_int> }
```

**Call example**:
```js
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
// Do something with the faces
}

services.face_detection('../../testdata/two_faces.jpg', 'jpg', handler );
```

**Example output**:
```js
for (var i=0;i<faces.length;i++)
{
    console.log("face " + (i+1) + ":");
    
    console.log("up_left_point: {x: " + faces[i].get_up_left_x() + ", y: " + faces[i].get_up_left_y() + "}"); 
    console.log("down_right_point: {x: " + faces[i].get_down_right_x() + ", y: " + faces[i].get_down_right_y() + "}");
}
```
```bash
face 1:
up_left_point: {x: 79, y: 94}
down_right_point: {x: 281, y: 296}
face 2:
up_left_point: {x: 416, y: 97}
down_right_point: {x: 616, y: 297}
```

## Qr detection

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-QR-Detection)

**Sample call** ```qr_detection(image, image_format, callback)```

**Input arguments**
- ```image```: string with the path of the input image
- ```image_format```: string, the format of the input image
- ```callback```: the function that will receive a vector of the detected qr code(s) coordinates

**Data returned to callback**
```js
function handler(qr_codes){...} // qr_codes: An array of found qr_code Objects (see includes/objects/qr_code.js).
// A qr_code is described by a centre in cartesian coordinates and a label(message):
// Center points (point2D) of found QR codes
// qr_centers: [{<point2D_1>}, ..., {<point2D_n>}] where point2D is an object of structure:
// point2D: { x: <value_int>, y: <value_int> }
// although this structure is not accessible from the scope out of the object without the use of its getter functions. 
```

**Call example**:
```js
#!/usr/bin/env node

// Import the qr_detection JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('rapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.qr_detection = require('rapp-platform-api/includes/cloud/qr_detection');
var services = new RAPPCloud();

/** 
 * This is the method that will handle the reply by the service.face_detection
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function handler(qr_codes) 
{
// Do something with the qr_codes
}

services.qr_detection('../../testdata/qrcode.png', 'png', handler );
```

**Example output**:
```js
for (var i=0;i<faces.length;i++)
{
    console.log ( "Found " + codes.length + " qr codes!");
    for (var i=0; i<codes.length; i++) {
        console.log("qr code " + (i+1) + ":");
	    console.log("    centre: {x: " + codes[i].get_centre_x() + ", y: " + codes[i].get_centre_y() + "}");
        console.log("    label: " + codes[i].get_label() + " ");
	}
}
```
```bash
Found 1 qr codes!
qr code 1:
    centre: {x: 86, y: 86}
    label: http://www.qrstuff.com
```

***

## Human detection

**Description** [here](https://github.com/rapp-project/rapp-platform/wiki/RAPP-Human-Detection)

**Sample call** ```human_detection(image, image_format, callback)```

**Input arguments**
- ```image```: string with the path of the input image
- ```image_format```: string, the format of the input image
- ```callback```: the function that will receive a vector of the detected human(s) coordinates

**Data returned to callback**
```js
function handler(humans){...} // humans: An array of found human Objects (see includes/objects/human.js).
# humans: [ {<human_1>}, ..., {<human_n>} ] where human_x is an object of internal, although not accessible from the outside without the use of its getter functions, structure:
# human: { up_left_point: {x: 0, y: 0}, down_right_point: {x: 0, y: 0} }
```

**Call example**:
```js
#!/usr/bin/env node

// Import the human_detection JS API Service & Init the RAPPCloud Object
var RAPPCloud = require('rapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.human_detection = require('rapp-platform-api/includes/cloud/human_detection');
var services = new RAPPCloud();

/** 
 * This is the method that will handle the reply by the service.face_detection
 * Do what you want with it - REMEMBER: The service is Asynchronous!!!
 */
function handler(humans) 
{
// Do something with the humans
}

services.human_detection('../../testdata/face_samples/fatsaSou_near.jpg', 'jpg', handler );
```

**Example output**:
```js
for (var i=0;i<humans.length;i++)
{
    console.log("human " + (i+1) + ":");
    console.log("up_left_point: {x: " + humans[i].get_up_left_x() + ", y: " + humans[i].get_up_left_y() + "}"); 
    console.log("down_right_point: {x: " + humans[i].get_down_right_x() + ", y: " + humans[i].get_down_right_y() + "}");
}
```
```bash
human 1:
up_left_point: {x: 1225, y: 480}
down_right_point: {x: 1331, y: 692}
```

***

