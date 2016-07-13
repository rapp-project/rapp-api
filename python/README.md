## Contents

- [Synopsis](#synopsis)
- [Dependencies](#dependencies)
- [Install](#installation)
- [Configuration](#configuration)
  - [Authentication](#authentication)
  - [RAPP Platform parameters](#rapp-platform-parameters)
- [Calling RAPP Platform Services - API usage](#calling-rapp-platform-services)
  - [Advanced API](#advanced-api)
  - [Hight Level API](#high-level-api)
- [Examples](#examples)
- [Tests](#tests)
- [Documentation](#documentation)
- [Contributors](#contributors)
- [Contact](#contact)


## Synopsis

The python implementation of the rapp-platform-api. The API allow for calling RAPP Platform Services.

By default the api creates and holds a session for each Service instance (that is used until the service instance has been deleted or the Platfrom terminates it),
enabling this way, persistent connections to the Platfrorm.

## Dependencies

TLSv1.2 requires either python-2.7.9+ or pyopenssl.
If pyopenssl is installed on the system it is used to apply proper tlsv1.2 adapter.
Otherwise it falls back to use TLSv1.1 adapter.

- pyopenssl

## Installation

You can install the Python Rapp API package either in system global space or in user's space:

To install in user's space simply execute:

```bash
$ python setup.py install --user
```

Root permissions are required in order to install system-wise:

```bash
$ sudo python setup.py install
```


If you indent to contribute, it is recommended to install in development mode. This way, editing the source code the changes will be available directly without having to reinstall every time that you make minor changes.

```bash
python setup.py develop --user
```


##  Configuration

### Authentication
The RAPP Platform uses token-based authentication mechanisms to authenticate user's use it's resources.
User's receive a token on registration to the RAPP Platform.

[Here](https://github.com/rapp-project/rapp-platform/wiki/Create-a-new-RAPP-user) you can find more information on how to create/register a new RAPP user.

Tokens are stored under:

```bash
${HOME}/.config/rapp_platform/tokens
```

Place the, received from the RAPP Platform, under the aforementioned directory (the file has to be named to **app**):

```bash
${HOME}/.config/rapp_platform/tokens/app
```

### RAPP Platform parameters

The API allows to set default parameters, for the RAPP Platform to connect to, through a simple configuration file (**yaml**). Those parameters are:

- `address`: The RAPP Platform ipv4-address/hostname. Defaults to **'localhost'**
- `port`: The RAPP Platform listening port number. Defaults to **'9001'**
- `protocol`: Protocol to use. Either **'http'** or **'https'**

Parameters are imported from the configuration file:

```bash
~/.config/rapp_platform/python_platform_api/config
```

Below is a sample of the file that configures the API to connect to `http://localhost:9001`:

```yaml
address: 'localhost'
port: '9001'
protocol: 'http'
```

**Note**: In the next Section, we will indroduce the `Service` object and explain how we can connect to different RAPP Platform hosts, in a single application implementation.


## Calling RAPP Platform Services

API users are able to select from 2 API implementations:

- **High level API**
- **Advanced API**

The first one allow API users to easily call RAPP PLatform Services through simple function calls.
The second one is for advanced usage, delivered for expert developers. This is an object-oriented implementation. As we will later describe, the advanced API usage allow creation of Cloud Messages. Both Platform requests and responses
are described by static objects.

**Note**: The High Level API actually wraps the Advanced API.


### Advanced API

`RappPlatformService` is the RAPP term for an established connection to the RAPP-Platform Services, over the www (World-Wide-Web).
Each Platform Service has it's own unique Response and Request message.

The `RappPlatformService` class is used to establish connections to the RAPP-Platform Web-Services, while `CloudMsg` objects include:
- `Request` object. RAPP-Platform Service specific Request message
- `Response` object. RAPP-Platform Service specific Response message


```python
from RappCloud import RappPlatformService

svcClient = RappPlatformService(persistent=True, timeout=30000)
```

By Default it connects to the localhost, assuming that the RAPP Platform has been setup on the local machine.
The constructor of the `RappPlatformService` class allow to specify the RAPP Platform parameters to connect to.

```python
from RappCloud import RappPlatformService

svcClient = RappPlatformService(address='RAPP_PLATFORM_IPv4_ADDRESS',
    port='RAPP_PLATFORM_PORT_NUMBER',
    protocol='http')
```

`RappPlatformService` object constructor allow to set:

- persistent (Boolean): Force peristent connections. **Defaults to True**
- timeout (Integer): Client timeout value. This is the timeout value waiting for a response from the RAPP Platform. **Defaults to infinity**
- address (String): The RAPP Platform IPv4 address to connect to. **Defaults to 'localhost'**
- port (String): The RAPP Platform listening port. **Defaults to "9001"**
- protocol (String): The configured application protocol for the RAPP Platform. Valid values are "**https**" and "**http**". **Defaults to "http"**


The `persistent` and `timeout` properties of a `RappPlatformService` object are public members and can be set using the **dot** (.) notation:

```py
svcClient = RappPlatformService()
svcClient.persistent = True
svcClient.timeout = 30000
```

`CloudMsg` objects are feed to the `RappPlatformService` object to specific RAPP-Platform Services.
`CloudMsg` classes can be imported from the CloudMsgs submodule of the RappCloud module:

```py
from RappCloud.CloudMsgs import FaceDetection
```

The above line of code is used as an example of importing the `FaceDetection` CloudMsg class.

A complete description on available CloudMsg classes as long as their Request and Response message classes is available [here](RappCloud/CloudMsgs/README.md)

CloudMsg objects hold a Request and a Response object:

```py
from RappCloud.CloudMsgs import FaceDetection
faceDetectMsg = FaceDetection()

reqObj = faceDetectMsg.req
respObj = faceDetectMsg.resp
```

Request and Response objects of a CloudMsg can be serialized to a dictionary:

```py
reqDict = faceDetectMsg.req.serialize()
print reqDict
  >> {fast: False, imageFilePath: ''}

respDict = faceDetectMsg.resp.serialize()
print respDict
  >> {faces: [], error: ''}
```

CloudMsg Request property values can be set through the `req` property of the CloudMsg object. or as keyword arguments to the constructor of a CloudMsg:

```py
from RappCloud.CloudMsgs import FaceDetection

msg = FaceDetection(imageFilepath='/tmp/face-sample.png')
print msg.req.serialize()
  >> {fast: False, imageFilepath: '/tmp/face-sample.png'}

msg.req.fast = True
print msg.req.serialize()
  >> {fast: True, imageFilepath: '/tmp/face-sample.png'}
```

`RappPlatfomrService` objects have a `.call()` method for calling RAPP-Platform Services:

```py
class RappPlatformService:
    ...

    def call(self, msg=None):
        ...
        return self.resp

    ...
```

The `.call()` method returns the Response object.

```py
svcClient= RappPlatformService()
msg = FaceDetection()
msg.req.fast = True
msg.req.imageFilepath = '/tmp/face-sample.png'

response = svcClient.call(msg)
print response.faces
print response.error

```

CloudMsg objects are passed as argument to the `.call()` method of the `RappPlatformService` object:

```py
svcClient= RappPlatformService()
msg = FaceDetection(imageFilepath='/tmp/face-sample.png')
response = svcClient.call(msg)
```

`CloudMsg` objects can also be passed to the constructor of `RappPlatformService`:

```py
faceMsg = FaceDetection(imageFilepath='/tmp/face-sample.png')
svcClient= RappPlatformService(msg=faceMsg, timeout=15000)
response = svcClient.call()
```

**Note**: Calling several different RAPP-Platform Services is done by passing the service specific
Cloud Message objects to the `.call()` of the `RappPlatformService` object.


The following example creates a `FaceDetection` and a `QrDetection` CloudMsg to call both
the Face-Detection and Qr-Detection RAPP-Platform Services.

```py
from RappCloud import RappPlatformService
from RappCloud.CloudMsgs import (
    FaceDetection,
    QrDetection)

svcClient = RappPlatformService(timeout=1000)
faceMsg = FaceDetection(fast=True, imageFilepath='/tmp/face-sample.png')
qrMsg = QrDetection()
qrMsg.req.imageFilepath = '/tmp/qr-sample.png'

fdResp = svcClient.call(faceMsg)
print "Found %s Faces" %len(fdResp.faces)

qrResp = svcClient.call(qrMsg)
print "Found %s QRs: %s" %(len(qrResp.qr_centers), qrResp.qr_messages)

```

### High Level API

Like previously mentioned, API users can also use the High Level implementation of the RAPP Platform API. Benefits from using this implementation is lack of knowledge of how Cloud Messages and RappPlatformService are used.
Calls to the RAPP Platform are done through simple function calls, under the RappPlatformAPI module.

Below is an example of performing a query to the ontologyi, hosted on the RAPP Platform, using the High Level API implementation:

```python
from RappCloud import RappPlatformAPI
ch = RappPlatformAPI()

response = ch.ontologySubclasses("Oven")

print response
>> {'results': [u'http://knowrob.org/kb/knowrob.owl#MicrowaveOven', u'http://knowrob.org/kb/knowrob.owl#RegularOven', u'http://knowrob.org/kb/knowrob.owl#ToasterOven'], 'error': u''}
```

The RappPlatformAPI usage and calls are fully documented [here](https://github.com/rapp-project/rapp-api/tree/master/python/RappCloud), also with examples of usage.



## Examples

Examples of using the Advanced API can be found [here](https://github.com/rapp-project/rapp-api/tree/master/python/RappCloud/CloudMsgs/README.md) while examples of the [High Level API here](https://github.com/rapp-project/rapp-api/blob/master/python/RappCloud/README.md)


## Tests
Functional/Unit tests are stored under the **tests** directory.


RAPP Platform's integration tests, use the python rapp-platform-api. For more information head to the
[rapp_testing_tools](https://github.com/rapp-project/rapp-platform/tree/devel/rapp_testing_tools) package, of the rapp-platform repository.


## Documentation

This package is documented using doxygen generator. You can locally generate the documentation by executing the **gen_doc_python_api.sh** script located under rapp-api/documentation/scripts directory.
Just navigate through this directory and execute:

```bash
./gen_doc_python_api.sh
```

This script will generate source code documentation and store them under the

```bash
${HOME}/rapp_platform_files/documentation/rapp-api/python
```
directory

You can change the default output directory by passing the directory path as an input for the **gen_doc_python_api.sh** script:

```bash
./gen_doc_python_api.sh <out_dir>
```


## Directories

- **RappCloud**: The RappCloud python module directory.
- **RappCloud/CloudMsgs**: Cloud Message classes.
- **RappCloud/Service**: Service submodule that includes the `RappPlatformService` implementation.


## Contributors

- Konstaninos Panayiotou, **klpanagi@gmail.com**
- Manos Tsardoulias, **etsardou@gmail.com**


## Contact

An active gitter chat room is available:

[![Join the chat at https://gitter.im/rapp-project/rapp-api](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/rapp-project/rapp-api?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
