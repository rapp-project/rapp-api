## Synopsis

The Rapp Platform Python API, used for interfering wth the RAPP Platform Services.


## Dependencies

This package has no external third-party dependencies! 


## Installation

You can install the Python Rapp API package either in global system scope or under User's score.

We recommend installing the package on development mode. This way, editing the source code the changes will be available directly without having to reinstall every time that you make minor changes.

Simply execute, under this directory:

```shell
python setup.py develop --user
```


##  Configure 
Current implementation uses predefined user account credentials in order get access to
the RAPP Platform Web Services.
You can define your own account information into the [config/auth.cfg](https://github.com/rapp-project/rapp-api/blob/python/python/RappCloud/config/auth.cfg) configuration file.

On default the RAPP API connects to the RAPP Platform Deployment Server. You can change that into the [config/platform.cfg](https://github.com/rapp-project/rapp-api/blob/python/python/RappCloud/config/platform.cfg)
configuration file. This file already includes configuration parameters used to connect to:

- The RAPP Platform Deployment Server.
- The RAPP Platform Development Server.
- The RAPP Platform installed **LOCALLY**.


## Import the Rapp API into your code

```python

from RappCloud import RappCloud

...

rappCloud = RappCloud()

```

Multible tests showing the usage of the RappCloud API can be found under the rapp-platform repository:

 [rapp_testing_tools](https://github.com/rapp-project/rapp-platform/tree/master/rapp_testing_tools)


## Directories

- **RappCloud**: The RappCloud python module directory.
- **RappCloud/CloudInterface**: The CloudInterface package used by the RappCloud class to perform Web .Post Requests.
- **RappCloud/RandStrGen**: The Random String Generator class used by the RappCloud class to generate random strings.


## Tests

The Test-Engine and individual written tests, using this engine, are located under the rapp-platform repository:

 [rapp_testing_tools](https://github.com/rapp-project/rapp-platform/tree/master/rapp_testing_tools)


## Documentation

This package is documented using doxygen documentation generator. You can locally generate the documentation by executing the **gen_doc_python_api.sh** script located under rapp-api/documentation/scripts directory.
Just navigate through this directory and execute:

```shell
./gen_doc_python_api.sh
```

This script will generate source code documentation and store them under the

```shell
${HOME}/rapp_platform_files/documentation/rapp-api/python
```
directory

You can change the default output directory by passing the directory path as an input for the **gen_doc_python_api.sh** script:

```shell
./gen_doc_python_api.sh <out_dir>
```

TODO -- Export html doxygen generated documentation


## Contributors

- Konstaninos Panayiotou, **[klpanagi@gmail.com]**
- Manos Tsardoulias, **[etsardou@gmail.com]**
