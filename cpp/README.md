# RAPP API 0.7.0
-----------------------

1. [Building](#Building)
1. [CMake Options](#CMake Options)
1. [Installing](#Installing)
1. [Testing](#Testing)
1. [Examples](#Examples)
1. [Older gcc/g++](#Older gcc/g++)
1. [Tutorials](#Tutorials)
1. [Documentation](#Documentation)
1. [Help](#Help)

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

##Building

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

##CMake Options

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

##Installing

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

##Testing

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

##Examples

The source files for the examples are under `/rapp-api/cpp/examples` and if you use the flag `-DBUILD_EXAMPLES=ON` they
will be built under `/rapp-api/cpp/build/examples/`.

##Older gcc/g++

Some OSes do not ship with a newer *g++* (versions 4.9 and up), or you may be for whatever reason stuck with an older version.

In this case, and assuming you do not want to build a newer g++ in the Robot OS,
you can build the API with a statically linked libstdc on another machine, and then transfer the binary file.

To do so use the cmake flag `-DRAPP_STATIC=ON` by building on a modern machine with *g++* >= 4.9.

##Tutorials

We have created two repositories with extensive tutorials and examples, ranging from simple use to advanced projects.
Those tutorials go through every single cloud and object class, and describe how to build applications for Aldebaran's NAO.

* https://github.com/ortelio/rapp_beginner_tutorials.git
* https://github.com/ortelio/rapp_advanced_tutorials.git

##Documentation

- C++ API cloud classes
  - [Available Services](#available-services)
  - [Cognitive Exercices](#cognitive-exercises)
    - [Test Selector](#cognitive-test-selector)
    - [Record Performance](#cognitive-record-performance)
    - [Get History](#cognitive-get-history)
    - [Get Scores](#cognitive-get-scores)
  - [Email](#email)
    - [Fetch email](#email-fetch)
    - [Send email](#email-send)
  - [Geolocation](#geolocation)
  - [News](#news)
  - [Ontology](#ontology)
    - [Subclasses of](#ontology-subclasses-of)
    - [Superclasses of](#ontology-superclasses-of)
    - [Is Subclass Superclass of](#ontology-is-subsuperclass-of)
  - [Path Planning](#path-planning)
    - [Path Plan 2D](#path-planning-2d) 
    - [Path Upload Map](#path-upload-map)

###available-services

A call which will return a list of pairs of strings, the first string naming the service name and the second defining the URL.

**Input arguments**
- `std::function<void(std::vector<service>)> callback` : a callback functor receiving the list of services

**Return values**
- The `service` type is defined as `typedef std::pair<std::string, std::string> service`

See example: `rapp-api/cpp/examples/available_services.cpp`

###cognitive-exercises

A series of classes which are used to play cognitive games.
Types of games are:

- ArithmeticCts
- AwarenessCts
- ReasoningCts

###cognitive-test-selector

A call which will select a test.
**Input arguments**
- `const std::string test_type`: sets the type of test
- `const std::string test_subtype`: sets the test sub-type
- `const std::string test_diff`: sets the difficulty value
- `const std::string test_index`: sets the exercise index
- `functor callback`: receives a `functor` type (see below)

The `functor` is type-defined as:

```
typedef std::function<void(std::vector<std::string>,
                           std::vector<std::vector<std::string>>,
                           std::vector<std::string>,
                           std::string,
                           std::string,
                           std::string)> functor;
```

The items in the functor represent the return values.

**Return values**
- array questions
- possible answers
- correct answers
- test instance names
- exercise type
- exercise sub type
- error message

See example `rapp-api/cpp/examples/cognitive_games.cpp`

###cognitive-record-performance

A call used to record performance for a user.

**Input arguments**
- `const std::string test_instance`: specifies the test
- `const float score`: sets the score
- `std::function<void(std::string)> callback` will receive the platform's response

**Return values**
- `std::string`: a performance entry

See example `rapp-api/cpp/examples/cognitive_games.cpp`

###cognitive-get-history

A call used to obtain user's history.

**Input arguments**
- `unsigned int from_time`: starting from time
- `unsigned int to_time`:  ending time
- `const std::string test_type`: test type
- `std::function<void(std::string)> callback`: functor receiving return values

**Return values**
- `std::string`: a JSON record of user's history (not-parsed)

See example `rapp-api/cpp/examples/cognitive_games.cpp`

###cognitive-get-scores

A call used to quqery scores.

**Input arguments**
- `unsigned int up_to_time`: query scores up to a specific time
- `const std::string test_type`: the type of test
- `std::function<void(std::vector<std::string>, std::vector<float>)> callback`: functor will receive return values

**Return values**
- `std::vector<std::string>`: name of test type
- `std::vector<float>`: respective score for test

See example `rapp-api/cpp/examples/cognitive_games.cpp`


###email

The platform supports sending and receiving email, when using your own
email account.

###email-fetch

Request to fetch email from your account.

**Input arguments**
- `const std::string email`: email account username
- `const std::string pwd`: plaintext password
- `const std::string server`: IMAP server address
- `const std::string port`: IMAP Port
- `const std::string email_status`: email status (ALL, UNSEEN)
- `const unsigned int from_date`: fetch from date (UNIX timestamp)
- `const unsigned int to_date`: fetch to date (UNIX timestamp)
- `const unsigned int num_emails`: limit number of emails

The callback functor receives the return values.

**Return values**
- `std::string`: sender address
- `std::vector<std::string>`: receivers
- `std::string`: body text (plaintext or html)
- `std::string`: date
- `std::vector<std::string>`: list of attachements

See example `rapp-api/cpp/examples/email_handling.cpp`

###email-send

Request an email to be sent.

**Input arguments**
- `const std::string email`: user's email address/username
- `const std::string pwd`: user's password
- `const std::string server`: SMTP server 
- `const std::string port`: SMTP port
- `const std::vector<std::string> recipients`: list of email addresses
- `const std::string body`: actual email body (plaintext or html)
- `const std::string subject`: email subject
- `const std::vector<rapp::types::byte> data`: a vector of attachments, of raw binary data

The callback functor may receive a JSON of errros.

**Return values**
- `std::string`: a JSON of errors (will default to empty if no errrors)


###geolocation

Quering your location based on the IP of the robot.
Requires that you can establish what the external interface/address is.

**Input arguments**
- `const std::string ipaddr`: the robot's IP address
- `const std::string engine`: the query engine (use `ip-api`)

Callback functor receives return values.

**Return values**
- `std::string`: City
- `std::string`: Country
- `std::string`: Country code
- `float`: latitude
- `float`: longtitude
- `std::string`: zip/postcode
- `std::string`: timezone

See example `rapp-api/cpp/examples/geolocation.cpp`

###ontology

The Platform supports querying a KnowRob/RoboEarth instance.
Eeach type of query returns an XML URI, which you'll have to visit and parse
in order to obtain meaningful meta-data.

###ontology-subclasses-of

Query the sub-classes of a class.

**Input arguments**
- `std::string ontology_class`: the entity being queried
- `bool recursive`: set to true if you wish to search recursively

The callback functor will receive the return values.

**Return values**
- `std::vector<std::string>`: a list of subclasses

See example `rapp-api/cpp/examples/knowrob_ontology.cpp`

###ontology-superclasses-of

Query the super-classes of a class.

**Input arguments**
- `const std::string ontology_class`: the entity being queried
- `bool recursive`: set to true if you wish to search recursively

The callback functor will receive the return values.

**Return values**
- `std::vector<std::string>`: a list of subclasses

See example `rapp-api/cpp/examples/knowrob_ontology.cpp`

###ontology-is-subsuperclass-of

Query if a sub-class is the super-class of another entity.

**Input arguments**
- `const std::string parent_class`: the super-class queried
- `const std::string child_class`: the sub-class queried
- `bool recursive`: set to true for a recursive search

The callback functor will receive the return values.

**Return values**
- `std::vector<bool>`: true if the subclass is the super class of the query, false if not

See example `rapp-api/cpp/examples/knowrob_ontology.cpp`

###path-planning

The platform offers a path planning service.
The requirement is that you must upload a map, and index the name of the map.
You may then request a path using that map and certain parameters.

###path-planning-2d


###path-upload-map


##Help

If you run into any bugs or issues, please report them on github. 
Alternatively, hit us up on Gitter: [![Join the chat at https://gitter.im/rapp-project/rapp-api](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/rapp-project/rapp-api?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
