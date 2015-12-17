## Synopsis

Containes RAPPCloud API modules used for interfering wth RAPP Platform as well as the RAPP Objects.


### Dependencies

To use this JS API you need nodejs and npm.
You can run the global_deps_install_script.sh located in the root folder to install them along with grunt-cli and mocha which are the global dependencies the API needs for task management and testing.

After that you can install all the required npm modules (development and production) with:

```shell
$ npm install
```
or

```shell
$ make deps
```

### Installation

To install the API globally, given that you have installed all the dependencies as explained in the previous step, you must type:

```shell
$ sudo make install
```

If at some point you no longer wish to have this API on your system you can remove it by typing:

```shell
$ sudo make uninstall
```

## Usage

The examples located in the examples directory showcase how you may use the RAPPCloud services for your convenience.
Provided you have succesfully installed the API globally in your system (sudo make install), you can require the service(s) that you want to use in your application, after requiring the RAPPCloud module as shown in the examples:

```shell
var RAPPCloud = require('RAPPCloud');
RAPPCloud.qrDetector = require('qrDetector');
```

You can run all the examples as executables, eg. ./face_detect.js


###  Configurations

On default the RAPP API connects on the RAPP Platform installed **LOCALLY**.
TODO: Provide the configuration parameters to connect the API to:

- The RAPP Platform Deployment Server.
- The RAPP Platform Development Server.


### How to use the RappCloud services

The examples located in the examples directory showcase how you may use the RAPPCloud services for your convenience.


## Directories

- **includes/cloud**: The RappCloud services directory.
- **includes/objects**: The Rapp Objects directory.
- **examples**: Examples that showcase how you may use the RAPPCloud services for your convenience.
- **test**: Unit tests for all the services and objects.


## Tests

In the test directory unit tests for all the services and objects can be found. In order to run them:

```shell
$ make test
```

## Documentation

This package's source-code is documented using the [JSDoc](https://github.com/jsdoc3/jsdoc) javascript documentation generator.

Generate documentation for the RAPP API Cloud Services ONLY!:

```shell
$ grunt jsdoc:cloud
```

Generate documentation for the RAPP API Objects ONLY!:

```shell
$ grunt jsdoc:objects
```

Gererate documentation for ALL:

```shell
$ make doc
```

Or

```shell
$ grunt jsdoc
```

Makefile tasks integrates grunt tasks on generating source-code documentation.


Generated doc files are located under the **doc/** directory.


## Contributors

- Lazaros Penteridis, **[lp@ortelio.co.uk]**
