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


## Calling RAPP Platform Services - API usage.

Cloud Service is the RAPP term for an established connection to the RAPP-Platform Services, over the www (World-Wide-Web).
Each Platform Service has it's own unique Response and Request message.

The `Service` class is used to establish connections to the RAPP-Platform Web-Services, while `CloudMsg` objects include:
- `Request` object. RAPP-Platform Service specific Request message
- `Response` object. RAPP-Platform Service specific Response message


```py
from RappCloud import Service

svcClient = Service(persistent=True, timeout=30000)
```

`Service` object constructor allow to set:

- persistent: Force peristent connections (Defaults to `True`)
- timeout: Client timeout value. This is the timeout value waiting for a response from the RAPP Platform. (Defaults to infinity)

The `persistent` and `timeout` properties of a `Service` object are public members and can be set using the **dot** (.) notation:

```py
svcClient = Service()
svcClient.persistent = True
svcClient.timeout = 30000
```

`CloudMsg` objects are feed to the `Service` object to specific RAPP-Platform Services.
`CloudMsg` classes can be imported from the CloudMsgs submodule of the RappCloud module:

```py
from RappCloud.CloudMsgs import FaceDetection
```

The above line of code is used as an example of importing the `FaceDetection` CloudMsg class.

A complete description on available CloudMsg classes as long as their Request and Response message classes is available [here](RappCloud/CloudMsgs/CLOUD_MSGS.md)

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

`Service` objects have a `.call()` method for calling RAPP-Platform Services:

```py
class Service:
    ...

    def call(self, msg=None):
        ...
        return self.resp

    ...
```

The `.call()` method returns the Response object.

```py
svcClient= Service()
msg = FaceDetection()
msg.req.fast = True
msg.req.imageFilepath = '/tmp/face-sample.png'

response = svcClient.call(msg)
print response.faces
print response.error

```

CloudMsg objects are passed as argument to the `.call()` method of the `Service` object:

```py
svcClient= Service()
msg = FaceDetection(imageFilepath='/tmp/face-sample.png')
response = svcClient.call(msg)
```

`CloudMsg` objects can also be passed to the constructor of the `Service` class:

```py
faceMsg = FaceDetection(imageFilepath='/tmp/face-sample.png')
svcClient= Service(msg=faceMsg, timeout=15000)
response = svcClient.call()
```

**Note**: Calling several different RAPP-Platform Services is done by passing the service specific
Cloud Message objects to the `.call()` of the `Service` object.


The following example creates a `FaceDetection` and a `QrDetection` CloudMsg to call both
the Face-Detection and Qr-Detection RAPP-Platform Services.

```py
from RappCloud import Service
from RappCloud.CloudMsgs import (
    FaceDetection,
    QrDetection)

svcClient = Service(timeout=1000)
faceMsg = FaceDetection(fast=True, imageFilepath='/tmp/face-sample.png')
qrMsg = QrDetection()
qrMsg.req.imageFilepath = '/tmp/qr-sample.png'

fdResp = svcClient.call(faceMsg)
print "Found %s Faces" %len(fdResp.faces)

qrResp = svcClient.call(qrMsg)
print "Found %s QRs: %s" %(len(qrResp.qr_centers), qrResp.qr_messages)

```



## Directories

- **RappCloud**: The RappCloud python module directory.
- **RappCloud/CloudMsgs**: Cloud Message classes.
- **RappCloud/Service**: Service submodule


## Examples

Examples can be found in the `examples` directory.


## Tests
Functional/Unit tests are stored under the **tests** directory.


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
