# JS RAPP API

## Synopsis

Containes RAPPCloud API modules used for interfering wth RAPP Platform as well as the RAPP Objects.

## Dependencies

To use this JS API you need nodejs and npm.
You can run the global_deps_install_script.sh located in the root folder to install them along with grunt-cli and mocha which are the global dependencies the API needs for task management and testing.

The rest dependencies (required npm modules), will be taken care of, from npm, while you install the rapp-platform-api package.

## Installation

Installing the rapp-platform-api is as easy as 

```shell
npm install rapp-platform-api
```

To install it globally:

```shell
npm install rapp-platform-api -g
```

If you also want to install the developer depencdencies, go to the root folder of the project and execute:

```shell
npm install
```

## Usage

The examples located in the examples directory showcase how you may use the RAPPCloud services for your convenience.
Provided you have succesfully installed the API in your system, you can require the service(s) that you want to use in your application, after requiring the RAPPCloud module as shown in the examples:

```js
var RAPPCloud = require('rapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.qr_detection = require('rapp-platform-api/includes/cloud/qr_detection');
RAPPCloud.face_detection = require('rapp-platform-api/includes/cloud/face_detection'); 
var services = new RAPPCloud();

services.qr_detection('../../testdata/qrcode.png', 'png', handler);
services.face_detection('../../testdata/faces.png', 'png', handler);
```

For the RAPP platform API objects you would have to point as well, to the respective directory in order to require them:

```js
var RAPPObjects = require('rapp-platform-api/includes/objects/RAPPObject');
RAPPObject.face = require('rapp-platform-api/includes/objects/face');
var objects = new RAPPObject();
```

## Directories

- **includes/cloud**: The RappCloud services directory.
- **includes/objects**: The Rapp Objects directory.
- **examples**: Examples that showcase how you may use the RAPPCloud services for your convenience.
- **test**: Unit tests for all the services and objects.

## Tests

For the following to run you will also need to install the developer dependencies (check installation section).

In the test directory unit tests for all the services and objects can be found. In order to run them while on root directory type:

```shell
npm test
```

## Documentation

For the following to run you will also need to install the developer dependencies (check installation section).

This package's source-code is documented using the [JSDoc](https://github.com/jsdoc3/jsdoc) javascript documentation generator.

Generate documentation for the RAPP API Cloud Services only:

For the documentation of all RAPP Cloud services and Objects see [here](https://github.com/rapp-project/rapp-api/tree/js/js/includes/README.md)

```shell
npm run doc-cloud
```

Generate documentation for the RAPP API Objects only:

```shell
npm run doc-objects
```

Gererate documentation for ALL:

```shell
npm run doc
```

Or

```shell
grunt jsdoc
```

Generated doc files are located under the **doc/** directory.

## Contributors

- Lazaros Penteridis, **[lp@ortelio.co.uk]**
