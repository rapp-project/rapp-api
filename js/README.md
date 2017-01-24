# JS RAPP API

## Synopsis

Contains RAPPCloud API modules used for interfering wth RAPP Platform as well as the RAPP Objects.

## Application development

You can distribute robotic applications you make using this API through this [Robot Apps Store](https://rapp.cloud/)

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
var RAPPCloud = require('rapp-platform-api/lib/cloud/RAPPCloud');
RAPPCloud.qr_detection = require('rapp-platform-api/lib/cloud/qr_detection');
RAPPCloud.face_detection = require('rapp-platform-api/lib/cloud/face_detection'); 
var services = new RAPPCloud();

services.qr_detection('../../testdata/qrcode.png', 'png', handler);
services.face_detection('../../testdata/faces.png', 'png', handler);
```

For the RAPP platform API objects you would have to point as well, to the respective directory in order to require them:

```js
var RAPPObjects = require('rapp-platform-api/lib/objects/RAPPObject');
RAPPObject.face = require('rapp-platform-api/lib/objects/face');
var objects = new RAPPObject();
```

## Directories

- **lib/config**: The folder with the configurations. 
- **lib/cloud**: The RappCloud services directory.
- **lib/objects**: The Rapp Objects directory.
- **examples**: Examples that showcase how you may use the RAPPCloud services for your convenience.
- **test**: Unit tests for all the services and objects.

## Tests

For the following to run you will also need to install the developer dependencies (check installation section).

In the test directory unit tests for all the services and objects can be found. In order to run them while on root directory type:

```shell
npm test
```

## Examples

The source files for the examples are under the examples folder located in the root of the JS Rapp Platform API.

You can run them individually, or use them as templates.

## Documentation

For a complete list of all RAPP JS API Cloud services and Objects along with their documentation see [here](https://github.com/rapp-project/rapp-api/tree/js/js/lib/README.md)

You might as well want to genetate documentation automatically from the comments of the code.
For the following to run you will also need to install the developer dependencies (check installation section).

This package's source-code is documented using the [JSDoc](https://github.com/jsdoc3/jsdoc) javascript documentation generator.

Generate documentation for the RAPP API Cloud Services only:


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

## Help

If you run into any bugs or issues, please report them on github. 
Alternatively, hit us up on Gitter: [![Join the chat at https://gitter.im/rapp-project/rapp-api](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/rapp-project/rapp-api?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

