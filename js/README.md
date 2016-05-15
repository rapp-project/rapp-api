# JS RAPP API

## Synopsis

Containes RAPPCloud API modules used for interfering wth RAPP Platform as well as the RAPP Objects.


## Dependencies

To use this JS API you need nodejs and npm.
You can run the global_deps_install_script.sh located in the root folder to install them along with grunt-cli and mocha which are the global dependencies the API needs for task management and testing.

The rest dependencies (required npm modules), will be taken care of, from npm while you install the rapp-platform-api package.


## Installation

Installing the rapp-platform-api is as easy as 

```shell
npm install rapp-platform-api
```

To install it globally:

```shell
npm install rapp-platform-api -g
```


## Usage

The examples located in the examples directory showcase how you may use the RAPPCloud services for your convenience.
Provided you have succesfully installed the API in your system, you can require the service(s) that you want to use in your application, after requiring the RAPPCloud module as shown in the examples:

```shell
var RAPPCloud = require('rapp-platform-api/includes/cloud/RAPPCloud');
RAPPCloud.qrDetector = require('rapp-platform-api/includes/cloud/qrDetector');
```

For the RAPP platform API objects you would have to point as well, to the respective directory in order to require them:

```shell
var RAPPObjects = require('rapp-platform-api/includes/cloud/RAPPObject');
RAPPObject.face = require('rapp-platform-api/includes/objects/face');
```


##  Configurations

On default the RAPP API connects on a RAPP Platform installed **LOCALLY**.
TODO: Provide the configuration parameters to connect the API to:

- The RAPP Platform Deployment Server.
- The RAPP Platform Development Server.


## Directories

- **includes/cloud**: The RappCloud services directory.
- **includes/objects**: The Rapp Objects directory.
- **examples**: Examples that showcase how you may use the RAPPCloud services for your convenience.
- **test**: Unit tests for all the services and objects.


## Tests

In the test directory unit tests for all the services and objects can be found. In order to run them while on root directory type:

```shell
npm test
```

## Documentation

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


## Contributors

- Lazaros Penteridis, **[lp@ortelio.co.uk]**
