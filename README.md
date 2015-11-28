# RAPP-API
--------------------

## Synopsis

The below table presents the up-to-date available RAPP Platform Service calls, throught the relevant RAPP-API (Python, JavaScript, C++)


- ✓   : Implemented and tested as a part of the relevant RAPP-API.
- ✗   : Not yet implemented


| Platform Services                 | C++      | JavaScript   | Python   |
| :-------------------------------: | :---:    | :----------: | :---:    |
| face_detection                    | ✓        |  ✓           | ✓        |
| qr_detection                      | ✓        |  ✓           | ✓        |
| text_to_speech                    | ✗        |  ✗           | ✓        |
| denoise_profile                   | ✓        |  ✓           | ✓        |
| speech_detection_sphix4           | ✓        |  ✓           | ✓        |
| speech_detection_google           | ✗        |  ✗           | ✓        |
| object_recognition                | ✓        |  ✗           |          |
| available_services                | ✓        |  ✗           | ✓        |
| ontology_subclasses_of            | ✓        |  ✓           | ✓        |
| ontology_superclasses_of          | ✓        |  ✓           | ✓        |
| ontology_is_supsuperclass_of      | ✓        |  ✓           | ✓        |
| cognitive_test_chooser            | ✗        |  ✗           | ✓        |
| record_cognitive_test_performance | ✗        |  ✗           | ✓        |



Information on RAPP Platform Services can he found [here](https://github.com/rapp-project/rapp-platform/tree/master/rapp_web_services/services).

## Directories

- `cpp/`    : C++ RAPP-API Sources
- `js/`     : JavaScript RAPP-API Sources
- `python/` : Python RAPP-API Sources


## Tests

## Building C++

For the C++ RAPP API, please note you need to satisfy certain dependencies:

* A modern C++11 enabled compiler (g++,clang) 
* BOOST library higher than 1.49
* OpenCV higher than 2.0
* CMake higher than 2.8

First create a build directory:
` $mkdir build`

` cd build`

Then run cmake:

`$ cmake ..`

Finally build:

`$ make -j8`

## Contributors

- Alexander Gkiokas, **[a.gkiokas@ortelio.co.uk]**
- Konstaninos Panayiotou, **[klpanagi@gmail.com]**
- Lazaros Penteridis, **[lp@ortelio.co.uk]**
