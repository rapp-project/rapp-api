# RAPP API (C++11)

The C++ API code is portable, since it relies on cross-platform libraries: 
- [lib BOOST](http://www.boost.org) and [C++ STL](https://en.wikipedia.org/wiki/Standard_Template_Library).

It uses asynchronous execution, inspired (and supported) by BOOST ASIO.
It has been designed this way on purpose: you can send one or many *jobs* (e.g., service calls)
to the cloud platform, and in the meantime keep the Robot busy with other local processing.

This enables you to write both asynchronous and multithreading robot controllers,
by *daisy-chanining* delegates via subsequent callbacks.

All callback schemes use the new C++11 `std::function` therefore you can pass 
*lambdas, function pointers, class members and struct functors* as callbacks.

# Building

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

*Note* that you can pass a variety of CMake arguments to suit your needs:

* `-DBUILD_RAPP_SHARED_LIBS=ON` enabled by default, will create a shared library
* `-DBUILD_RAPP_STATIC_LIBS=ON` optional, will create a static library
* `-DBUILD_TESTS=ON`            optional, compile various tests - run with `make test`
* `-DBUILD_EXAMPLES=ON`         optional, compile various examples (see directory `build`)
* `-DCMAKE_BUILD_TYPE=Debug`    optional, enable debug symbols - default is `Release`
* `-DSTATIC_LIBSTD=ON`          optional, compile statically against libstdc++
* `-DOPEN_NAO=ON`               optional, compiling on OpenNAO requires additional CXX flags

# Installing

You may install if you wish to (as root or with `sudo`):
```
make install
```

The static and shared library will be installed in `/usr/local/lib/`
whereas the headers are installed in `/usr/local/include/`.
If you wish to change the location, simply edit the appropriate lines in the `CMakeLists.txt`.

The global include header is:
```
#include <rapp/rapp>
```

You can of course include specific headers if you wish to.

To link with the `api` use the `librapp.so` (shared library) or with the static version `librapp.a`.
For linking instructions, please have a look at CMake helpfiles.

# OS with old gcc/g++

Some OSes do not ship with a newer *g++* (versions 4.8 and up), 
or you may be for whatever reason stuck with an older version.

In this case, and assuming you do not want to build a newer g++ in the Robot OS,
you can build the API with a statically linked libstdc on another machine, and then transfer the binary file.

To do so use `-DSTATIC_LIBSTD=ON -DBUILD_RAPP_STATIC_LIBS=ON`.

For `OpenNao` you may have to also enable `-DOPEN_NAO=ON` which adds two more link flags (`-lc++ -lcxxrt`)
and attempts to build for `i386` cpu-architecture.

Additional flags should be added in the `CMakeLists.txt` if you plan on doing a *multiarch* compilation.
For example, building for OpenNAO, might require a `CXXFLAGS -m32` (already included in the `-DOPEN_NAO=ON`).

We haven't as of yet, tested the API on `arm` platforms.

# Bugs/Help

If you run into any bugs or issues, please report them on github, or using [![Join the chat at https://gitter.im/rapp-project/rapp-api](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/rapp-project/rapp-api?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
