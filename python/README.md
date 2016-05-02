## Synopsis

The python implementation of the rapp-platform-api.

By default the api creates and holds a session for each Service instance (that is used until the service instance has been deleted or the Platfrom terminates it),
enabling this way, persistent connections to the Platfrorm.

## Dependencies

TLSv1.2 requires either python-2.7.9+ or pyopenssl.
If pyopenssl is installed on the system it is used to apply proper tlsv1.2 adapter.
Otherwise it falls back to use TLSv1.1 adapter.


## Installation

You can install the Python Rapp API package either in global system scope or under User's score.

We recommend installing the package on development mode. This way, editing the source code the changes will be available directly without having to reinstall every time that you make minor changes.


```shell
python setup.py develop --user
```


##  Configure 

### Authentication/Tokens
The RAPP Platform uses token-based authentication mechanisms to authenticate user's use it's resources.
User's receive a token on registration to the RAPP Platform.

For more information on how to register to the RAPP-Platform, look at [todo-reference-here](#)

Tokens are stored under:

```shell
${HOME}/.config/rapp_platform/tokens
```

Place the, received from the RAPP Platform, under the aforementioned directory (the file has to be named to **app**):

```shell
${HOME}/.config/rapp_platform/tokens/app
```

### Platform deployment/development

On default the RAPP API connects to the RAPP Platform Deployment Server. You can change that into the [config/platform.cfg](https://github.com/rapp-project/rapp-api/blob/python/python/RappCloud/config/platform.cfg)
configuration file. This file already includes configuration parameters used to connect to:

- The RAPP Platform Deployment Server.
- The RAPP Platform Development Server.
- The RAPP Platform installed **LOCALLY**.


## How to use the RAPP Platform Services though the API.

CloudService classes are implemented, for each RAPP Platform Service, under the RappCloud/CloudServices directory.
CloudService is the RAPP term for an established connection to the Platform Services over the Network.
Each CloudService class holds a ServiceController instance that is responsible for over network communications
to the RAPP Platform Services.


```python

# Import the FaceDetection CloudService
from RappCloud import FaceDetection

# Instantiate a new FaceDetection service
faceDetector = FaceDetection(image='<path_to_image_file>', fast=True)
# Call the RAPP Platform FaceDetection service
response = faceDetector.call()
# Print detected faces. Response properties can be retrieved using the dot notation
print response.faces
# Print the wohole response object, serialized to dictionary
print response.serialize() # Print the whole Platform's response object

...
# Set an attribute
faceDetector.fast = False
# Call
response = faceDetector.call()


```


## Directories

- **RappCloud**: The RappCloud python module directory.
- **RappCloud/CloudService**: CloudService implementation classes.
- **RappCloud/ServiceController**: The ServiceController implementation. Includes Transport Adapters, Authentication and ServiceController implementations.
- **RappCloud/RandStrGen**: The Random String Generator class used by the RappCloud class to generate random strings.


## Examples

Examples can be found under the examples directory.


## Tests
Functional/Unit are stored under the **tests** directory.
(**Under Development**)


RAPP Platform's integration tests, use the python rapp-platform-api. Those are located under the rapp-platform repository:

 [rapp_testing_tools](https://github.com/rapp-project/rapp-platform/tree/devel/rapp_testing_tools)


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


## Contributors

- Konstaninos Panayiotou, **[klpanagi@gmail.com]**
- Manos Tsardoulias, **[etsardou@gmail.com]**
