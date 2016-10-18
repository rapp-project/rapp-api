# RAPP API 0.7.0
-----------------------

## Contents
- [Building](#building)
- [CMake Options](#cmake-options)
- [Installing](#installing)
- [Testing](#testing)
- [Examples](#examples)
- [Old Compilers](#old-compilers)
- [Tutorials](#tutorials)
- [Documentation](#documentation)
- [Help](#help)

[![Build Status](https://travis-ci.org/rapp-project/rapp-api.svg?branch=cpp_dev)](https://travis-ci.org/rapp-project/rapp-api) [![Join the chat at https://gitter.im/rapp-project/rapp-api](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/rapp-project/rapp-api?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

The RAPP API for C++ uses C++14 features and allows your apps to access the RAPP platform.
It is portable on Linuxes and relies on cross-platform libraries: 
[lib BOOST](http://www.boost.org) and [C++ STL](https://en.wikipedia.org/wiki/Standard_Template_Library).

It uses asynchronous execution, inspired (and supported) by BOOST ASIO.
It has been designed this way on purpose: you can send one or many *jobs* (e.g., service calls)
to the cloud platform, and in the meantime keep the Robot busy with other local processing.

This enables you to write both asynchronous and multithreading robot controllers,
by *daisy-chanining* delegates via subsequent callbacks.

All callback schemes use the `std::function` therefore you can pass 
*lambdas, function pointers, class members and struct functors* as callbacks.

## Building

For the C++ RAPP API, please note you need to satisfy these *dependencies*:
* A modern C++11 enabled compiler (g++, clang) 
* BOOST library higher than 1.49
* CMake higher than 2.8

To build:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

You should end up with a library and/or tests and examples under your build directory.

## CMake Options

*Note* that you can pass a variety of CMake arguments to suit your needs:

* `-DRAPP_SHARED=ON`		                        (Default: compile a shared librapp)
* `-DRAPP_STATIC=ON`		                        (Optional: compile a static librapp)
* `-DBUILD_TESTS=ON`                                (Optional: compile various tests - run with `make test`)
* `-DBUILD_EXAMPLES=ON`                             (Optional: compile various examples)
* `-DCMAKE_BUILD_TYPE=Debug`                        (Optional: enable debug symbols)
* `-DSTATIC_LIBSTD=ON`                              (Optional: compile statically against libstdc++)
* `-DOPEN_NAO=ON`                                   (Optional: compiling on OpenNAO requires additional CXX flags)
* `-DCMAKE_INSTALL_PREFIX=/usr`	                    (Optional: specify the library install directory
* `-DOPENSSL_ROOT_DIR=/usr/local/opt/openssl`       (Optional: specify OpenSSL root directory)
* `-DOPENSSL_LIBRARIES=/usr/local/opt/openssl/lib/` (Optional: specify OpenSSL library directory)

All of those arguments are optional, however depending on your scenario you may have to adjust.
For example, building for a NAO robot the convenience flag `-DOPEN_NAO=ON` will create a static library optimising for an ATOM cpu
using i386 architecture.

## Installing

You may install if you wish to (as root or using `sudo`):

```
make install
```

The produced library will be installed in `/usr/local/lib/` whereas the headers are installed in `/usr/local/include/` by default.

If you wish to install to another location or a user directory then run:

```
-DCMAKE_INSTALL_PREFIX=/other/dir
```

*Bear in mind* that this only changes the library installation location and **not** the header install location.

## Testing

Enable tests when you run cmake by:

```
cmake .. -DBUILD_TESTS=ON
```

This will create a `rapp-api/cpp/build/tests` directory to all the corresponding source files in `rapp-api/cpp/tests`.
There are three types of tests:

* JSON (de)serialisation tests.
* Class unit tests.
* Cloud functionality tests.

To execute them, type:

```
make test
```

*_Warning_*: do not run individual tests from within the `/rapp-api/cpp/build/tests` directory!
*_Note_*: all examples and test have been checked with `valgrind --leak-check=full` under Ubuntu 14.04 and found
to have no memory leaks or segfaults.
If you do happen to run across such issues, please open an issue on GitHub.

## Examples

The source files for the examples are under `/rapp-api/cpp/examples` and if you use the flag `-DBUILD_EXAMPLES=ON` they
will be built under `/rapp-api/cpp/build/examples/`.

## Old Compilers

Some OSes do not ship with a newer *g++* (versions 4.9 and up), or you may be for whatever reason stuck with an older version.
A requirement for version 0.7.0 is to have gcc/g++ >= 4.9, therefore if you are targetting an older platform you have two options:

* build a gcc 4.9 [from source](https://gcc.gnu.org/wiki/InstallingGCC)
* build your apps using a static rapp library

Because the rapp library relies only on `libstdc++` a static link with it increases the executable size,
but allows you to target older systems.
To do so use the cmake flag `-DRAPP_STATIC=ON` by building on a modern machine with *g++* >= 4.9.
However, the boost dependencies also require a somewhat new version of the C runtime libraries.
For further details please see the advanced tutorials.

## Tutorials

We have created two repositories with extensive tutorials and examples, ranging from simple use to advanced projects.
Those tutorials go through every single cloud and object class, and describe how to build applications for Aldebaran's NAO.

* https://github.com/ortelio/rapp_beginner_tutorials.git
* https://github.com/ortelio/rapp_advanced_tutorials.git

## Documentation

For a complete list of the cloud classes and the object classes used by the C++ API,
please read the [Documentation](DOCUMENTATION.md) file.

## Help

If you run into any bugs or issues, please report them on github. 
Alternatively, hit us up on Gitter: [![Join the chat at https://gitter.im/rapp-project/rapp-api](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/rapp-project/rapp-api?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
