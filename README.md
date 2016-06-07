# RAPP-API
--------------------

## Synopsis

The below table presents the up-to-date available RAPP Platform Service calls, throught the relevant RAPP-API (Python, JavaScript, C++)

- ✓   : Implemented and tested as a part of the relevant RAPP-API.
- ✗   : Not yet implemented

| Platform Services                 | C++      | JavaScript   | Python   |
| :-------------------------------: | :---:    | :----------: | :---:    |
| Face detection                    | ✓        |  ✓           | ✓        |
| Qr detection                      | ✓        |  ✓           | ✓        |
| Text to Speech                    | ✗        |  ✗           | ✓        |
| De-noise profile                  | ✓        |  ✓           | ✓        |
| Speech to Text (sphinx4)          | ✓        |  ✓           | ✓        |
| Speech to Text (google)           | ✗        |  ✓           | ✓        |
| Object Recognition Caffe          | ✓        |  ✗           | ✓        |
| Available services                | ✓        |  ✗           | ✓        |
| Ontology subclasses of            | ✓        |  ✓           | ✓        |
| Ontology superclasses of          | ✓        |  ✓           | ✓        |
| Ontology is subsuperclass of      | ✓        |  ✓           | ✓        |
| Cognitive test chooser            | ✗        |  ✗           | ✓        |
| Cognitive get history             | ✗        |  ✗           | ✓        |
| Cognitive get scores              | ✗        |  ✗           | ✓        |
| Record cognitive test performance | ✗        |  ✗           | ✓        |
| Send email                        | ✗        |  ✗           | ✓        |
| Fetch received emails             | ✗        |  ✗           | ✓        |
| News stories                      | ✗        |  ✗           | ✓        |
| Geolocation                       | ✗        |  ✗           | ✓        |
| Weather report current            | ✗        |  ✗           | ✓        |
| Weather report forecast           | ✗        |  ✗           | ✓        |
| Hazard detection light-check      | ✗        |  ✗           | ✓        |
| Hazard detection door-check       | ✗        |  ✗           | ✓        |
| Path planning upload-map          | ✗        |  ✗           | ✓        |
| Path planning plan-path-2d        | ✗        |  ✗           | ✓        |


Information on RAPP Platform front-end Web Services can he found [here](https://github.com/rapp-project/rapp-platform/tree/master/rapp_web_services/services).

## Directories

- `cpp/`    : C++ RAPP-API Sources
- `js/`     : JavaScript RAPP-API Sources
- `python/` : Python RAPP-API Sources

## Tests

See under each directory for `tests`, `examples`.

Each language API has a `README.md` with detailed instructions on how to use it.

[![Join the chat at https://gitter.im/rapp-project/rapp-api](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/rapp-project/rapp-api?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

## Contributors

- Alexander Giokas, **[a.gkiokas@ortelio.co.uk]**
- Konstaninos Panayiotou, **[klpanagi@gmail.com]**
- Lazaros Penteridis, **[lp@ortelio.co.uk]**

## Contributing

- Please read `CONTRIBUTING.md` before submitting/contributing to this project.
