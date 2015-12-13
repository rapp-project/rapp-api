#C++ RAPP API
The C++ API code is portable, since it relies on cross-platform libraries: BOOST and OpenCV.
It uses asynchronous execution, inspired (and largely supported) by BOOST ASIO.
It has been designed this way on purpose: you can send one or many *jobs* (e.g., service calls)
to the cloud platform, and in the meantime keep the Robot busy with other local processing.

## Building the C++ API
For the C++ RAPP API, please note you need to satisfy certain dependencies:
* A modern C++11 enabled compiler (g++,clang) 
* BOOST library higher than 1.49
* OpenCV higher than 2.0
* CMake higher than 2.8

To build:
```
$ mkdir build
$ cd build
$ cmake ..
$ make -j8
```

## Installing
You may install if you wish to:
```
sudo make install
```

The static and shared library will be installed in `/usr/local/lib/`
whereas the headers are installed in `/usr/local/include/`.
If you wish to change the location, simply edit the appropriate lines in the `CMakeLists.txt`.
    
The global include header is:
```
#include <rapp/rapp>
```

You can, of course include specific headers if you wish to.
To link with it, use the lrapp-0.1.so (shared library) or with the static version.
For linking instructions, please have a look at CMake helpfiles.

## OSes with older G++
Some OSes do not ship with a newer *g++*, or you may be for whatever reason stuck with an older version.
In this case, and assuming you do not want to build a newer g++ in the Robot OS,
you can build the API with a statically linked libstdc.
To do so, edit the `CMakeLists.txt` and comment the following line:

```
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++11 -Wall -fPIC")
```
and uncomment this line:
```
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++11 -Wall -fPIC -static-libstdc++")
```
