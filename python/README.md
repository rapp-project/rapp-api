## Synopsis

Containes RappCloud API module used for interfering wth RAPP Platform.

## Usage

##### Add the module to python path
Add the following into your ~/.bashrc in order to add RappCloud module into python module scope:

```
  export PYTHONPATH=$PYTHONPATH:<*rapp_api_repo_path*>/python
```

where <rapp_api_repo_path> is the path to the rapp-api repository locally.

>  e.g. "~/rapp_ws/src/rapp-api"


##### How to use the RappCloud module

```python
from RappCloud import RappCloud
...
rappCloud = RappCloud()
```

## Directories

- **RappCloud**: The RappCloud python module directory.


## Tests

Testing tools tha are also testing the usage of the RappCloud API python module can be found
into the rapp-platform repository under <rapp_platform_path>/hop_services/utilities/testing_tools

 [testing_tools](https://github.com/rapp-project/rapp-platform/tree/master/hop_services/utilities/testing_tools)


## Contributors

- Konstaninos Panayiotou, **[klpanagi@gmail.com]**
- Manos Tsardoulias, **[etsardou@gmail.com]**
