## Synopsis

Containes RappCloud API modules used for interfering wth RAPP Platform.


### Dependencies

You need nodejs and npm.
To install them run the node_npm_install_script.sh

After that you can install all the required npm modules (development and production) with:

```shell
$ npm install
```
or

```shell
$ make deps
```

## Usage

The examples located in the examples directory showcase how you may use the RAPPCloud services for your convenience.
After you have all the dependancies installed you can run all the examples as executables, eg. ./face_detect.js


####  Configurations

On default the RAPP API connects on the RAPP Platform installed **LOCALLY**.
TODO: Provide the configuration parameters to connect the API to:

- The RAPP Platform Deployment Server.
- The RAPP Platform Development Server.


### How to use the RappCloud services

The examples located in the examples directory showcase how you may use the RAPPCloud services for your convenience.


## Install

--TODO--


## Directories

- **includes/cloud**: The RappCloud services directory.
- **includes/objects**: The Rapp Objects directory.
- **examples**: Examples that showcase how you may use the RAPPCloud services for your convenience.
- **test**: Unit tests for all the services and objects.


## Tests

In the test directory unit tests for all the services and objects can be found. In order to run them you will need to install unitjs and mocha globally.


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
