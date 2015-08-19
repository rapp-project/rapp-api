## Synopsis

Containes RappCloud API module used for interfering wth RAPP Platform.

## Usage

##### Add the module to python path
Add the following into your ~/.bashrc in order to add RappCloud module into python module scope:

```
  export PYTHONPATH=$PYTHONPATH:{rapp_api_repo_path}/python
```

where {rapp_api_repo_path} is the path to the rapp-api repository locally.

>  e.g. "~/rapp_ws/src/rapp-api"


#####  Configurations
Current implementation uses predefined user account credentials in order get access to
the RAPP Platform Web Services.
You can define your own account information into the **config/auth.cfg** configuration file.

On default the RAPP API connects to the RAPP Platform Deployment Server. You can change that into the config/platform.cfg
configuration file. This file already includes configuration parameters used to connect to:

- The RAPP Platform Deployment Server.
- The RAPP Platform Development Server.
- The RAPP Platform install **LOCALLY**.


##### How to use the RappCloud module

```python
from RappCloud import RappCloud
...
rappCloud = RappCloud()
```

Multible tests showing the usage of the RappCloud API can be found under the rapp-platform repository
( {rapp_platform_path}/hop_services/utilities/testing_tools/python_tests ) locally or at the following link:

 [testing_tools](https://github.com/rapp-project/rapp-platform/tree/master/hop_services/utilities/testing_tools/python_tests)


## Directories

- **RappCloud**: The RappCloud python module directory.


## Tests

Testing tools tha are also testing the usage of the RappCloud API python module can be found
under the rapp-platform repository ( {rapp_platform_path}/hop_services/utilities/testing_tools ) locally
or at the following link:

 [testing_tools](https://github.com/rapp-project/rapp-platform/tree/master/hop_services/utilities/testing_tools)


## Contributors

- Konstaninos Panayiotou, **[klpanagi@gmail.com]**
- Manos Tsardoulias, **[etsardou@gmail.com]**
