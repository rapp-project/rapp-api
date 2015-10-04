## Synopsis

Containes RappCloud API module used for interfering wth RAPP Platform.

## Usage

#### Add the module to python path

Add the following into your ~/.bashrc in order to add RappCloud module into python module scope:

```
  export PYTHONPATH=$PYTHONPATH:{rapp_api_repo_path}/python
```

where {rapp_api_repo_path} is the path to locally installed rapp-api repository.

>  e.g. "~/rapp_ws/src/rapp-api"


#### Dependencies

Dependencies are defined into dependencies.txt file.
To install all dependencies (global-scope) execute under this directory:

```bash
sudo pip install -r dependencies.txt
```

####  Configurations
Current implementation uses predefined user account credentials in order get access to
the RAPP Platform Web Services.
You can define your own account information into the [config/auth.cfg](https://github.com/rapp-project/rapp-api/blob/python/python/RappCloud/config/auth.cfg) configuration file.

On default the RAPP API connects to the RAPP Platform Deployment Server. You can change that into the [config/platform.cfg](https://github.com/rapp-project/rapp-api/blob/python/python/RappCloud/config/platform.cfg)
configuration file. This file already includes configuration parameters used to connect to:

- The RAPP Platform Deployment Server.
- The RAPP Platform Development Server.
- The RAPP Platform installed **LOCALLY**.


#### How to use the RappCloud module

```python
from RappCloud import RappCloud
...
rappCloud = RappCloud()
```

Multible tests showing the usage of the RappCloud API can be found under the rapp-platform repository:

 [rapp_testing_tools](https://github.com/rapp-project/rapp-platform/tree/master/rapp_testing_tools)


## Install

--TODO--


## Directories

- **RappCloud**: The RappCloud python module directory.


## Tests

The Test-Engine and individual written tests, using this engine, are located under the rapp-platform repository:

 [rapp_testing_tools](https://github.com/rapp-project/rapp-platform/tree/master/rapp_testing_tools)


## Contributors

- Konstaninos Panayiotou, **[klpanagi@gmail.com]**
- Manos Tsardoulias, **[etsardou@gmail.com]**
