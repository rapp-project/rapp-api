# RAPP-API
--------------------

## Synopsis

The below table presents the up-to-date available RAPP Platform Service calls, throught the relevant RAPP-API (Python, JavaScript, C++)

- ✓   : Implemented and tested as a part of the relevant RAPP-API.
- ✗   : Not yet implemented

| Platform Services                 | C++      | JavaScript   | Python   |
| :-------------------------------: | :---:    | :----------: | :---:    |
| face detection                    | ✓        |  ✓           | ✓        |
| qr detection                      | ✓        |  ✓           | ✓        |
| text to speech                    | ✗        |  ✗           | ✓        |
| de-noise profile                  | ✓        |  ✓           | ✓        |
| speech to text (sphinx4)          | ✓        |  ✓           | ✓        |
| speech to text (google)           | ✗        |  ✓           | ✓        |
| object recognition                | ✓        |  ✗           | ✓        |
| available services                | ✓        |  ✗           | ✓        |
| ontology subclasses of            | ✓        |  ✓           | ✓        |
| ontology superclasses of          | ✓        |  ✓           | ✓        |
| ontology is subsuperclass of      | ✓        |  ✓           | ✓        |
| cognitive test chooser            | ✗        |  ✗           | ✓        |
| record cognitive test performance | ✗        |  ✗           | ✓        |

// TODO: RAPP Robot API


Information on RAPP Platform front-end Web Services can he found [here](https://github.com/rapp-project/rapp-platform/tree/master/rapp_web_services/services).

## Directories

- `cpp/`    : C++ RAPP-API Sources
- `js/`     : JavaScript RAPP-API Sources
- `python/` : Python RAPP-API Sources

## Tests

* C++ Unit testing, see `/tests`

[![Join the chat at https://gitter.im/rapp-project/rapp-api](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/rapp-project/rapp-api?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

## Contributors

- Alexander Giokas, **[a.gkiokas@ortelio.co.uk]**
- Konstaninos Panayiotou, **[klpanagi@gmail.com]**
- Lazaros Penteridis, **[lp@ortelio.co.uk]**
